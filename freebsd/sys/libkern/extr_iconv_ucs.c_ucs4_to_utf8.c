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
typedef  int uint32_t ;
typedef  int u_char ;

/* Variables and functions */

__attribute__((used)) static u_char *
ucs4_to_utf8(uint32_t ucs4, char *dst, size_t *utf8width, size_t dstlen)
{
	u_char lead, *p;
	size_t i, w;

	/*
	 * determine utf-8 width and leading bits
	 */
	if (ucs4 < 0x80) {
		w = 1;
		lead = 0;	/* "0" */
	} else if (ucs4 < 0x800) {
		w = 2;
		lead = 0xc0;	/* "11" */
	} else if (ucs4 < 0x10000) {
		w = 3;
		lead = 0xe0;	/* "111" */
	} else if (ucs4 < 0x200000) {
		w = 4;
		lead = 0xf0;	/* "1111" */
	} else {
		return (NULL);
	}

	if (dstlen < w)
		return (NULL);

	/*
	 * construct utf-8
	 */
	p = dst;
	for (i = w - 1 ; i >= 1 ; i--) {
		/* get trailing 6 bits and put it with leading bit as "1" */
		*(p + i) = (ucs4 & 0x3f) | 0x80;
		ucs4 >>= 6;
	}
	*p = ucs4 | lead;

	*utf8width = w;

	return (p);
}