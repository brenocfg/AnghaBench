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
#define  NUL 128 
 char* VOIDP (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
parse_opt(char const ** nm_pp, char ** arg_pp, char * buf, size_t bufsz)
{
    int  res = 0;
    char const * p = *nm_pp;
    *arg_pp  = NULL;

    for (;;) {
        switch (*(p++)) {
        case NUL: return res;

        case '=':
            memcpy(buf, *nm_pp, (size_t)res);

            buf[res] = NUL;
            *nm_pp   = buf;
            *arg_pp  = VOIDP(p);
            return res;

        default:
            if (++res >= (int)bufsz)
                return -1;
        }
    }
}