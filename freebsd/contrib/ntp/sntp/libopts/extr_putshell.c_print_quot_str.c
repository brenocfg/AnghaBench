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

/* Variables and functions */
 int /*<<< orphan*/  APOSTROPHE ; 
 char const* EMPTY_ARG ; 
 char const NUL ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char const*,size_t,size_t,int /*<<< orphan*/ ) ; 
 char* print_quoted_apostrophes (char const*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_quot_str(char const * str)
{
    /*
     *  Handle empty strings to make the rest of the logic simpler.
     */
    if ((str == NULL) || (*str == NUL)) {
        fputs(EMPTY_ARG, stdout);
        return;
    }

    /*
     *  Emit any single quotes/apostrophes at the start of the string and
     *  bail if that is all we need to do.
     */
    str = print_quoted_apostrophes(str);
    if (*str == NUL)
        return;

    /*
     *  Start the single quote string
     */
    fputc(APOSTROPHE, stdout);
    for (;;) {
        char const * pz = strchr(str, APOSTROPHE);
        if (pz == NULL)
            break;

        /*
         *  Emit the string up to the single quote (apostrophe) we just found.
         */
        (void)fwrite(str, (size_t)(pz - str), (size_t)1, stdout);

        /*
         * Close the current string, emit the apostrophes and re-open the
         * string (IFF there is more text to print).
         */
        fputc(APOSTROPHE, stdout);
        str = print_quoted_apostrophes(pz);
        if (*str == NUL)
            return;

        fputc(APOSTROPHE, stdout);
    }

    /*
     *  If we broke out of the loop, we must still emit the remaining text
     *  and then close the single quote string.
     */
    fputs(str, stdout);
    fputc(APOSTROPHE, stdout);
}