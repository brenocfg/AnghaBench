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
typedef  size_t ptrdiff_t ;
typedef  int Char ;

/* Variables and functions */
 size_t MALLOC_INCR ; 
 size_t MALLOC_SURPLUS ; 
 int const QUOTE ; 
 int /*<<< orphan*/  one_wctomb (char*,int const) ; 
 char* xmalloc (size_t) ; 
 char* xrealloc (char*,size_t) ; 

char   *
short2qstr(const Char *src)
{
    static char *sdst = NULL;
    static size_t dstsize = 0;
    char *dst, *edst;

    if (src == NULL)
	return (NULL);

    if (sdst == NULL) {
	dstsize = MALLOC_INCR;
	sdst = xmalloc((dstsize + MALLOC_SURPLUS) * sizeof(char));
    }
    dst = sdst;
    edst = &dst[dstsize];
    while (*src) {
	if (*src & QUOTE) {
	    *dst++ = '\\';
	    if (dst == edst) {
		dstsize += MALLOC_INCR;
		sdst = xrealloc(sdst,
				(dstsize + MALLOC_SURPLUS) * sizeof(char));
		edst = &sdst[dstsize];
		dst = &edst[-MALLOC_INCR];
	    }
	}
	dst += one_wctomb(dst, *src);
	src++;
	if (dst >= edst) {
	    ptrdiff_t i = dst - edst;
	    dstsize += MALLOC_INCR;
	    sdst = xrealloc(sdst, (dstsize + MALLOC_SURPLUS) * sizeof(char));
	    edst = &sdst[dstsize];
	    dst = &edst[-MALLOC_INCR + i];
	}
    }
    *dst = 0;
    return (sdst);
}