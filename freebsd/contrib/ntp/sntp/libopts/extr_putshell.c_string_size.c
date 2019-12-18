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
#define  BEL 135 
#define  BS 134 
#define  CR 133 
#define  FF 132 
#define  HT 131 
#define  NL 130 
#define  NUL 129 
#define  VT 128 

__attribute__((used)) static size_t
string_size(char const * scan, size_t nl_len)
{
    /*
     *  Start by counting the start and end quotes, plus the NUL.
     */
    size_t res_ln = 3;

    for (;;) {
        char ch = *(scan++);
        if ((ch >= ' ') && (ch <= '~')) {

            /*
             * a backslash allowance for double quotes and baskslashes
             */
            res_ln += ((ch == '"') || (ch == '\\')) ? 2 : 1;
        }

        /*
         *  When not a normal character, then count the characters
         *  required to represent whatever it is.
         */
        else switch (ch) {
        case NUL:
            return res_ln;

        case NL:
            res_ln += nl_len;
            break;

        case HT:
        case BEL:
        case BS:
        case FF:
        case CR:
        case VT:
            res_ln += 2;
            break;

        default:
            res_ln += 4; /* text len for \xNN */
        }
    }
}