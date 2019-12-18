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
typedef  int ch_t ;

/* Variables and functions */
#define  NUL 128 
 int /*<<< orphan*/  ao_string_cook_escape_char (char const*,char*,int) ; 

__attribute__((used)) static void
copy_cooked(ch_t ** ppDest, char const ** ppSrc)
{
    ch_t * pDest = (ch_t *)*ppDest;
    const ch_t * pSrc  = (const ch_t *)(*ppSrc + 1);

    for (;;) {
        ch_t ch = *(pSrc++);
        switch (ch) {
        case NUL:   *ppSrc = NULL; return;
        case '"':   goto done;
        case '\\':
            pSrc += ao_string_cook_escape_char((const char *)pSrc, (char *)&ch, 0x7F);
            if (ch == 0x7F)
                break;
            /* FALLTHROUGH */

        default:
            *(pDest++) = ch;
        }
    }

 done:
    *ppDest = (ch_t *)pDest; /* next spot for storing character */
    *ppSrc  = (char const *)pSrc;  /* char following closing quote    */
}