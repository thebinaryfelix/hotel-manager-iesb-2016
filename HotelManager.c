#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

int loggedIn() //OK
{
    //Identifica se o usuário fez login ou não.

    FILE *arq_funcionarios;
    FILE *arq_admin;
    FILE *arq_checkIn;
    FILE *autenticado;

    char user[30] = " ";
    char cName[30];
    char cName2[30];
    char pass[10] = " ";
    char line[22];

    int i, UserNotFound=0;




    system("cls"); //Clear screen.

    printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("                          ||                 FELIPPE'S HOTEL                       ||\n");
    printf("                          ||                                                       ||\n");
    printf("                          ||                  ÁREA DE LOGIN                        ||\n");
    printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    printf("                                             Usuário: ");
    fflush(stdin);
    fgets(user, 11, stdin);
    printf("                                             Senha: ");
    fflush(stdin);
    fgets(pass, 9, stdin);

    pass[strcspn(pass, "\n")] = 0;  //A função strcspn() retorna um número inteiro que, nesse caso, corresponde ao índice da primeira ocorrência de '\n' em pass[i] = '\n' anulando esta ocorrência.
    //Utilizei esta função para evitar duplicatas '\n' na hora de salvar os dados do usuário em arquivo e na hora da leitura deste mesmo arquivo.

    strcpy(cName, user);
    cName[strcspn(cName, "\n")] = 0;

    for (i=0 ; i<strlen(user) ; i++)
    {
        if(user[i] == '\n')
        {
            user[i] = '\t';
        }
    }
    if(strlen(user) == 10 && user[strlen(user)-1] != '\t')
    {
        strcat(user, "\t");
    }



    strcat(pass, "\n");
    strcat(user, pass);

    arq_funcionarios = fopen("Login/Funcionarios.txt", "r"); //ABRE ARQUIVO DOS FUNCIONÁRIOS

    if(arq_funcionarios == NULL)
    {
        printf("Falha ao abrir arquivo de funcionários.");
    }
    else
    {
        while(fgets(line, 20, arq_funcionarios) != NULL)
        {
            if(strcmp(line, user) == 0)
            {
                fclose(arq_funcionarios); //FECHA ARQUIVO DOS FUNCIONÁRIOS CASO ENCONTRE O USUÁRIO

                autenticado = fopen("Login/autenticadoATUAL.txt", "w");
                if(autenticado == NULL)
                {
                    printf("Falha ao abrir arquivo.");
                }
                else
                {
                    fprintf(autenticado, "%s", cName);
                }
                fclose(autenticado);

                strcat(cName,".txt");
                strcpy(cName2, "Login/Count_CheckIn/");
                strcat(cName2, cName);
                arq_checkIn = fopen(cName2, "a+");
                fclose(arq_checkIn);
                return 1; //Retorna 1 se for funcionário.
            }
            else
            {
                UserNotFound = 1;
            }
        }
    }

    if(UserNotFound == 1)
    {
        arq_admin = fopen("Login/Admins.txt", "r"); //ABRE ARQUIVO DOS ADMINISTRADORES

        if(arq_admin == NULL)
        {
            printf("Falha ao abrir arquivo de administradores.");
        }
        else
        {
            while(fgets(line, 20, arq_admin) != NULL)
            {
                if(strcmp(line, user) == 0)
                {
                    fclose(arq_admin); //FECHA ARQUIVO DOS ADMINISTRADORES CASO ENCONTRE O USUÁRIO
                    fclose(arq_funcionarios); //FECHA ARQUIVO DOS FUNCIONÁRIOS CASO ENCONTRE O USUÁRIO

                    autenticado = fopen("Login/autenticadoATUAL.txt", "w");
                    if(autenticado == NULL)
                    {
                        printf("Falha ao abrir arquivo.");
                    }
                    else
                    {
                        fprintf(autenticado, "%s", cName);
                    }
                    fclose(autenticado);

                    strcat(cName,".txt");
                    strcpy(cName2, "Login/Count_CheckIn/");
                    strcat(cName2, cName);
                    arq_checkIn = fopen(cName2, "a+");
                    fclose(arq_checkIn);
                    return 2; //Retorna 2 se for administrador.
                }
                else
                {
                    UserNotFound = 2;
                }
            }
        }
    }

    //Este programa foi desenvolvido por Mateus C. F. Oliveira

    if(UserNotFound == 2)
    {
        system("cls");
        printf("\n\n                                  Usuário ou senha não encontrados.\n");
        printf("                             Acesse o perfil de administrador para cadastrar um usuário.\n\n");
        printf("\t\t\t");
        system("pause");
        system("cls");
    }
    fclose(arq_admin); //FECHA ARQUIVO DOS ADMINISTRADORES
    fclose(arq_funcionarios); //FECHA ARQUIVO DOS FUNCIONÁRIOS
    return 0;
}

int cadastrar_funcionario() //OK
{

    FILE *arq_funcionarios;
    FILE *arq_admin;
    FILE *arq_nomes_registrados;

    char nome[30];
    char senha[10];
    char line[20];

    int UserStats, OkToRegister=0, verificador=0, i;




    system("cls");
    printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("                          ||                 FELIPPE'S HOTEL                       ||\n");
    printf("                          ||                                                       ||\n");
    printf("                          ||           CADASTRAR NOVO FUNCIONÁRIO                  ||\n");
    printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

    while(OkToRegister != 1)
    {
        arq_nomes_registrados = fopen("Login/Geral_nomes.txt", "r"); //ABRE ARQUIVO GERAL DOS NOMES DE USUÁRIOS

        if(arq_nomes_registrados == NULL)
        {
            printf("Falha ao abrir arquivo.");
        }
        else
        {
            printf("                                     Nome do usuario: ");
            fflush(stdin);
            fgets(nome, 11, stdin);

            if(strlen(nome) == 10 && nome[strlen(nome)-1] != '\n')
            {
                strcat(nome, "\n");
            }

            nome[strcspn(nome, "\n")] = 0;

            printf("                         Senha (maximo 8 caracteres): ");
            fflush(stdin);
            fgets(senha, 9, stdin);

            senha[strcspn(senha, "\n")] = 0;

            printf("\n");
            printf("               Esse usuário será administrador do sistema?\n\n");
            printf("                                    [1] - SIM   [2] - NÃO: ");
            fflush(stdin);
            scanf("%d", &UserStats);

            while(fgets(line, 11, arq_nomes_registrados) != NULL && verificador==0)
            {
                line[strcspn(line, "\n")] = 0;
                printf("nome: %s", nome);
                printf("linha: %s", line);
                printf("______");
                system("pause");
                if(strcmp(line, nome)==0)
                {

                    verificador++;
                }
            }
            if(verificador!=0)
            {
                OkToRegister = 0;
                printf("\n                                          Usuário já cadastrado.\n\n");
            }
            else
            {
                OkToRegister = 1;
            }
            verificador=0;
        }
        fclose(arq_nomes_registrados);//FECHA ARQUIVO GERAL DE NOMES
    }

    arq_admin = fopen("Login/Admins.txt", "a");//ABRE ARQUIVO DOS ADMINISTRADORES
    arq_funcionarios = fopen("Login/Funcionarios.txt", "a");//ABRE ARQUIVO DOS FUNCIONÁRIOS
    arq_nomes_registrados = fopen("Login/Geral_nomes.txt", "a");//ABRE ARQUIVO GERAL DOS NOMES

    if(arq_funcionarios == NULL || arq_admin == NULL || arq_nomes_registrados == NULL)
    {
        printf("Falha ao abrir um dos arquivos.");
    }
    else
    {

        fprintf(arq_nomes_registrados, "%s", nome);

        nome[strcspn(nome, "\n")] = 0;
        strcat(nome, "\t");

        strcat(senha, "\n");

        strcat(nome, senha);

        if(UserStats == 1)
        {
            fprintf(arq_admin, "%s", nome); //Nome já concatenado com a senha cadastrada.
        }
        else
        {
            fprintf(arq_funcionarios, "%s", nome); //Nome já concatenado com a senha cadastrada.
        }
    }

    fclose(arq_admin);
    fclose(arq_funcionarios);
    fclose(arq_nomes_registrados);

    return 0;
}

int remover_funcionario() //OK
{

    FILE *arq_funcionarios;
    FILE *arq_admin;
    FILE *tmpFile;
    FILE *arq_nomes_registrados;
    FILE *atual;

    char *inFileAdm = "Login/Admins.txt";
    char *inFileFunc = "Login/Funcionarios.txt";
    char *outFile = "Login/tmp.txt";
    char *atualUsuario = "Login/autenticadoATUAL.txt";
    char nome[11];
    char verifyName[11];
    char removeUsername[11];
    char aux [11] = "";
    char line[20] = "";

    int i=0, j=0;
    int c, stop, countLine;
    int removeFromAdmFile=0, encontrado=0, usuarioAutenticado=0;




    system("cls");

    arq_admin = fopen("Login/Admins.txt", "r");//ABRE ARQUIVO DOS ADMINISTRADORES
    arq_funcionarios = fopen("Login/Funcionarios.txt", "r");//ABRE ARQUIVO DOS FUNCIONÁRIOS
    arq_nomes_registrados = fopen("Login/Geral_nomes.txt", "r");//ABRE ARQUIVO GERAL DOS NOMES


    if(arq_funcionarios == NULL || arq_admin == NULL || arq_nomes_registrados == NULL)
    {
        printf("Falha ao abrir um dos arquivos.");
    }
    else
    {
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("                          ||                 FELIPPE'S HOTEL                       ||\n");
        printf("                          ||                                                       ||\n");
        printf("                          ||               REMOVER FUNCIONÁRIO                     ||\n");
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n\n");
        printf("                                          Usuários cadastrados:\n\n");
        while(fgets(nome, 11, arq_nomes_registrados) != NULL) //Apenas para mostrar os nomes dos funcionários cadastrados, em formato de matriz Nx5 (N linhas x 5 colunas).
        {
            nome[strcspn(nome, "\n")] = 0;

            printf("\t%s", nome);
            i++;
            if(i==8)
            {
                printf("\n");
                i=0;
            }
        }
        fclose(arq_nomes_registrados);//FECHA ARQUIVO GERAL DOS NOMES

        //Nesse ponto, os arquivos "Login/Funcionarios.txt" e "Login/Admins.txt" ainda estão ABERTOS para LEITURA "r".

        printf("\n\n\n\tDigite o nome do usuário a ser removido ou SAIR para retornar: ");
        fflush(stdin);
        fgets(removeUsername, 11, stdin);
        removeUsername[strcspn(removeUsername, "\n")] = 0;

        if(strcmp(removeUsername, "SAIR")==0)
        {
            return 1;
        }
        else
        {
            while(encontrado != 1)
            {
                arq_nomes_registrados = fopen("Login/Geral_nomes.txt", "r");//ABRE ARQUIVO GERAL DOS NOMES

                if(arq_nomes_registrados == NULL)
                {
                    printf("Falha ao abrir um dos arquivos.");
                }
                else
                {
                    stop = 0;
                    while(stop == 0)
                    {
                        i=0;
                        memset(aux, 0, sizeof(aux));//Resetar string aux toda vez antes de reiniciar o segundo while (abaixo).
                        while(fgets(nome, 11, arq_nomes_registrados) != NULL)
                        {
                            nome[strcspn(nome, "\n")] = 0;

                            if(strcmp(nome, removeUsername)==0)
                            {
                                stop = 1;
                            }
                        }
                        if(fgets(nome, 11, arq_nomes_registrados) == NULL && stop != 1)
                        {
                            if(strcmp(nome, "fixo")==0)
                            {
                                stop = 1;
                                encontrado = 0;
                                printf("\n\tUsuário informado não existe. Favor informar outro nome: ");
                                fflush(stdin);
                                fgets(removeUsername, 11, stdin);
                                removeUsername[strcspn(removeUsername, "\n")] = 0;

                                if(strcmp(removeUsername, "SAIR")==0)
                                {
                                    return 1;
                                }
                            }
                            else
                            {
                                stop = 1;
                                encontrado = 0;
                                printf("\n\tUsuário informado não existe. Favor informar outro nome: ");
                                fflush(stdin);
                                fgets(removeUsername, 11, stdin);
                                removeUsername[strcspn(removeUsername, "\n")] = 0;

                                if(strcmp(removeUsername, "SAIR")==0)
                                {
                                    return 1;
                                }
                            }
                        }
                        else
                        {
                            atual = fopen(atualUsuario, "r"); //ABRE ARQUIVO DE REGISTRO DO USUÁRIO ATUAL AUTENTICADO NO SISTEMA

                            fgets(verifyName, 11, atual);

                            if(strcmp(removeUsername, verifyName)==0)
                            {
                                usuarioAutenticado = 1;
                            }
                            else
                            {
                                usuarioAutenticado = 0;
                            }

                            fclose(atual); //FECHA ARQUIVO DE REGISTRO DE LOGIN

                            if(usuarioAutenticado == 0)
                            {
                                encontrado = 1;
                            }
                            else
                            {
                                printf("\n\tUsuário selecionado não pode ser removido pois está em uso: É você!\n\n");
                                printf("\tFavor informar outro nome de usuário: ");
                                fflush(stdin);
                                fgets(removeUsername, 11, stdin);
                                removeUsername[strcspn(removeUsername, "\n")] = 0;

                                if(strcmp(removeUsername, "SAIR")==0)
                                {
                                    return 1;
                                }
                            }
                        }
                    }
                }
                fclose(arq_nomes_registrados);//FECHA ARQUIVO GERAL DOS NOMES
            }

            stop = 0;
            countLine = 0;
            while(stop == 0)
            {
                i=0;
                memset(aux, 0, sizeof(aux));//Resetar string aux toda vez antes de reiniciar o segundo while (abaixo).
                while((c = fgetc(arq_admin)) != EOF && (char) c != '\t' && (char) c != '\n')
                {
                    aux[i++] = (char) c;
                }
                if(strcmp(aux, removeUsername)==0)
                {
                    stop = 1;
                    removeFromAdmFile = 1;
                }


                j=0;
                memset(aux, 0, sizeof(aux));//Resetar string aux toda vez antes de reiniciar o segundo while (abaixo).
                while((c = fgetc(arq_funcionarios)) != EOF && (char) c != '\t' && (char) c != '\n')
                {
                    aux[j++] = (char) c;
                }
                if(strcmp(aux, removeUsername)==0)
                {
                    stop = 1;
                }

                countLine++; //Só precisamos contar os números ímpares desta variável para saber em qual linha está o usuário desejado.
            }
            fclose(arq_admin);//FECHA ARQUIVO DOS ADMINISTRADORES
            fclose(arq_funcionarios);//FECHA ARQUIVO DOS FUNCIONÁRIOS


            if(removeFromAdmFile == 1)
            {
                arq_admin = fopen(inFileAdm, "r");//ABRE ARQUIVO DOS ADMINISTRADORES
                tmpFile =  fopen(outFile, "w+");//ABRE ARQUIVO TEMPORÁRIO

                if(arq_admin == NULL && tmpFile == NULL)
                {
                    printf("Falha ao abrir um dos arquivos.\n");
                }
                else
                {
                    i=1;
                    while(fgets(line, 20, arq_admin) != NULL)
                    {

                        if(i != (countLine+1)/2)
                        {
                            fprintf(tmpFile, "%s", line);
                        }
                        i++;
                    }
                }
                fclose(tmpFile);//FECHA ARQUIVO TEMPORÁRIO
                fclose(arq_admin);//FECHA ARQUIVO DOS ADMINISTRADORES

                if(remove(inFileAdm) != 0)
                {
                    printf("Arquivo não deletado\n");
                    system("pause");
                }
                if(rename(outFile, "Login/Admins.txt") != 0 )
                {
                    printf("Erro ao renomear arquivos.\n");
                    system("pause");
                }
            }
            else
            {
                arq_funcionarios = fopen(inFileFunc, "r");//ABRE ARQUIVO DOS FUNCIONÁRIOS
                tmpFile =  fopen(outFile, "w+");//ABRE ARQUIVO TEMPORÁRIO

                if(arq_funcionarios == NULL && tmpFile == NULL)
                {
                    printf("Falha ao abrir um dos arquivos.\n");
                }
                else
                {
                    j=1;
                    while(fgets(line, 20, arq_funcionarios) != NULL)
                    {

                        if(j != (countLine+1)/2)
                        {
                            fprintf(tmpFile, "%s", line);
                        }
                        j++;
                    }
                }

                fclose(arq_funcionarios);//FECHA ARQUIVO DOS FUNCIONÁRIOS
                fclose(tmpFile);//FECHA ARQUIVO TEMPORÁRIO


                if(remove("Login/Funcionarios.txt") != 0)
                {
                    printf("Arquivo não deletado\n");
                    system("pause");
                }
                if(rename(outFile, "Login/Funcionarios.txt") != 0 )
                {
                    printf("Erro ao renomear arquivo.\n");
                    system("pause");
                }

            }


            arq_nomes_registrados = fopen("Login/Geral_nomes.txt", "r");//ABRE ARQUIVO GERAL DOS NOMES

            stop = 0;
            countLine = 0;
            while(stop == 0)
            {

                i=0;
                memset(aux, 0, sizeof(aux));
                while((c = fgetc(arq_nomes_registrados)) != EOF && (char) c != '\t' && (char) c != '\n')
                {
                    aux[i++] = (char) c;
                }
                if(strcmp(aux, removeUsername)==0)
                {
                    stop = 1;
                }
                countLine++;

            }

            fclose(arq_nomes_registrados);//FECHA ARQUIVO GERAL DOS NOMES

            arq_nomes_registrados = fopen("Login/Geral_nomes.txt", "r");//ABRE ARQUIVO GERAL DOS NOMES
            tmpFile =  fopen(outFile, "w+");//ABRE ARQUIVO TEMPORÁRIO

            if(arq_nomes_registrados == NULL && tmpFile == NULL)
            {
                printf("Falha ao abrir um dos arquivos.\n");
            }
            else
            {
                i=1;
                while(fgets(line, 20, arq_nomes_registrados) != NULL)
                {
                    if(i != countLine)
                    {
                        fprintf(tmpFile, "%s", line);
                    }
                    i++;
                }
            }
            fclose(arq_nomes_registrados);//FECHA ARQUIVO GERAL DOS NOMES
            fclose(tmpFile);//FECHA ARQUIVO TEMPORÁRIO

            if(remove("Login/Geral_nomes.txt") != 0)
            {
                printf("Arquivo não deletado\n");
                system("pause");
            }
            if(rename(outFile, "Login/Geral_nomes.txt") != 0 )
            {
                printf("Erro ao renomear arquivo.\n");
                system("pause");
            }
        }
    }

    fclose(arq_admin);
    fclose(arq_funcionarios);

    return 0;
}

int adicionar_quarto() //OK
{

    FILE *arq_quartos;
    FILE *desocupados;

    char numQuarto[20];
    char aux[20] = "";
    char qtdPessoas[10];

    int OkToRegister=0;
    int i=0;
    int c, stop, countLine;




    system("cls");
    printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("                          ||                 FELIPPE'S HOTEL                       ||\n");
    printf("                          ||                                                       ||\n");
    printf("                          ||                 ADICIONAR QUARTO                      ||\n");
    printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n\n");

    printf("                    Digite o número do quarto a ser adicionado: ");
    fflush(stdin);
    fgets(numQuarto, 5, stdin);
    numQuarto[strcspn(numQuarto, "\n")] = 0;

    printf("         Digite a capacidade deste quarto (número de hóspedes): ");
    fflush(stdin);
    fgets(qtdPessoas, 5, stdin);
    qtdPessoas[strcspn(qtdPessoas, "\n")] = 0;


    OkToRegister=0;
    while(OkToRegister==0)
    {
        arq_quartos = fopen("Quartos/Quartos.txt", "r");

        stop = 0;
        countLine = 0;
        while(stop == 0)
        {
            i=0;
            memset(aux, 0, sizeof(aux));
            while((c = fgetc(arq_quartos)) != EOF && (char) c != '\t' && (char) c != '\n')
            {
                aux[i++] = (char) c;
            }
            if(strcmp(aux, numQuarto)==0)
            {
                stop = 1;
                OkToRegister = 0;
            }
            else if(fgets(aux, 20, arq_quartos) == NULL)
            {
                stop = 1;
                OkToRegister = 1;
            }
            countLine++;
        }

        fclose(arq_quartos);

        if(OkToRegister==0)
        {
            memset(numQuarto, 0, sizeof(numQuarto));

            printf("\n                 Quarto já existe. Favor informar outro número: ");
            fflush(stdin);
            gets(numQuarto);
            numQuarto[strcspn(numQuarto, "\n")];

            printf("         Digite a capacidade deste quarto (número de hóspedes): ");
            fflush(stdin);
            gets(qtdPessoas);
            qtdPessoas[strcspn(qtdPessoas, "\n")];
        }
    }

    arq_quartos = fopen("Quartos/Quartos.txt", "a");

    if(arq_quartos == NULL)
    {
        printf("Falha ao abrir o arquivo dos Quartos.");
    }
    else
    {
        desocupados = fopen("Quartos/QuartosDesocupados.txt", "a");

        if(desocupados == NULL)
        {
            printf("Falha ao abrir arquivo dos qurtos registrados.");
        }
        else
        {
            strcat(numQuarto, "\n");
            fprintf(desocupados, "%s", numQuarto);
            numQuarto[strcspn(numQuarto, "\n")] = 0;
        }
        fclose(desocupados);

        strcat(numQuarto, "\t");
        strcat(qtdPessoas, "\n");
        strcat(numQuarto, qtdPessoas);

        fprintf(arq_quartos, "%s", numQuarto);
    }
    fclose(arq_quartos);

    return 0;
}

int remover_quarto() //OK
{

    FILE *arq_quartos;
    FILE *tmpFile;
    FILE *desocupados;
    FILE *ocupados;

    char *inFile = "Quartos/Quartos.txt";
    char *outFile = "Quartos/tmp.txt";
    char numQuarto[11];
    char numero[20];
    char removeRoom[11];
    char aux [11] = "";
    char line[20] = "";

    int i=0, j=0;
    int c, stop, countLine;
    int encontrado=0;




    system("cls");

    arq_quartos = fopen("Quartos/Quartos.txt", "r");
    desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");
    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");

    if(arq_quartos == NULL || desocupados == NULL)
    {
        printf("Falha ao abrir um dos arquivos.");
    }
    else
    {
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("                          ||                 FELIPPE'S HOTEL                       ||\n");
        printf("                          ||                                                       ||\n");
        printf("                          ||                 REMOVER QUARTO                        ||\n");
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n\n");
        printf("                                                 [Ocupados]\n\n");

        while(fgets(numero, 11, ocupados) != NULL)
        {
            numero[strcspn(numero, "\n")] = 0;

            printf("\t%s", numero);
            i++;
            if(i==8)
            {
                printf("\n");
                i=0;
            }
        }
        fclose(ocupados);

        printf("\n                                               [Desocupados]\n\n");

        while(fgets(numero, 11, desocupados) != NULL)
        {
            numero[strcspn(numero, "\n")] = 0;

            printf("\t%s", numero);
            i++;
            if(i==8)
            {
                printf("\n");
                i=0;
            }
        }
        fclose(desocupados);


        //Nesse ponto, o arquivo "Quartos/Quartos.txt" ainda está ABERTO para LEITURA "r".

        printf("\n\n\n\tDigite o numero do quarto a ser removido ou SAIR para retornar: ");
        fflush(stdin);
        fgets(removeRoom, 11, stdin);
        removeRoom[strcspn(removeRoom, "\n")] = 0;

        if(strcmp(removeRoom, "SAIR")==0)
        {
            return 1;
        }
        else
        {
            while(encontrado != 1)
            {
                desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");

                if(desocupados == NULL)
                {
                    printf("Falha ao abrir um dos arquivos.");
                }
                else
                {
                    stop = 0;
                    while(stop == 0)
                    {
                        i=0;
                        memset(aux, 0, sizeof(aux));
                        while(fgets(numQuarto, 11, desocupados) != NULL)
                        {
                            numQuarto[strcspn(numQuarto, "\n")] = 0;

                            if(strcmp(numQuarto, removeRoom)==0)
                            {
                                stop = 1;
                            }
                        }
                        if(fgets(numQuarto, 11, desocupados) == NULL && stop != 1)
                        {
                            if(strcmp(numQuarto, "fixo")==0) //Apenas por segurança.
                            {
                                stop = 1;
                                encontrado = 0;
                                printf("\n\tQuarto informado não existe ou está ocupado. Favor informar outro número: ");
                                fflush(stdin);
                                fgets(removeRoom, 11, stdin);
                                removeRoom[strcspn(removeRoom, "\n")] = 0;

                                if(strcmp(removeRoom, "SAIR")==0)
                                {
                                    return 1;
                                }
                            }
                            else
                            {
                                stop = 1;
                                encontrado = 0;
                                printf("\n\tQuarto informado não existe ou está ocupado. Favor informar outro número: ");
                                fflush(stdin);
                                fgets(removeRoom, 11, stdin);
                                removeRoom[strcspn(removeRoom, "\n")] = 0;

                                if(strcmp(removeRoom, "SAIR")==0)
                                {
                                    return 1;
                                }
                            }
                        }
                        else
                        {
                            encontrado = 1;
                        }
                    }
                }
                fclose(desocupados);
            }

            stop = 0;
            countLine = 0;
            while(stop == 0)
            {
                i=0;
                memset(aux, 0, sizeof(aux));
                while((c = fgetc(arq_quartos)) != EOF && (char) c != '\t' && (char) c != '\n')
                {
                    aux[i++] = (char) c;
                }
                if(strcmp(aux, removeRoom)==0)
                {
                    stop = 1;
                }
                countLine++;
            }
            fclose(arq_quartos);

            arq_quartos = fopen(inFile, "r");
            tmpFile =  fopen(outFile, "w+");

            if(arq_quartos == NULL && tmpFile == NULL)
            {
                printf("Falha ao abrir um dos arquivos.\n");
            }
            else
            {
                i=1;
                while(fgets(line, 20, arq_quartos) != NULL)
                {
                    if(i != (countLine+1)/2)
                    {
                        fprintf(tmpFile, "%s", line);
                    }
                    i++;
                }
            }
            fclose(tmpFile);
            fclose(arq_quartos);

            if(remove(inFile) != 0)
            {
                printf("Arquivo não deletado\n");
                system("pause");
            }
            if(rename(outFile, "Quartos/Quartos.txt") != 0 )
            {
                printf("Erro ao renomear arquivos.\n");
                system("pause");
            }

            desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");

            stop = 0;
            countLine = 0;
            while(stop == 0)
            {

                i=0;
                memset(aux, 0, sizeof(aux));
                while((c = fgetc(desocupados)) != EOF && (char) c != '\t' && (char) c != '\n')
                {
                    aux[i++] = (char) c;
                }
                if(strcmp(aux, removeRoom)==0)
                {
                    stop = 1;
                }
                countLine++;

            }

            fclose(desocupados);

            desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");
            tmpFile =  fopen(outFile, "w+");

            if(desocupados == NULL && tmpFile == NULL)
            {
                printf("Falha ao abrir um dos arquivos.\n");
            }
            else
            {
                i=1;
                while(fgets(line, 20, desocupados) != NULL)
                {
                    if(i != countLine)
                    {
                        fprintf(tmpFile, "%s", line);
                    }
                    i++;
                }
            }
            fclose(desocupados);
            fclose(tmpFile);

            if(remove("Quartos/QuartosDesocupados.txt") != 0)
            {
                printf("Arquivo não deletado\n");
                system("pause");
            }
            if(rename(outFile, "Quartos/QuartosDesocupados.txt") != 0 )
            {
                printf("Erro ao renomear arquivo.\n");
                system("pause");
            }
        }
    }

    fclose(arq_quartos);
    fclose(desocupados);

    return 0;
}

int contarCheckIn() //OK
{

    FILE *arq;
    FILE *log;

    char nome[30];
    char nome2[30];
    char contador = 'i';


    arq = fopen("Login/autenticadoATUAL.txt", "r");

    if(arq == NULL)
    {
        printf("Falha ao abrir autenticadoATUAL.");
    }
    else
    {
        fgets(nome, 11, arq);
    }
    fclose(arq);

    strcat(nome, ".txt");
    strcpy(nome2, "Login/Count_CheckIn/");
    strcat(nome2, nome);

    log = fopen(nome2, "a");
    if(log == NULL)
    {
        printf("Falha ao abrir arquivo de usuário.");
    }
    else
    {
        fprintf(log, "%c", contador);
    }
    fclose(log);

    return 0;
}

int DadosHospede(char *a) //OK
{
    FILE *quartos;
    FILE *hospede;
    FILE *hospedesGeral;
    FILE *reg_hospede;

    char *open1 = "Quartos/Quartos.txt";
    char open2[50];
    char nomePrincipal[31];
    char numHospedes[3];
    char dadosQuarto[11];
    char numQuarto[20];
    char fileRoom[50];
    char fileRoom2[50];
    char arqQuartos[50];
    char contador = 'i';
    char compararNome[31];

    int encontrado;
    int stop;
    int i;
    int ok=0;
    strcpy(dadosQuarto, a);
    strcat(dadosQuarto, "\t");



    printf("\n\n\t************************Dados do Hóspede************************\n\n");
    printf("\n\tNome do hóspede principal (SEM ACENTOS): ");
    fflush(stdin);
    fgets(nomePrincipal, 31, stdin);

    printf("\n\tQuantidade de hóspedes: ");
    fflush(stdin);
    fgets(numHospedes, 3, stdin);

    nomePrincipal[strcspn(nomePrincipal, "\n")] = 0;
    strcpy(open2, "Quartos/Hospedes/ArqQuartos/");
    strcat(open2, nomePrincipal);
    strcat(open2, ".txt");


    while(ok != 1)
    {
        hospede = fopen(open2, "r");
        if(hospede == NULL)
        {
            //ok para check-in
            ok = 1;
        }
        else
        {
            //já foi realizado check-in
            ok = 0;

            printf("\n\tHóspede já realizou check-in. Informe outro nome.\n");
            printf("\n\tNome do hóspede principal (SEM ACENTOS): ");
            fflush(stdin);
            fgets(nomePrincipal, 31, stdin);

            nomePrincipal[strcspn(nomePrincipal, "\n")] = 0;
            strcpy(open2, "Quartos/Hospedes/ArqQuartos/");
            strcat(open2, nomePrincipal);
            strcat(open2, ".txt");
        }
        fclose(hospede);
    }


    strcat(nomePrincipal, "\n");

    strcat(dadosQuarto, numHospedes); //Possui \n no final.

    dadosQuarto[strcspn(dadosQuarto, "\n")] = 0;

    while(encontrado != 1)
    {
        quartos = fopen(open1, "r");

        if(quartos == NULL)
        {
            printf("Falha ao abrir um arquivo.");
        }
        else
        {
            stop = 0;
            while(stop == 0)
            {
                i=0;
                while(fgets(numQuarto, 11, quartos) != NULL)
                {
                    numQuarto[strcspn(numQuarto, "\n")] = 0;

                    if(strcmp(numQuarto, dadosQuarto)==0)
                    {
                        stop = 1;

                    }
                }
                if(fgets(numQuarto, 11, quartos) == NULL && stop != 1)
                {
                    stop = 1;
                    encontrado = 0;
                    printf("\n\tQuantidade de hóspedes é diferente da capacidade do quarto.\nFavor informar outro número ou SAIR para cancelar: ");
                    fflush(stdin);
                    fgets(numHospedes, 11, stdin);
                    numHospedes[strcspn(numHospedes, "\n")] = 0;

                    strcpy(dadosQuarto, a);
                    strcat(dadosQuarto, "\t");
                    strcat(dadosQuarto, numHospedes);

                    if(strcmp(numHospedes, "SAIR")==0)
                    {
                        return 9;
                    }
                }
                else
                {
                    encontrado = 1;
                }
                fclose(quartos);
            }
        }
    }
    fclose(quartos);


    strcpy(fileRoom2, a);
    strcpy(fileRoom, "Quartos/Count_CheckIn/");
    strcat(fileRoom, fileRoom2);
    strcat(fileRoom, ".txt");

    quartos = fopen(fileRoom, "a");

    if(quartos == NULL)
    {
        printf("Falha ao abrir arquivo.");
    }
    else
    {
        fprintf(quartos, "%c", contador);
    }
    fclose(quartos);


    for(i=0 ; i<strlen(nomePrincipal) ; i++)
    {
        if(nomePrincipal[i] == ' ')
        {
            nomePrincipal[i] = '_';
        }
    }

    nomePrincipal[strcspn(nomePrincipal, "\n")] = 0;

    strcpy(fileRoom2, nomePrincipal);
    strcpy(fileRoom, "Quartos/Hospedes/");
    strcat(fileRoom, fileRoom2);
    strcat(fileRoom, ".txt");


    hospedesGeral = fopen("Quartos/Hospedes/AllGuests.txt", "a");
    hospede = fopen(fileRoom, "r");

    if(hospede == NULL)
    {
        strcat(nomePrincipal, "\n");
        fprintf(hospedesGeral, "%s", nomePrincipal);
    }
    else
    {
        fprintf(hospede, "%c", contador);
    }
    fclose(hospede);
    fclose(hospedesGeral);

    hospede = fopen(fileRoom, "a");

    if(hospede == NULL)
    {
        printf("Falha ao abrir arquivo de usuário.");
    }
    else
    {
        fprintf(hospede, "%c", contador);
    }
    fclose(hospede);


    nomePrincipal[strcspn(nomePrincipal, "\n")] = 0;

    //Este programa foi desenvolvido por Mateus C. F. Oliveira

    strcpy(arqQuartos, "Quartos/Hospedes/ArqQuartos/");
    strcat(arqQuartos, nomePrincipal);
    strcat(arqQuartos, ".txt");

    reg_hospede = fopen(arqQuartos, "w");

    if(reg_hospede == NULL)
    {
        printf("Falha ao abrir arquivo.");
    }
    else
    {
        fprintf(reg_hospede, "%s", a);
    }

    fclose(reg_hospede);

    contarCheckIn();

    return 0;
}

int consultaGeral() //OK
{

    FILE *ocupados;
    FILE *desocupados;
    FILE *tmpFile;

    char numero[20];
    char checkin_number[11];
    char aux[20];
    char numQuarto[20];
    char *outFile = "Quartos/tmp.txt";
    char line[20];

    int i;
    int encontrado;
    int stop;
    int countLine;
    int c;
    int choice;

    system("cls");

    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");
    desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");

    if(ocupados == NULL || desocupados == NULL)
    {
        printf("Falha ao abrir um dos arquivos.");
    }
    else
    {
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("                          ||                  FELIPPE'S HOTEL                     ||\n");
        printf("                          ||                                                      ||\n");
        printf("                          ||                  CONSULTA  GERAL                     ||\n");
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n\n");
        printf("                                                 [Ocupados]\n\n");

        while(fgets(numero, 11, ocupados) != NULL)
        {
            numero[strcspn(numero, "\n")] = 0;

            printf("\t%s", numero);
            i++;
            if(i==8)
            {
                printf("\n");
                i=0;
            }
        }
        fclose(ocupados);

        printf("\n                                               [Desocupados]\n\n");

        while(fgets(numero, 11, desocupados) != NULL)
        {
            numero[strcspn(numero, "\n")] = 0;

            printf("\t%s", numero);
            i++;
            if(i==8)
            {
                printf("\n");
                i=0;
            }
        }
        fclose(desocupados);
    }

    printf("\n\nEscolha um quarto desocupado para realizar o Check-In: ");
    fflush(stdin);
    fgets(checkin_number, 11, stdin);
    checkin_number[strcspn(checkin_number, "\n")] = 0;

    if(strcmp(checkin_number, "SAIR")==0)
    {
        return 9;
    }
    else
    {
        while(encontrado != 1)
        {
            desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");

            if(desocupados == NULL)
            {
                printf("Falha ao abrir um dos arquivos.");
            }
            else
            {
                stop = 0;
                while(stop == 0)
                {
                    i=0;
                    while(fgets(numQuarto, 11, desocupados) != NULL)
                    {
                        numQuarto[strcspn(numQuarto, "\n")] = 0;

                        if(strcmp(numQuarto, checkin_number)==0)
                        {
                            stop = 1;
                        }
                    }
                    if(fgets(numQuarto, 11, desocupados) == NULL && stop != 1)
                    {
                        stop = 1;
                        encontrado = 0;
                        printf("\n\tQuarto informado não está desocupado ou não existe. Favor informar outro número: ");
                        fflush(stdin);
                        fgets(checkin_number, 11, stdin);
                        checkin_number[strcspn(checkin_number, "\n")] = 0;

                        if(strcmp(checkin_number, "SAIR")==0)
                        {
                            return 9;
                        }
                    }
                    else
                    {
                        choice = DadosHospede(checkin_number); //Pede os dados do hóspede que ficará no quarto escolhido.
                        if(choice != 0)
                        {
                            return 1;
                        }
                        else
                        {
                            encontrado = 1;
                        }
                    }
                }
            }
            fclose(desocupados);
        }

        desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");
        stop = 0;
        countLine = 0;
        while(stop == 0)
        {

            i=0;
            memset(aux, 0, sizeof(aux));
            while((c = fgetc(desocupados)) != EOF && (char) c != '\t' && (char) c != '\n')
            {
                aux[i++] = (char) c;
            }
            if(strcmp(aux, checkin_number)==0)
            {
                stop = 1;
            }
            countLine++;
        }
        fclose(desocupados);//FECHA ARQUIVO GERAL DOS QUARTOS


        desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");//ABRE ARQUIVO DOS QUARTOS DESOCUPADOS
        ocupados = fopen("Quartos/QuartosOcupados.txt", "a");//ABRE ARQUIVO DOS QUARTOS OCUPADOS
        tmpFile =  fopen(outFile, "w+");//ABRE ARQUIVO TEMPORÁRIO

        if(desocupados == NULL && tmpFile == NULL)
        {
            printf("Falha ao abrir um dos arquivos.\n");
        }
        else
        {
            i=1;
            while(fgets(line, 20, desocupados) != NULL)
            {
                if(i != countLine)
                {
                    fprintf(tmpFile, "%s", line);
                }
                else
                {
                    fprintf(ocupados, "%s", line);
                }
                i++;
            }
        }
        fclose(tmpFile);//FECHA ARQUIVO TEMPORÁRIO
        fclose(ocupados);//FECHA ARQUIVO DOS QUARTOS OCUPADOS
        fclose(desocupados);//FECHA ARQUIVO DOS QUARTOS DESOCUPADOS

        if(remove("Quartos/QuartosDesocupados.txt") != 0)
        {
            printf("Arquivo não deletado\n");
            system("pause");
        }
        if(rename(outFile, "Quartos/QuartosDesocupados.txt") != 0 )
        {
            printf("Erro ao renomear arquivo.\n");
            system("pause");
        }
    }//END-ELSE

    return 0;
}

int consultaporquantidade() //OK
{

    FILE *quartos;
    FILE *desocupados;
    FILE *ocupados;
    FILE *tmpFile;

    char *open = "Quartos/Quartos.txt";
    char *outFile = "Quartos/tmp.txt";
    char qtdHospedes[11];
    char room[11];
    char roomD[11];
    char qtdQuarto[11];
    char numQuarto[11];
    char checkin_number[20];
    char aux[20];
    char line[20];

    int i, j, pulalinha;
    int existe = 0;
    int encontrado;
    int stop;
    int choice;
    int countLine;
    int c;
    int existeBackup = 0;


    printf("\n                                     Informe a quantidade de hóspedes: ");
    fflush(stdin);
    fgets(qtdHospedes, 11, stdin);
    qtdHospedes[strcspn(qtdHospedes, "\n")] = 0;

    while(existeBackup == 0)
    {
        if(strcmp(qtdHospedes, "SAIR")==0)
        {
            return 9;
        }
        else
        {
            system("cls");
            printf("\n                              Quartos desocupados com capacidade para %s pessoas:\n\n", qtdHospedes);

            quartos = fopen(open, "r");

            if(quartos == NULL)
            {
                printf("Falha ao abrir arquivo dos quartos.");
            }
            else
            {
                while(fgets(room, 11, quartos) != NULL)
                {
                    if(strcmp(room, "fixo\tfixo\n")==0)
                    {
                        //ignorar
                    }
                    else
                    {
                        memset(numQuarto, 0, sizeof(numQuarto));
                        for(i = 0 ; i<strcspn(room, "\t") ; i++)
                        {
                            numQuarto[i] = room[i];
                        }

                        j=0;
                        memset(qtdQuarto, 0, sizeof(qtdQuarto));
                        for(i = strlen(room)-2 ; i>strcspn(room, "\t") ; i--)
                        {
                            qtdQuarto[j] = room[i];
                            j++;
                        }

                        if(strlen(qtdQuarto)>=2)
                        {
                            strcpy(aux, qtdQuarto);
                            //*********************************INVERTER A STRING PARA EVITAR ESPELHAMENTO DE CARACTERES QUANDO A CAPACIDADE DO QUARTO FOR >= 10*******************************************
                            j=0;
                            for(i = strlen(qtdQuarto)-1 ; i>=0 ; i--)
                            {
                                qtdQuarto[j] = aux[i];
                                j++;
                            }
                            //****************************************************************************************************************************************************************************
                        }

                        existe = 0;
                        if(strcmp(qtdHospedes, qtdQuarto)==0)
                        {
                            strcat(numQuarto, "\n");
                            desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");
                            while(fgets(roomD, 11, desocupados) != NULL)
                            {
                                if(strcmp(roomD, numQuarto)==0)
                                {
                                    //Quarto está desocupado. Pode mostrar na tela.
                                    numQuarto[strcspn(numQuarto, "\n")] = 0;
                                    printf("\t%s", numQuarto);
                                    pulalinha++;
                                    if(pulalinha==11)
                                    {
                                        printf("\n");
                                        pulalinha=0;
                                    }
                                    existe++;
                                }
                            }
                            fclose(desocupados);
                        }
                        existeBackup = existeBackup + existe;
                    }
                }
                fclose(quartos);
            }
            printf("\n\n\n");
            if(existeBackup == 0)
            {
                printf("\n                             Não existem quartos disponíveis com essa capacidade.\n\n\n");

                printf("\n                                     Informe a quantidade de hóspedes: ");
                fflush(stdin);
                fgets(qtdHospedes, 11, stdin);
                qtdHospedes[strcspn(qtdHospedes, "\n")] = 0;
            }
        }
    }

    //****************************************************************************FAZER CHECK-IN*********************************************************************************************

    printf("\n\nEscolha um quarto para realizar o Check-In: ");
    fflush(stdin);
    fgets(checkin_number, 11, stdin);
    checkin_number[strcspn(checkin_number, "\n")] = 0;

    if(strcmp(checkin_number, "SAIR")==0)
    {
        return 9;
    }
    else
    {
        while(encontrado != 1)
        {
            desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");

            if(desocupados == NULL)
            {
                printf("Falha ao abrir um dos arquivos.");
            }
            else
            {
                stop = 0;
                while(stop == 0)
                {
                    i=0;
                    while(fgets(numQuarto, 11, desocupados) != NULL)
                    {
                        numQuarto[strcspn(numQuarto, "\n")] = 0;

                        if(strcmp(numQuarto, checkin_number)==0)
                        {
                            stop = 1;
                        }
                    }
                    if(fgets(numQuarto, 11, desocupados) == NULL && stop != 1)
                    {
                        stop = 1;
                        encontrado = 0;
                        printf("\n\tQuarto informado não está desocupado ou não existe. Favor informar outro número: ");
                        fflush(stdin);
                        fgets(checkin_number, 11, stdin);
                        checkin_number[strcspn(checkin_number, "\n")] = 0;

                        if(strcmp(checkin_number, "SAIR")==0)
                        {
                            return 9;
                        }
                    }
                    else
                    {
                        choice = DadosHospede(checkin_number); //Pede os dados do hóspede que ficará no quarto escolhido.
                        if(choice != 0)
                        {
                            return 1;
                        }
                        else
                        {
                            encontrado = 1;
                        }
                    }
                    //*****************************************************************************************************************
                }
            }
            fclose(desocupados);
        }

        desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");
        stop = 0;
        countLine = 0;
        while(stop == 0)
        {

            i=0;
            memset(aux, 0, sizeof(aux));
            while((c = fgetc(desocupados)) != EOF && (char) c != '\t' && (char) c != '\n')
            {
                aux[i++] = (char) c;
            }
            if(strcmp(aux, checkin_number)==0)
            {
                stop = 1;
            }
            countLine++;
        }
        fclose(desocupados);


        desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");//ABRE ARQUIVO DOS QUARTOS DESOCUPADOS
        ocupados = fopen("Quartos/QuartosOcupados.txt", "a");//ABRE ARQUIVO DOS QUARTOS OCUPADOS
        tmpFile =  fopen(outFile, "w+");//ABRE ARQUIVO TEMPORÁRIO

        if(desocupados == NULL && tmpFile == NULL)
        {
            printf("Falha ao abrir um dos arquivos.\n");
        }
        else
        {
            i=1;
            while(fgets(line, 20, desocupados) != NULL)
            {
                if(i != countLine)
                {
                    fprintf(tmpFile, "%s", line);
                }
                else
                {
                    fprintf(ocupados, "%s", line);
                }
                i++;
            }
        }
        fclose(tmpFile);//FECHA ARQUIVO TEMPORÁRIO
        fclose(ocupados);//FECHA ARQUIVO DOS QUARTOS OCUPADOS
        fclose(desocupados);//FECHA ARQUIVO DOS QUARTOS DESOCUPADOS

        if(remove("Quartos/QuartosDesocupados.txt") != 0)
        {
            printf("Arquivo não deletado\n");
            system("pause");
        }
        if(rename(outFile, "Quartos/QuartosDesocupados.txt") != 0 )
        {
            printf("Erro ao renomear arquivo.\n");
            system("pause");
        }
    }//END-ELSE

    return 0;
}

int checkIn() //OK
{

    int choice=0;

    char UserChoice[3] = "";

    system("cls");

    while(choice == 0)
    {
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("                          ||                     FELIPPE'S HOTEL                   ||\n");
        printf("                          ||                                                       ||\n");
        printf("                          ||                        CHECK-IN                       ||\n");
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
        printf("                                        [1] - Consulta Geral\n");
        printf("                                        [2] - Consulta por quantidade de pessoas\n");
        printf("                                        [3] - Retornar ao Menu do Funcionário\n");
        printf("                                         ");
        fflush(stdin);
        fgets(UserChoice, 2, stdin); //Pegar entrada como "char" para evitar loop indevido caso usuário digite uma letra ao invés de um "int".
        UserChoice[strcspn(UserChoice, "\n")] = 0; //Eliminar \n da string.
        if(strcmp(UserChoice, "0")!=0 && strcmp(UserChoice, "1")!=0 && strcmp(UserChoice, "2")!=0 && strcmp(UserChoice, "3")!=0)
        {
            system("cls");
            printf("                                                Opção inválida.\n\n");
        }
        else
        {
            if(strcmp(UserChoice, "1")==0)
            {
                choice = 1;
            }
            else if(strcmp(UserChoice, "2")==0)
            {
                choice = 2;
            }
            else if(strcmp(UserChoice, "3")==0)
            {
                choice = 3;
            }
        }
    }

    switch(choice)
    {
    case 1:
        choice = consultaGeral();
        if(choice == 9)
        {
            system("cls");
            checkIn();
        }
        system("cls");
        printf("\n                                          Check-In Realizado!\n\n");

        break;
    case 2:
        choice = consultaporquantidade();
        if(choice == 9)
        {
            system("cls");
            checkIn();
        }
        system("cls");
        printf("\n                                          Check-In Realizado!\n\n");
        break;
    case 3:
        system("cls");
        return 3;
        break;
    default:
        choice = 0;
    }

    return 0;
}

int co_PorNome() //OK
{

    FILE *reg_hospede;
    FILE *ocupados;
    FILE *desocupados;
    FILE *tmpFile;

    char *outFile = "Quartos/tmp.txt";
    char nomeHospede[50];
    char openfile[50];
    char numQuarto[20];
    char checkin_number[20];
    char room[10];
    char aux[50];
    char line[20];

    int encontrado;
    int stop;
    int i, c;
    int countLine;

    while(encontrado != 1)
    {
        if(strcmp(nomeHospede, "SAIR")==0)
        {
            return 9;
        }
        else
        {
            printf("\tInforme o nome do hóspede (exatamente como informado no check-in): ");
            fflush(stdin);
            fgets(nomeHospede, 31, stdin);
            nomeHospede[strcspn(nomeHospede, "\n")] = 0;


            strcpy(openfile, "Quartos/Hospedes/ArqQuartos/");
            strcat(openfile, nomeHospede);

            strcat(openfile, ".txt");

            reg_hospede = fopen(openfile, "r");

            if(reg_hospede == NULL)
            {
                printf("\n\tHóspede não encontrado.\n\n");
            }
            else
            {
                fgets(room, 10, reg_hospede);
                strcpy(checkin_number, room);
                encontrado = 1;
            }
        }
    }
    fclose(reg_hospede);



    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");
    stop = 0;
    countLine = 0;
    while(stop == 0)
    {
        i=0;
        memset(aux, 0, sizeof(aux));
        while((c = fgetc(ocupados)) != EOF && (char) c != '\t' && (char) c != '\n')
        {
            aux[i++] = (char) c;
        }
        if(strcmp(aux, checkin_number)==0)
        {
            stop = 1;
        }
        countLine++;
    }
    fclose(ocupados);//FECHA ARQUIVO GERAL DOS QUARTOS


    desocupados = fopen("Quartos/QuartosDesocupados.txt", "a");//ABRE ARQUIVO DOS QUARTOS DESOCUPADOS
    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");//ABRE ARQUIVO DOS QUARTOS OCUPADOS
    tmpFile =  fopen(outFile, "w+");//ABRE ARQUIVO TEMPORÁRIO

    if(ocupados == NULL && tmpFile == NULL && desocupados == NULL)
    {
        printf("Falha ao abrir um dos arquivos.\n");
    }
    else
    {
        i=1;
        while(fgets(line, 20, ocupados) != NULL)
        {
            if(i != countLine)
            {
                fprintf(tmpFile, "%s", line);
            }
            else
            {
                fprintf(desocupados, "%s", line);
            }
            i++;
        }
    }
    fclose(tmpFile);//FECHA ARQUIVO TEMPORÁRIO
    fclose(ocupados);//FECHA ARQUIVO DOS QUARTOS OCUPADOS
    fclose(desocupados);//FECHA ARQUIVO DOS QUARTOS DESOCUPADOS

    if(remove("Quartos/QuartosOcupados.txt") != 0)
    {
        printf("Arquivo não deletado\n");
        system("pause");
    }
    if(rename(outFile, "Quartos/QuartosOcupados.txt") != 0 )
    {
        printf("Erro ao renomear arquivo.\n");
        system("pause");
    }

    if(remove(openfile) != 0)
    {
        printf("Arquivo não deletado\n");
        system("pause");
    }

    return 0;
}

int co_PorNumero() //OK
{

    FILE *reg_hospede;
    FILE *reg_quarto;
    FILE *ocupados;
    FILE *desocupados;
    FILE *tmpFile;

    char *outFile = "Quartos/tmp.txt";
    char openfile[50];
    char nomeHospede[50];
    char nomeHospede2[50];
    char nomeHospede_verificar[50];
    char numQuarto[11];
    char entraQuarto[11];
    char aux[20];
    char line[20];

    int encontrado=0;
    int i, c;
    int stop=0;
    int countLine=0;


    printf("\tInforme número do quarto para check-out: ");
    fflush(stdin);
    fgets(entraQuarto, 11, stdin);
    entraQuarto[strcspn(entraQuarto, "\n")] = 0;

    while(encontrado != 1)
    {
        if(strcmp(entraQuarto, "SAIR")==0)
        {
            return 9;
        }
        else
        {

            reg_hospede = fopen("Quartos/Hospedes/AllGuests.txt", "r");

            if(reg_hospede == NULL)
            {
                printf("Falha ao abrir arquivo.");
            }
            else
            {
                while(fgets(nomeHospede_verificar, 31, reg_hospede) != NULL && stop != 1)
                {
                    strcpy(nomeHospede, nomeHospede_verificar);
                    nomeHospede[strcspn(nomeHospede, "\n")] = 0;
                    strcpy(nomeHospede2,"Quartos/Hospedes/ArqQuartos/");
                    strcat(nomeHospede2, nomeHospede);
                    strcat(nomeHospede2, ".txt");

                    reg_quarto = fopen(nomeHospede2, "r");
                    if(reg_quarto == NULL)
                    {
                        //ignorar.
                    }
                    else
                    {
                        fgets(numQuarto, 11, reg_quarto);
                        if(strcmp(entraQuarto, numQuarto)==0)
                        {
                            stop = 1;
                            encontrado = 1;
                        }
                    }
                }

                if (fgets(nomeHospede, 11, reg_quarto) == NULL && stop == 0)
                {
                    printf("\tQuarto não encontrado. Informe número do quarto para check-out: ");
                    fflush(stdin);
                    fgets(entraQuarto, 11, stdin);
                    entraQuarto[strcspn(entraQuarto, "\n")] = 0;
                    encontrado = 0;

                    if(strcmp(entraQuarto, "SAIR")==0)
                    {
                        return 9;
                    }
                }
                fclose(reg_quarto);
                fclose(reg_hospede);
            }
        }
    }

    //Fazer check-out


    printf("\n\n\tCheck-out de [%s] em andamento. \n", nomeHospede);
    printf("\t");
    system("pause");

    strcpy(openfile, "Quartos/Hospedes/ArqQuartos/");
    strcat(openfile, nomeHospede);
    strcat(openfile, ".txt");

    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");
    stop = 0;
    countLine = 0;
    while(stop == 0)
    {
        i=0;
        memset(aux, 0, sizeof(aux));
        while((c = fgetc(ocupados)) != EOF && (char) c != '\n')
        {
            aux[i++] = (char) c;
        }
        if(strcmp(aux, entraQuarto)==0)
        {
            stop = 1;
        }
        countLine++;
    }
    fclose(ocupados);//FECHA ARQUIVO GERAL DOS QUARTOS


    desocupados = fopen("Quartos/QuartosDesocupados.txt", "a");//ABRE ARQUIVO DOS QUARTOS DESOCUPADOS
    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");//ABRE ARQUIVO DOS QUARTOS OCUPADOS
    tmpFile =  fopen(outFile, "w+");//ABRE ARQUIVO TEMPORÁRIO

    if(ocupados == NULL && tmpFile == NULL && desocupados == NULL)
    {
        printf("Falha ao abrir um dos arquivos.\n");
    }
    else
    {
        i=1;
        while(fgets(line, 20, ocupados) != NULL)
        {
            if(i != countLine)
            {
                fprintf(tmpFile, "%s", line);
            }
            else
            {
                fprintf(desocupados, "%s", line);
            }
            i++;
        }
    }
    fclose(tmpFile);//FECHA ARQUIVO TEMPORÁRIO
    fclose(ocupados);//FECHA ARQUIVO DOS QUARTOS OCUPADOS
    fclose(desocupados);//FECHA ARQUIVO DOS QUARTOS DESOCUPADOS

    if(remove("Quartos/QuartosOcupados.txt") != 0)
    {
        printf("Arquivo não deletado\n");
        system("pause");
    }
    if(rename(outFile, "Quartos/QuartosOcupados.txt") != 0 )
    {
        printf("Erro ao renomear arquivo.\n");
        system("pause");
    }

    if(remove(openfile) != 0)
    {
        printf("Arquivo não deletado\n");
        system("pause");
    }

    return 0;
}

int co_Geral() //OK
{
    FILE *ocupados;
    FILE *desocupados;
    FILE *tmpFile;
    FILE *reg_hospede;
    FILE *reg_quarto;

    char *outFile = "Quartos/tmp.txt";
    char openfile[50];
    char numero[20];
    char checkout_number[20];
    char numQuarto[20];
    char aux[20];
    char line[20];
    char nomeHospede[50];
    char nomeHospede2[50];
    char nomeHospede_verificar[50];

    int i, c, stop;
    int encontrado;
    int countLine;


    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");

    printf("\n                                               [Ocupados]\n\n");

    while(fgets(numero, 11, ocupados) != NULL)
    {
        numero[strcspn(numero, "\n")] = 0;

        printf("\t%s", numero);
        i++;
        if(i==8)
        {
            printf("\n");
            i=0;
        }
    }
    fclose(ocupados);


    printf("\n\nEscolha um quarto ocupados para realizar o Check-Out: ");
    fflush(stdin);
    fgets(checkout_number, 11, stdin);
    checkout_number[strcspn(checkout_number, "\n")] = 0;

    if(strcmp(checkout_number, "SAIR")==0)
    {
        return 9;
    }
    else
    {
        while(encontrado != 1)
        {
            stop = 0;
            while(stop == 0)
            {
                ocupados = fopen("Quartos/QuartosOcupados.txt", "r");
                if(ocupados == NULL)
                {
                    printf("Falha ao abrir arquivo.");
                }
                else
                {
                    while(fgets(numQuarto, 11, ocupados) != NULL && stop != 1)
                    {
                        numQuarto[strcspn(numQuarto, "\n")] = 0;

                        if(strcmp(numQuarto, checkout_number)==0)
                        {
                            stop = 1;
                            encontrado = 1;
                        }
                    }
                    if(fgets(numQuarto, 11, ocupados) == NULL && stop != 1)
                    {
                        stop = 1;
                        encontrado = 0;

                        printf("\n\tQuarto informado não está ocupado ou não existe. Favor informar outro número: ");
                        fflush(stdin);
                        fgets(checkout_number, 11, stdin);
                        checkout_number[strcspn(checkout_number, "\n")] = 0;

                        if(strcmp(checkout_number, "SAIR")==0)
                        {
                            return 9;
                        }
                    }
                    //*****************************************************************************************************************
                    fclose(ocupados);
                }
            }
        }


        encontrado = 0;
        stop = 0;
        while(encontrado == 0)
        {
            reg_hospede = fopen("Quartos/Hospedes/AllGuests.txt", "r");

            if(reg_hospede == NULL)
            {
                printf("Falha ao abrir arquivo.");
            }
            else
            {
                while(fgets(nomeHospede_verificar, 31, reg_hospede) != NULL && stop != 1)
                {
                    strcpy(nomeHospede, nomeHospede_verificar);
                    nomeHospede[strcspn(nomeHospede, "\n")] = 0;
                    strcpy(nomeHospede2,"Quartos/Hospedes/ArqQuartos/");
                    strcat(nomeHospede2, nomeHospede);
                    strcat(nomeHospede2, ".txt");

                    reg_quarto = fopen(nomeHospede2, "r");
                    if(reg_quarto == NULL)
                    {
                        //ignorar.
                    }
                    else
                    {
                        fgets(numQuarto, 11, reg_quarto);
                        if(strcmp(checkout_number, numQuarto)==0)
                        {
                            stop = 1;
                            encontrado = 1;
                        }
                    }
                }
                fclose(reg_quarto);
                fclose(reg_hospede);
            }
        }
    }

    //Fazer check-out
    printf("\n\n\tCheck-out de [%s] em andamento. \n", nomeHospede);
    printf("\t");
    system("pause");



    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");
    stop = 0;
    countLine = 0;
    while(stop == 0)
    {
        i=0;
        memset(aux, 0, sizeof(aux));
        while((c = fgetc(ocupados)) != EOF && (char) c != '\t' && (char) c != '\n')
        {
            aux[i++] = (char) c;
        }
        if(strcmp(aux, checkout_number)==0)
        {
            stop = 1;
        }
        countLine++;
    }
    fclose(ocupados);


    desocupados = fopen("Quartos/QuartosDesocupados.txt", "a");//ABRE ARQUIVO DOS QUARTOS DESOCUPADOS
    ocupados = fopen("Quartos/QuartosOcupados.txt", "r");//ABRE ARQUIVO DOS QUARTOS OCUPADOS
    tmpFile =  fopen(outFile, "w+");//ABRE ARQUIVO TEMPORÁRIO

    if(ocupados == NULL && tmpFile == NULL && desocupados == NULL)
    {
        printf("Falha ao abrir um dos arquivos.\n");
    }
    else
    {
        i=1;
        while(fgets(line, 20, ocupados) != NULL)
        {
            if(i != countLine)
            {
                fprintf(tmpFile, "%s", line);
            }
            else
            {
                fprintf(desocupados, "%s", line);
            }
            i++;
        }
    }
    fclose(tmpFile);
    fclose(ocupados);
    fclose(desocupados);
    fclose(tmpFile);
    fclose(ocupados);
    fclose(desocupados);

    if(remove("Quartos/QuartosOcupados.txt") != 0)
    {
        printf("Arquivo não deletado\n");
        system("pause");
    }
    if(rename(outFile, "Quartos/QuartosOcupados.txt") != 0 )
    {
        printf("Erro ao renomear arquivo.\n");
        system("pause");
    }

    strcpy(openfile, "Quartos/Hospedes/ArqQuartos/");
    strcat(openfile, nomeHospede);
    strcat(openfile, ".txt");

    if(remove(openfile) != 0)
    {
        printf("Arquivo não deletado\n");
        system("pause");
    }

    return 0;
}

int checkOut() //OK
{

    int choice=0;

    char UserChoice[3] = "";

    system("cls");

    while(choice == 0)
    {
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("                          ||                    FELIPPE'S HOTEL                    ||\n");
        printf("                          ||                                                       ||\n");
        printf("                          ||                       CHECK-OUT                       ||\n");
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
        printf("                                        [1] - Check-out por nome\n");
        printf("                                        [2] - Check-out por número do quarto\n");
        printf("                                        [3] - Check-out Geral\n");
        printf("                                        [4] - Retornar ao Menu do Funcionário\n");
        printf("                                         ");
        fflush(stdin);
        fgets(UserChoice, 2, stdin); //Pegar entrada como "char" para evitar loop indevido caso usuário digite uma letra ao invés de um "int".
        UserChoice[strcspn(UserChoice, "\n")] = 0; //Eliminar \n da string.
        if(strcmp(UserChoice, "0")!=0 && strcmp(UserChoice, "1")!=0 && strcmp(UserChoice, "2")!=0 && strcmp(UserChoice, "3")!=0 && strcmp(UserChoice, "4")!=0)
        {
            system("cls");
            printf("                                                Opção inválida.\n\n");
        }
        else
        {
            if(strcmp(UserChoice, "1")==0)
            {
                choice = 1;
            }
            else if(strcmp(UserChoice, "2")==0)
            {
                choice = 2;
            }
            else if(strcmp(UserChoice, "3")==0)
            {
                choice = 3;
            }
            else if(strcmp(UserChoice, "4")==0)
            {
                choice = 4;
            }
        }
    }

    switch(choice)
    {
    case 1:
        choice = co_PorNome();
        if(choice == 9)
        {
            system("cls");
            checkOut();
        }
        break;
    case 2:
        choice = co_PorNumero();
        if(choice == 9)
        {
            system("cls");
            checkOut();
        }
        break;
    case 3:
        choice = co_Geral();
        if(choice == 9)
        {
            system("cls");
            checkOut();
        }
        break;
    case 4:
        system("cls");
        return 3;
        break;
    default:
        choice = 0;
    }

    return 0;
}

int quarto_maisCheckIn() //OK
{

    FILE *quartoCheckIn;
    FILE *open;

    char numQuarto[11];
    char fileQuarto[30];
    char maior[11];

    int i, c, j;
    int contador = 0;


    open = fopen("Quartos/QuartosDesocupados.txt", "r");
    i=0;
    j=0;
    while(fgets(numQuarto, 11, open) != NULL)
    {
        numQuarto[strcspn(numQuarto, "\n")] = 0;

        strcpy(fileQuarto, "Quartos/Count_CheckIn/");
        strcat(fileQuarto, numQuarto);
        strcat(fileQuarto, ".txt");

        quartoCheckIn = fopen(fileQuarto, "r");

        i=0;
        while((c = fgetc(quartoCheckIn)) != EOF)
        {
            i++;
        }

        fclose(quartoCheckIn);

        if(j==0)
        {
            strcpy(maior, numQuarto);
            contador = i;
        }
        else
        {
            if(i>contador)
            {
                strcpy(maior, numQuarto);
                contador = i;
            }
        }
        j=1;
    }
    fclose(open);


    open = fopen("Quartos/QuartosOcupados.txt", "r");

    i=0;
    j=0;
    while(fgets(numQuarto, 11, open) != NULL)
    {
        numQuarto[strcspn(numQuarto, "\n")] = 0;

        strcpy(fileQuarto, "Quartos/Count_CheckIn/");
        strcat(fileQuarto, numQuarto);
        strcat(fileQuarto, ".txt");

        quartoCheckIn = fopen(fileQuarto, "r");

        i=0;
        while((c = fgetc(quartoCheckIn)) != EOF)
        {
            i++;
        }

        fclose(quartoCheckIn);

        if(j==0)
        {
            strcpy(maior, numQuarto);
        }
        else
        {
            if(i>contador)
            {
                strcpy(maior, numQuarto);
                contador = i;
            }
        }
        j=1;
    }

    fclose(open);

    printf("\n\n                                    O quarto com mais check-in foi o [%s].\n\n\n", maior);
    printf("\t\t\t\t");
    system("pause");

    return 0;
}

int MaiorQuarto() //OK
{

    FILE *quartos;

    char line[20];
    char capacidade[20];
    char aux[20];
    char maior[20];
    char numQuarto[20];

    int j, i;
    int qtdHospedes;
    int contador = 0;




    quartos = fopen("Quartos/Quartos.txt", "r");
    while(fgets(line, 11, quartos) != NULL)
    {
        if(strcmp(line, "fixo\tfixo\n")==0)
        {
            //ignorar
        }
        else
        {
            memset(numQuarto, 0, sizeof(numQuarto));
            for(i = 0 ; i<strcspn(line, "\t") ; i++)
            {
                numQuarto[i] = line[i];
            }
            j=0;
            memset(capacidade, 0, sizeof(capacidade));
            for(i = strlen(line)-2 ; i>strcspn(line, "\t") ; i--)
            {
                capacidade[j] = line[i];
                j++;
            }

            if(strlen(capacidade)>=2)
            {
                strcpy(aux, capacidade);
                //*********************************INVERTER A STRING PARA EVITAR ESPELHAMENTO DE CARACTERES QUANDO A CAPACIDADE DO QUARTO FOR >= 10*******************************************
                j=0;
                for(i = strlen(capacidade)-1 ; i>=0 ; i--)
                {
                    capacidade[j] = aux[i];
                    j++;
                }
                //****************************************************************************************************************************************************************************
            }

            capacidade[strcspn(capacidade, "\n")] = 0;
            qtdHospedes = 0;
            for(i=0; i<strlen(capacidade); i++)
            {
                qtdHospedes = qtdHospedes * 10 + (capacidade[i] - '0' ); //converte uma string para int, baseado na tabela ASCII, onde 0 representa o decimal de valor 48 e 1 = 49 ; 2 = 50 ; 3 = 51... 9 = 57.
            }

            if(qtdHospedes>contador)
            {
                strcpy(maior, numQuarto);
                contador = qtdHospedes;
            }
        }
    }

    fclose(quartos);


    printf("\n                                       Quarto com maior capacidade é o [%s]\n\n", maior);
    printf("\t\t\t\t    ");
    system("pause");

    return 0;
}

int MaiorQuartoDesocupado() //OK
{
    FILE *quartos;
    FILE *desocupados;

    char line[20];
    char capacidade[20];
    char aux[20];
    char maior[20];
    char numQuarto[20];
    char room[20];

    int j, i;
    int qtdHospedes;
    int contador = 0;
    int desocupado;
    int existe = 0;



    quartos = fopen("Quartos/Quartos.txt", "r");
    while(fgets(line, 11, quartos) != NULL)
    {
        if(strcmp(line, "fixo\tfixo\n")==0)
        {
            //ignorar
        }
        else
        {
            memset(numQuarto, 0, sizeof(numQuarto));
            for(i = 0 ; i<strcspn(line, "\t") ; i++)
            {
                numQuarto[i] = line[i];
            }
            desocupados = fopen("Quartos/QuartosDesocupados.txt", "r");
            while(fgets(room, 11, desocupados) != NULL)
            {
                room[strcspn(room, "\n")] = 0;
                if(strcmp(room, numQuarto)==0)
                {
                    desocupado = 1;

                }
            }
            fclose(desocupados);

            if(desocupado == 1)
            {
                j=0;
                memset(capacidade, 0, sizeof(capacidade));
                for(i = strlen(line)-2 ; i>strcspn(line, "\t") ; i--)
                {
                    capacidade[j] = line[i];
                    j++;
                }

                if(strlen(capacidade)>=2)
                {
                    strcpy(aux, capacidade);
                    //*********************************INVERTER A STRING PARA EVITAR ESPELHAMENTO DE CARACTERES QUANDO A CAPACIDADE DO QUARTO FOR >= 10*******************************************
                    j=0;
                    for(i = strlen(capacidade)-1 ; i>=0 ; i--)
                    {
                        capacidade[j] = aux[i];
                        j++;
                    }
                    //****************************************************************************************************************************************************************************
                }

                capacidade[strcspn(capacidade, "\n")] = 0;
                qtdHospedes = 0;
                for(i=0; i<strlen(capacidade); i++)
                {
                    qtdHospedes = qtdHospedes * 10 + (capacidade[i] - '0' ); //converte uma string para int, baseado na tabela ASCII, onde 0 representa o decimal de valor 48 e 1 = 49 ; 2 = 50 ; 3 = 51... 9 = 57.
                }

                if(qtdHospedes>contador)
                {
                    strcpy(maior, numQuarto);
                    contador = qtdHospedes;
                }

                existe++;
            }
        }
    }

    fclose(quartos);

    if(existe != 0)
    {
        printf("\n                                       Quarto com maior capacidade é o [%s]\n\n", maior);
        printf("\t\t\t\t    ");
        system("pause");
    }
    else
    {
        printf("\n                                       Todos os quartos estão ocupados.\n\n");
        printf("\t\t\t\t    ");
        system("pause");
    }

    return 0;
}

int funcionario_maisCheckIn() //OK
{

    FILE *funcionarioCheckIn;
    FILE *open;

    char nomeFunc[11];
    char fileFunc[30];
    char maior[11];

    int i, c, j;
    int contador = 0;


    open = fopen("Login/Geral_nomes.txt", "r");
    i=0;
    j=0;
    while(fgets(nomeFunc, 11, open) != NULL)
    {
        nomeFunc[strcspn(nomeFunc, "\n")] = 0;

        strcpy(fileFunc, "Login/Count_CheckIn/");
        strcat(fileFunc, nomeFunc);
        strcat(fileFunc, ".txt");

        funcionarioCheckIn = fopen(fileFunc, "r");

        i=0;
        while((c = fgetc(funcionarioCheckIn)) != EOF)
        {
            i++;
        }

        fclose(funcionarioCheckIn);

        if(j==0)
        {
            strcpy(maior, nomeFunc);
            contador = i;
        }
        else
        {
            if(i>contador)
            {
                strcpy(maior, nomeFunc);
                contador = i;
            }
        }
        j=1;
    }
    fclose(open);

    printf("\n\n                             O funcionário que mais realizou check-in foi [%s].\n\n\n", maior);
    printf("\t\t\t\t");
    system("pause");


    return 0;
}

int hospede_maisCheckIn() //OK
{

    FILE *hospedeCheckIn;
    FILE *open;

    char nomeH[11];
    char fileH[30];
    char maior[11];

    int i, c, j;
    int contador = 0;


    open = fopen("Quartos/Hospedes/AllGuests.txt", "r");
    i=0;
    j=0;
    while(fgets(nomeH, 11, open) != NULL)
    {
        nomeH[strcspn(nomeH, "\n")] = 0;

        strcpy(fileH, "Quartos/Hospedes/");
        strcat(fileH, nomeH);
        strcat(fileH, ".txt");

        hospedeCheckIn = fopen(fileH, "r");

        i=0;
        while((c = fgetc(hospedeCheckIn)) != EOF)
        {
            i++;
        }

        fclose(hospedeCheckIn);

        if(j==0)
        {
            strcpy(maior, nomeH);
            contador = i;
        }
        else
        {
            if(i>contador)
            {
                strcpy(maior, nomeH);
                contador = i;
            }
        }
        j=1;
    }
    fclose(open);

    printf("\n\n                              O hóspede que mais realizou check-in foi [%s].\n\n\n", maior);
    printf("\t\t\t\t");
    system("pause");


    return 0;
}

int relatorios() //OK
{

    int choice=0;

    char UserChoice[3] = "";

    system("cls");

    while(choice == 0)
    {
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("                          ||                    FELIPPE'S HOTEL                    ||\n");
        printf("                          ||                                                       ||\n");
        printf("                          ||                      RELATÓRIOS                       ||\n");
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
        printf("                                        [1] - Quarto que mais recebeu check-in\n");
        printf("                                        [2] - Quarto com maior capacidade\n");
        printf("                                        [3] - Quarto desocupado com maior capacidade\n");
        printf("                                        [4] - Funcionário que mais fez check-in\n");
        printf("                                        [5] - Hóspede que mais fez check-in\n");
        printf("                                        [6] - Retornar ao Menu do Funcionário\n");
        printf("                                         ");
        fflush(stdin);
        fgets(UserChoice, 2, stdin); //Pegar entrada como "char" para evitar loop indevido caso usuário digite uma letra ao invés de um "int".
        UserChoice[strcspn(UserChoice, "\n")] = 0; //Eliminar \n da string.
        if(strcmp(UserChoice, "0")!=0 && strcmp(UserChoice, "1")!=0 && strcmp(UserChoice, "2")!=0 && strcmp(UserChoice, "3")!=0
                && strcmp(UserChoice, "4")!=0 && strcmp(UserChoice, "5")!=0 && strcmp(UserChoice, "6")!=0)
        {
            system("cls");
            printf("                                                Opção inválida.\n\n");
        }
        else
        {
            if(strcmp(UserChoice, "1")==0)
            {
                choice = 1;
            }
            else if(strcmp(UserChoice, "2")==0)
            {
                choice = 2;
            }
            else if(strcmp(UserChoice, "3")==0)
            {
                choice = 3;
            }
            else if(strcmp(UserChoice, "4")==0)
            {
                choice = 4;
            }
            else if(strcmp(UserChoice, "5")==0)
            {
                choice = 5;
            }
            else if(strcmp(UserChoice, "6")==0)
            {
                choice = 6;
            }
        }
    }

    switch(choice)
    {
    case 1:
        choice = quarto_maisCheckIn();
        break;
    case 2:
        choice = MaiorQuarto();
        break;
    case 3:
        choice = MaiorQuartoDesocupado();
        break;
    case 4:
        choice = funcionario_maisCheckIn();
        break;
    case 5:
        choice = hospede_maisCheckIn();
        break;
    case 6:
        system("cls");
        return 3;
        break;
    default:
        choice = 0;
    }

    return 0;
}

void main() //OK
{
    system("color 0F"); //muda dor do prompt para fundo preto (0) e texto branco (F).
    int user_loggedIn = 0, choice=0, retornar=0;
    char UserChoice[3] = "";
    setlocale(LC_ALL,""); //Uso de caracteres especiais no comando "printf".

    while((user_loggedIn) == 0)
    {
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("                          ||                  FELIPPE'S HOTEL                      ||\n");
        printf("                          ||                                                       ||\n");
        printf("                          ||                      INÍCIO                           ||\n");
        printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
        printf("                                          [1] LOGIN   [2] FECHAR\n\n");
        printf("                                 Digite uma das opções para continuar: ");
        fflush(stdin);
        fgets(UserChoice, 2, stdin);
        UserChoice[strcspn(UserChoice, "\n")] = 0; //Eliminar \n da string.
        if(strcmp(UserChoice, "0")!=0 && strcmp(UserChoice, "1")!=0 && strcmp(UserChoice, "2") && strcmp(UserChoice, "3")!=0)
        {
            system("cls");
            printf("                                              Opção inválida.\n\n");
        }
        else
        {
            if(strcmp(UserChoice, "1")==0)
            {
                user_loggedIn = loggedIn();
            }
            else if(strcmp(UserChoice, "2")==0)
            {
                exit(0);
            }
            else if(strcmp(UserChoice, "3")==0)
            {
                system("cls");
                retornar=0;
                while(retornar == 0 )
                {
                    printf("     -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                    printf("     ||                                     FELIPPE'S HOTEL                                         ||\n");
                    printf("     ||                                                                                             ||\n");
                    printf("     ||                     Programa para simulação de gerenciamento de hotel                       ||\n");
                    printf("     ||        Desenvolvido para a disciplina de Algoritmos e Programação de Computadores           ||\n");
                    printf("     ||                                                                                             ||\n");
                    printf("     ||                          Autor: Mateus Cavalcanti Félix Oliveira                            ||\n");
                    printf("     ||                          1º Semestre - Engenharia da Computação                             ||\n");
                    printf("     ||                                                                                             ||\n");
                    printf("     ||                     Instituto de Educação Superior de Brasília - IESB                       ||\n");
                    printf("     ||                                           2016                                              ||\n");
                    printf("     -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");


                    printf("                                   [1] - Retornar à tela de Início ");
                    fflush(stdin);
                    fgets(UserChoice, 2, stdin);
                    UserChoice[strcspn(UserChoice, "\n")] = 0;
                    if(strcmp(UserChoice, "1")!=0)
                    {
                        system("cls");
                        printf("Opção inválida.\n\n");
                        retornar=0;
                    }
                    else
                    {
                        system("cls");
                        retornar = 1;
                    }
                }
            }
        }
    }

    system("cls");
    if(user_loggedIn == 2)
    {
        while(user_loggedIn == 2)
        {
            system("color F0"); //muda dor do prompt para fundo branco (F) e texto preto (0).
            //Menu do admin
            while(choice == 0)
            {
                printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                printf("                          ||                     FELIPPE'S HOTEL                   ||\n");
                printf("                          ||                                                       ||\n");
                printf("                          ||                  MENU DO ADMINISTRADOR                ||\n");
                printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
                printf("                                        [1] - Cadastrar funcionário\n");
                printf("                                        [2] - Remover funcionário\n");
                printf("                                        [3] - Adicionar quarto\n");
                printf("                                        [4] - Remover quarto\n");
                printf("                                        [5] - Log-out\n");
                printf("                                         ");
                fflush(stdin);
                fgets(UserChoice, 2, stdin); //Pegar entrada como "char" para evitar loop indevido caso usuário digite uma letra ao invés de um "int".
                UserChoice[strcspn(UserChoice, "\n")] = 0; //Eliminar \n da string.
                if(strcmp(UserChoice, "0")!=0 && strcmp(UserChoice, "1")!=0 && strcmp(UserChoice, "2")!=0 && strcmp(UserChoice, "3")!=0 && strcmp(UserChoice, "4")!=0 && strcmp(UserChoice, "5")!=0)
                {
                    system("cls");
                    printf("                                            Opção inválida.\n\n");
                }
                else
                {
                    if(strcmp(UserChoice, "1")==0)
                    {
                        choice = 1;
                    }
                    else if(strcmp(UserChoice, "2")==0)
                    {
                        choice = 2;
                    }
                    else if(strcmp(UserChoice, "3")==0)
                    {
                        choice = 3;
                    }
                    else if(strcmp(UserChoice, "4")==0)
                    {
                        choice = 4;
                    }
                    else if(strcmp(UserChoice, "5")==0)
                    {
                        choice = 5;
                    }
                }
            }

            switch(choice)
            {
            case 1:
                choice = cadastrar_funcionario();
                system("cls");
                printf("\n                                           Usuário cadastrado com sucesso!\n\n");
                break;
            case 2:
                choice = remover_funcionario();
                if(choice == 0)
                {
                    system("cls");
                    printf("\n                                           Usuário removido com sucesso!\n\n");
                }
                else
                {
                    system("cls");
                    choice = 0;
                }
                break;
            case 3:
                choice = adicionar_quarto();
                system("cls");
                printf("\n                                          Quarto adicionado com sucesso!\n\n");
                break;
            case 4:
                choice = remover_quarto();
                if(choice == 0)
                {
                    system("cls");
                    printf("\n                                           Quarto removido com sucesso!\n\n");
                }
                else
                {
                    system("cls");
                    choice = 0;
                }
                break;
            case 5:
                user_loggedIn = 0;
                system("cls");
                main();
                break;
            default:
                choice = 0;
            }
        }
    }
    else if(user_loggedIn == 1)
    {
        while(user_loggedIn == 1)
        {
            system("cls");
            system("color F0"); //muda dor do prompt para fundo branco (F) e texto preto (0).
            //Menu do funcionário
            while((choice < 1) || (choice > 4))
            {
                printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                printf("                          ||                    FELIPPE'S HOTEL                    ||\n");
                printf("                          ||                                                       ||\n");
                printf("                          ||                  MENU DO FUNCIONÁRIO                  ||\n");
                printf("                          -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
                printf("                                        [1] - Check-in\n");
                printf("                                        [2] - Check-out\n");
                printf("                                        [3] - Relatórios\n");
                printf("                                        [4] - Log-out\n");
                printf("                                         ");
                fflush(stdin);
                fgets(UserChoice, 2, stdin); //Pegar entrada como "char" para evitar loop indevido caso usuário digite uma letra ao invés de um "int".
                UserChoice[strcspn(UserChoice, "\n")] = 0; //Eliminar \n da string.
                if(strcmp(UserChoice, "0")!=0 && strcmp(UserChoice, "1")!=0 && strcmp(UserChoice, "2")!=0 && strcmp(UserChoice, "3")!=0 && strcmp(UserChoice, "4")!=0)
                {
                    system("cls");
                    printf("                                         Opção inválida.\n\n");
                }
                else
                {
                    if(strcmp(UserChoice, "1")==0)
                    {
                        choice = 1;
                    }
                    else if(strcmp(UserChoice, "2")==0)
                    {
                        choice = 2;
                    }
                    else if(strcmp(UserChoice, "3")==0)
                    {
                        choice = 3;
                    }
                    else if(strcmp(UserChoice, "4")==0)
                    {
                        choice = 4;
                    }
                }
            }
            switch(choice)
            {
            case 1:
                choice = checkIn();
                choice = 0;
                break;
            case 2:
                choice = checkOut();
                choice = 0;
                break;
            case 3:
                choice = relatorios();
                choice = 0;
                break;
            case 4:
                user_loggedIn = 0;
                system("cls");
                main();
                break;
            default:
                choice = 0;
            }
        }
    }
}
