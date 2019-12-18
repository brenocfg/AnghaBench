#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeCDict (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  compress (char const*,char* const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * createCDict_orDie (char const* const,int const) ; 
 char* createOutFilename_orDie (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char* const) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, const char** argv)
{
    const char* const exeName = argv[0];
    int const cLevel = 3;

    if (argc<3) {
        fprintf(stderr, "wrong arguments\n");
        fprintf(stderr, "usage:\n");
        fprintf(stderr, "%s [FILES] dictionary\n", exeName);
        return 1;
    }

    /* load dictionary only once */
    const char* const dictName = argv[argc-1];
    ZSTD_CDict* const dictPtr = createCDict_orDie(dictName, cLevel);

    int u;
    for (u=1; u<argc-1; u++) {
        const char* inFilename = argv[u];
        char* const outFilename = createOutFilename_orDie(inFilename);
        compress(inFilename, outFilename, dictPtr);
        free(outFilename);
    }

    ZSTD_freeCDict(dictPtr);
    printf("All %u files compressed. \n", argc-2);
    return 0;
}