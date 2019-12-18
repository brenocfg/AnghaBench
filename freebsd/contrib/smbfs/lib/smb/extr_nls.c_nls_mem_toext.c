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
 void* memcpy (void*,void*,int) ; 
 scalar_t__ nls_toext ; 

void *
nls_mem_toext(void *dst, void *src, int size)
{
#ifdef HAVE_ICONV
	char *p = dst;
	char *s = src;
	size_t inlen, outlen;

	if (size == 0)
		return NULL;

	if (nls_toext == (iconv_t)0)
		return memcpy(dst, src, size);

	inlen = outlen = size;
	iconv(nls_toext, NULL, NULL, &p, &outlen);
	while (iconv(nls_toext, &s, &inlen, &p, &outlen) == -1) {
		*p++ = *s++;
		inlen--;
		outlen--;
	}
	return dst;
#else
	return memcpy(dst, src, size);
#endif
}