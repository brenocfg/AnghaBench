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
typedef  char uint8_t ;

/* Variables and functions */

void
nvme_strvis(uint8_t *dst, const uint8_t *src, int dstlen, int srclen)
{
	uint8_t *cur_pos;

	/* Trim leading/trailing spaces, nulls. */
	while (srclen > 0 && src[0] == ' ')
		src++, srclen--;
	while (srclen > 0
	    && (src[srclen - 1] == ' ' || src[srclen - 1] == '\0'))
		srclen--;

	while (srclen > 0 && dstlen > 1) {
		cur_pos = dst;

		/* Show '?' for non-printable characters. */
		if (*src < 0x20 || *src >= 0x7F)
			*cur_pos++ = '?';
		else
			*cur_pos++ = *src;
		src++;
		srclen--;
		dstlen -= cur_pos - dst;
		dst = cur_pos;
	}
	*dst = '\0';
}