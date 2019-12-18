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
typedef  int /*<<< orphan*/  uint_t ;

/* Variables and functions */
#define  NL 129 
#define  NUL 128 
 unsigned int ao_string_cook_escape_char (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contiguous_quote (char**,char*,int*) ; 

char *
ao_string_cook(char * pzScan, int * lnct_p)
{
    int   l = 0;
    char  q = *pzScan;

    /*
     *  It is a quoted string.  Process the escape sequence characters
     *  (in the set "abfnrtv") and make sure we find a closing quote.
     */
    char * pzD = pzScan++;
    char * pzS = pzScan;

    if (lnct_p == NULL)
        lnct_p = &l;

    for (;;) {
        /*
         *  IF the next character is the quote character, THEN we may end the
         *  string.  We end it unless the next non-blank character *after* the
         *  string happens to also be a quote.  If it is, then we will change
         *  our quote character to the new quote character and continue
         *  condensing text.
         */
        while (*pzS == q) {
            *pzD = NUL; /* This is probably the end of the line */
            if (! contiguous_quote(&pzS, &q, lnct_p))
                return pzS;
        }

        /*
         *  We are inside a quoted string.  Copy text.
         */
        switch (*(pzD++) = *(pzS++)) {
        case NUL:
            return NULL;

        case NL:
            (*lnct_p)++;
            break;

        case '\\':
            /*
             *  IF we are escaping a new line,
             *  THEN drop both the escape and the newline from
             *       the result string.
             */
            if (*pzS == NL) {
                pzS++;
                pzD--;
                (*lnct_p)++;
            }

            /*
             *  ELSE IF the quote character is '"' or '`',
             *  THEN we do the full escape character processing
             */
            else if (q != '\'') {
                unsigned int ct;
                ct = ao_string_cook_escape_char(pzS, pzD-1, (uint_t)NL);
                if (ct == 0)
                    return NULL;

                pzS += ct;
            }     /* if (q != '\'')                  */

            /*
             *  OTHERWISE, we only process "\\", "\'" and "\#" sequences.
             *  The latter only to easily hide preprocessing directives.
             */
            else switch (*pzS) {
            case '\\':
            case '\'':
            case '#':
                pzD[-1] = *pzS++;
            }
        }     /* switch (*(pzD++) = *(pzS++))    */
    }         /* for (;;)                        */
}