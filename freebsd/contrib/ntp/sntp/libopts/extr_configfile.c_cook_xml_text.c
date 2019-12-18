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
 int parse_xml_encoding (char**) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
cook_xml_text(char * pzData)
{
    char * pzs = pzData;
    char * pzd = pzData;
    char   bf[4];
    bf[2] = NUL;

    for (;;) {
        int ch = ((int)*(pzs++)) & 0xFF;
        switch (ch) {
        case NUL:
            *pzd = NUL;
            return;

        case '&':
            ch = parse_xml_encoding(&pzs);
            *(pzd++) = (char)ch;
            if (ch == NUL)
                return;
            break;

        case '%':
            bf[0] = *(pzs++);
            bf[1] = *(pzs++);
            if ((bf[0] == NUL) || (bf[1] == NUL)) {
                *pzd = NUL;
                return;
            }

            ch = (int)strtoul(bf, NULL, 16);
            /* FALLTHROUGH */

        default:
            *(pzd++) = (char)ch;
        }
    }
}