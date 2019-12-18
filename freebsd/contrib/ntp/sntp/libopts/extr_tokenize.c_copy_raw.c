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
typedef  int cc_t ;

/* Variables and functions */
#define  NL 129 
#define  NUL 128 

__attribute__((used)) static void
copy_raw(ch_t ** ppDest, char const ** ppSrc)
{
    ch_t * pDest = *ppDest;
    cc_t * pSrc  = (cc_t *) (*ppSrc + 1);

    for (;;) {
        ch_t ch = *(pSrc++);
        switch (ch) {
        case NUL:   *ppSrc = NULL; return;
        case '\'':  goto done;
        case '\\':
            /*
             *  *Four* escapes are handled:  newline removal, escape char
             *  quoting and apostrophe quoting
             */
            switch (*pSrc) {
            case NUL:   *ppSrc = NULL; return;
            case '\r':
                if (*(++pSrc) == NL)
                    ++pSrc;
                continue;

            case NL:
                ++pSrc;
                continue;

            case '\'':
                ch = '\'';
                /* FALLTHROUGH */

            case '\\':
                ++pSrc;
                break;
            }
            /* FALLTHROUGH */

        default:
            *(pDest++) = ch;
        }
    }

 done:
    *ppDest = pDest; /* next spot for storing character */
    *ppSrc  = (char const *) pSrc;  /* char following closing quote    */
}