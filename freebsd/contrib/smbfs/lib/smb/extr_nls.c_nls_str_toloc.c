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
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int iconv (scalar_t__,char**,size_t*,char**,size_t*) ; 
 scalar_t__ nls_toloc ; 
 char* strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

char *
nls_str_toloc(char *dst, char *src)
{
#ifdef HAVE_ICONV
	char *p = dst;
	size_t inlen, outlen;

	if (nls_toloc == (iconv_t)0)
		return strcpy(dst, src);
	inlen = outlen = strlen(src);
	iconv(nls_toloc, NULL, NULL, &p, &outlen);
	while (iconv(nls_toloc, &src, &inlen, &p, &outlen) == -1) {
		*p++ = *src++;
		inlen--;
		outlen--;
	}
	*p = 0;
	return dst;
#else
	return strcpy(dst, src);
#endif
}