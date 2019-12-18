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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AGDUPSTR (char*,char const*,char*) ; 
 int /*<<< orphan*/  AGFREE (char const*) ; 
 char HT ; 
 char NL ; 
 char NUL ; 
 int /*<<< orphan*/  isspace (int) ; 
 int /*<<< orphan*/  print_one_paragraph (char const*,int,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 

void
optionPrintParagraphs(char const * text, bool plain, FILE * fp)
{
    size_t len = strlen(text);
    char * buf;
#ifndef ENABLE_NLS
    if (plain || (len < 256))
#else
    if (len < 256)
#endif
    {
        print_one_paragraph(text, plain, fp);
        return;
    }

    AGDUPSTR(buf, text, "ppara");
    text = buf;

    for (;;) {
        char * scan;

        if (len < 256) {
        done:
            print_one_paragraph(buf, plain, fp);
            break;
        }
        scan = buf;

    try_longer:
        scan = strchr(scan, NL);
        if (scan == NULL)
            goto done;

        if ((scan - buf) < 40) {
            scan++;
            goto try_longer;
        }

        scan++;
        if ((! isspace((int)*scan)) || (*scan == HT))
            /*
             * line starts with tab or non-whitespace --> continuation
             */
            goto try_longer;

        if (*scan == NL) {
            /*
             * Double newline -> paragraph break
             * Include all newlines in current paragraph.
             */
            while (*++scan == NL)  /*continue*/;

        } else {
            char * p = scan;
            int   sp_ct = 0;

            while (*p == ' ') {
                if (++sp_ct >= 8) {
                    /*
                     * Too many spaces --> continuation line
                     */
                    scan = p;
                    goto try_longer;
                }
                p++;
            }
        }

        /*
         * "scan" points to the first character of a paragraph or the
         * terminating NUL byte.
         */
        {
            char svch = *scan;
            *scan = NUL;
            print_one_paragraph(buf, plain, fp);
            len -= scan - buf;
            if (len <= 0)
                break;
            *scan = svch;
            buf = scan;
        }
    }
    AGFREE(text);
}