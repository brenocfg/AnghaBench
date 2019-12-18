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

void
ftpvis(char *dst, size_t dstlen, const char *src, size_t srclen)
{
	size_t	di, si;

	for (di = si = 0;
	    src[si] != '\0' && di < dstlen && si < srclen;
	    di++, si++) {
		switch (src[si]) {
		case '\\':
		case ' ':
		case '\t':
		case '\r':
		case '\n':
		case '"':
			dst[di++] = '\\';
			if (di >= dstlen)
				break;
			/* FALLTHROUGH */
		default:
			dst[di] = src[si];
		}
	}
	dst[di] = '\0';
}