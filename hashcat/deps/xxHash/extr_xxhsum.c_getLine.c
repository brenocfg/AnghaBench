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
typedef  int /*<<< orphan*/  GetLineResult ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEFAULT_LINE_LENGTH ; 
 int const EOF ; 
 int /*<<< orphan*/  GetLine_eof ; 
 int /*<<< orphan*/  GetLine_exceedMaxLineLength ; 
 int /*<<< orphan*/  GetLine_ok ; 
 int /*<<< orphan*/  GetLine_outOfMemory ; 
 int MAX_LINE_LENGTH ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ realloc (char*,int) ; 

__attribute__((used)) static GetLineResult getLine(char** lineBuf, int* lineMax, FILE* inFile)
{
    GetLineResult result = GetLine_ok;
    int len = 0;

    if ((*lineBuf == NULL) || (*lineMax<1)) {
        free(*lineBuf);  /* in case it's != NULL */
        *lineMax = 0;
        *lineBuf = (char*)malloc(DEFAULT_LINE_LENGTH);
        if(*lineBuf == NULL) return GetLine_outOfMemory;
        *lineMax = DEFAULT_LINE_LENGTH;
    }

    for (;;) {
        const int c = fgetc(inFile);
        if (c == EOF) {
            /* If we meet EOF before first character, returns GetLine_eof,
             * otherwise GetLine_ok.
             */
            if (len == 0) result = GetLine_eof;
            break;
        }

        /* Make enough space for len+1 (for final NUL) bytes. */
        if (len+1 >= *lineMax) {
            char* newLineBuf = NULL;
            int newBufSize = *lineMax;

            newBufSize += (newBufSize/2) + 1; /* x 1.5 */
            if (newBufSize > MAX_LINE_LENGTH) newBufSize = MAX_LINE_LENGTH;
            if (len+1 >= newBufSize) return GetLine_exceedMaxLineLength;

            newLineBuf = (char*) realloc(*lineBuf, newBufSize);
            if (newLineBuf == NULL) return GetLine_outOfMemory;

            *lineBuf = newLineBuf;
            *lineMax = newBufSize;
        }

        if (c == '\n') break;
        (*lineBuf)[len++] = (char) c;
    }

    (*lineBuf)[len] = '\0';
    return result;
}