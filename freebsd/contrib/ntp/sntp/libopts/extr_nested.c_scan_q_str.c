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
 char NUL ; 

__attribute__((used)) static char const *
scan_q_str(char const * pzTxt)
{
    char q = *(pzTxt++); /* remember the type of quote */

    for (;;) {
        char ch = *(pzTxt++);
        if (ch == NUL)
            return pzTxt-1;

        if (ch == q)
            return pzTxt;

        if (ch == '\\') {
            ch = *(pzTxt++);
            /*
             *  IF the next character is NUL, drop the backslash, too.
             */
            if (ch == NUL)
                return pzTxt - 2;

            /*
             *  IF the quote character or the escape character were escaped,
             *  then skip both, as long as the string does not end.
             */
            if ((ch == q) || (ch == '\\')) {
                if (*(pzTxt++) == NUL)
                    return pzTxt-1;
            }
        }
    }
}