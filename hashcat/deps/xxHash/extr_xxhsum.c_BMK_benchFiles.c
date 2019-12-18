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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BMK_benchMem (void* const,size_t const,int /*<<< orphan*/ ) ; 
 size_t BMK_selectBenchedSize (char const* const) ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const* const) ; 
 scalar_t__ calloc (size_t const,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 size_t fread (void* const,int,size_t const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  free (char* const) ; 

__attribute__((used)) static int BMK_benchFiles(const char** fileNamesTable, int nbFiles, U32 specificTest)
{
    int result = 0;
    int fileIdx;

    for (fileIdx=0; fileIdx<nbFiles; fileIdx++) {
        const char* const inFileName = fileNamesTable[fileIdx];
        FILE* const inFile = fopen( inFileName, "rb" );
        size_t const benchedSize = BMK_selectBenchedSize(inFileName);
        char* const buffer = (char*)calloc(benchedSize+16+3, 1);
        void* const alignedBuffer = (buffer+15) - (((size_t)(buffer+15)) & 0xF);  /* align on next 16 bytes */

        /* Checks */
        if ((inFile==NULL) || (inFileName==NULL)) {
            DISPLAY("Pb opening %s\n", inFileName);
            free(buffer);
            return 11;
        }
        if(!buffer) {
            DISPLAY("\nError: not enough memory!\n");
            fclose(inFile);
            return 12;
        }

        /* Fill input buffer */
        DISPLAYLEVEL(1, "\rLoading %s...        \n", inFileName);
        {   size_t const readSize = fread(alignedBuffer, 1, benchedSize, inFile);
            fclose(inFile);
            if(readSize != benchedSize) {
                DISPLAY("\nError: problem reading file '%s' !!    \n", inFileName);
                free(buffer);
                return 13;
        }   }

        /* bench */
        result |= BMK_benchMem(alignedBuffer, benchedSize, specificTest);

        free(buffer);
    }

    return result;
}