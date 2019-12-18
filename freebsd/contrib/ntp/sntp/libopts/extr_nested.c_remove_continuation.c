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
 char NL ; 
#define  NUL 128 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
remove_continuation(char * src)
{
    char * pzD;

    do  {
        while (*src == NL)  src++;
        pzD = strchr(src, NL);
        if (pzD == NULL)
            return;

        /*
         *  pzD has skipped at least one non-newline character and now
         *  points to a newline character.  It now becomes the source and
         *  pzD goes to the previous character.
         */
        src = pzD--;
        if (*pzD != '\\')
            pzD++;
    } while (pzD == src);

    /*
     *  Start shifting text.
     */
    for (;;) {
        char ch = ((*pzD++) = *(src++));
        switch (ch) {
        case NUL:  return;
        case '\\':
            if (*src == NL)
                --pzD; /* rewrite on next iteration */
        }
    }
}