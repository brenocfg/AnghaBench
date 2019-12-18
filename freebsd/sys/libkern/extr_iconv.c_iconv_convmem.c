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
 int iconv_conv (void*,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

void *
iconv_convmem(void *handle, void *dst, const void *src, int size)
{
	const char *s = src;
	char *d = dst;
	size_t inlen, outlen;
	int error;

	if (size == 0)
		return dst;
	if (handle == NULL) {
		memcpy(dst, src, size);
		return dst;
	}
	inlen = outlen = size;
	error = iconv_conv(handle, NULL, NULL, &d, &outlen);
	if (error)
		return NULL;
	error = iconv_conv(handle, &s, &inlen, &d, &outlen);
	if (error)
		return NULL;
	return dst;
}