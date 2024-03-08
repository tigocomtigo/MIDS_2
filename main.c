#include <stdlib.h>
#include <stdio.h>
#define leitura 1
#define tamGrafo 200
#define tipo 1
#define teste 30
#include <time.h>
#include <limits.h>
#define maxFormigas 3000
#define inserirFeromonios 2
#define maxVezes 1

int main()
{
    FILE *file;
    file = fopen("/home/tigocomtigo/MIDS_2/antigos/johnson32-2-4.mis", "r");
    int tam2, vertices;
    // printf("x");

    if (leitura == 1)
    {
        fscanf(file, "%i %i\n", &tam2, &tam2);
        fscanf(file, "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ");
    }
    else if (leitura == 2)
    {
        fscanf(file, "%%%%MatrixMarket matrix coordinate pattern symmetric\n");
        fscanf(file, "%i %i %i", &tam2, &tam2, &vertices);
    }

    int matriz[tam2 + 1][tam2 + 1];
    int permitido[tam2 + 1];
    int feromoniosArestas[tam2 + 1];
    int vetorResposta[tam2];
    int vetorRespostaFinal[tam2];

    for (int i = 0; i <= tam2; ++i)
    {
        for (int j = 0; j <= tam2; ++j)
        {
            matriz[i][j] = 1;
        }
        feromoniosArestas[i] = 200;
        vetorResposta[i] = 0;
        vetorRespostaFinal[i] = -1;
    }

    int valor1, valor2;

    if (tipo == 1)
    {
        while (!feof(file))
        {
            fscanf(file, "%i %i\n", &valor1, &valor2);
            // printf("%i %i\n", valor1, valor2);
            //  fscanf(file,"%i %i\n", &valor1, &valor2);
            matriz[valor1][valor2] = 0;
            matriz[valor2][valor1] = 0;
            --feromoniosArestas[valor1];
            --feromoniosArestas[valor2];
        }
    }
    else if (tipo == 2)
    {
        while (!feof(file))
        {
            fscanf(file, "e %i %i\n", &valor1, &valor2);
            // fscanf(file,"%i %i\n", &valor1, &valor2);
            matriz[valor1][valor2] = 0;
            matriz[valor2][valor1] = 0;
            --feromoniosArestas[valor1];
            --feromoniosArestas[valor2];
        }
    }

    int quantidade_vertices;
    int qtd_formigas;
    int pontape;
    int caminhar;
    int valor_escolhido;
    int controle = 0;
    int posAtual = 0;
    int tamanhoMenor;
    int tamanhoAtual;
    double media = 0;
    int menorGlobal = INT_MAX;
    int testes = maxVezes;
    srand(time(NULL));
    double elapsed = 0;
    clock_t begin = clock();
    while (testes > 0)
    {
        controle = 0;
        tamanhoMenor = tam2;
        tamanhoAtual = tam2;
        qtd_formigas = maxFormigas;
        while (qtd_formigas > 0)
        {
            posAtual = 0;
            pontape = (rand() % tam2) + 1; // pontape inicial
            permitido[pontape] = 0;
            quantidade_vertices = tam2;
            // printf("x");
            permitido[0] = 0;
            for (int i = 1; i <= tam2; ++i)
            {
                if (matriz[pontape][i] == 0)
                {
                    permitido[i] = 0;
                    --quantidade_vertices;
                }
                else if (i != pontape)
                {
                    permitido[i] = 1;
                }
            }
            vetorResposta[posAtual] = pontape;
            ++posAtual;
            tamanhoAtual = 1;
            valor_escolhido = pontape;
            while (quantidade_vertices)
            {
                controle = 0;
                caminhar = (rand() % feromoniosArestas[pontape]) + 2;
                for (int i = 0; i <= tam2; ++i)
                {
                    // printf("x");
                    caminhar -= matriz[pontape][i];
                    if (caminhar <= 0)
                    {
                        if (permitido[i] == 1)
                        {
                            valor_escolhido = i;
                            break;
                        }
                    }
                    if (permitido[i] == 1)
                    {
                        valor_escolhido = i;
                        controle = valor_escolhido;
                    }
                }
                if (pontape == valor_escolhido)
                {
                    break;
                }
                permitido[valor_escolhido] = 0;
                for (int i = 1; i <= tam2; ++i)
                {
                    if (matriz[valor_escolhido][i] == 0 && permitido[i] == 1)
                    {
                        permitido[i] = 0;
                        --quantidade_vertices;
                    }
                }
                vetorResposta[posAtual] = valor_escolhido;
                pontape = valor_escolhido;
                ++posAtual;
                ++tamanhoAtual;
                --quantidade_vertices;
            }

            if (tamanhoAtual <= tamanhoMenor)
            {
                for (int i = 0; i < tam2; ++i)
                {
                    if (vetorRespostaFinal[i] == 0 && qtd_formigas < tam2)
                    {
                        break;
                    }
                    vetorRespostaFinal[i] = vetorResposta[i];
                    vetorResposta[i] = 0;
                }
                tamanhoMenor = tamanhoAtual;
            }
            else
            {
                for (int i = 0; i < tam2; ++i)
                {
                    if (vetorResposta[i] != 0)
                    {
                        vetorResposta[i] = 0;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            for (int i = 0; i < tam2; ++i)
            {
                if (vetorRespostaFinal[i + 1] == 0)
                {
                    // printf("%i", vetorRespostaFinal[i]);
                    break;
                }
                else
                {
                    if (i >= 1 && vetorRespostaFinal[i + 1] != 0)
                    {
                        ++feromoniosArestas[vetorRespostaFinal[i]];
                        ++matriz[vetorRespostaFinal[i]][vetorRespostaFinal[i + 1]];
                        ++matriz[vetorRespostaFinal[i + 1]][vetorRespostaFinal[i]];
                    }
                    printf("%i ", vetorRespostaFinal[i]);
                }
            }
            printf("\n");
            --qtd_formigas;
            posAtual = 0;
        }
        if (menorGlobal > tamanhoMenor)
        {
            menorGlobal = tamanhoMenor;
        }
        media += tamanhoMenor;
        --testes;
    }
    printf("\nMenor número: %i\nMedia: %lf", menorGlobal, (media * 1.0) / maxVezes);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    elapsed = time_spent;
    printf("\nExecuted in : %f s\n", elapsed);

    for (int i = 0; i <= tam2; ++i)
    {
        permitido[i] = 1;
    }
    for (int i = 0; i < tam2; ++i)
    {
        if (vetorRespostaFinal[i] != 0)
        {
            permitido[vetorRespostaFinal[i]] = 0;
            for (int j = 0; j <= tam2; ++j)
            {
                if (matriz[vetorRespostaFinal[i]][j] == 0)
                {
                    permitido[j] = 0;
                }
            }
        }
    }
    for (int i = 0; i <= tam2; ++i)
    {
        printf("%i ", permitido[i]);
    }
}