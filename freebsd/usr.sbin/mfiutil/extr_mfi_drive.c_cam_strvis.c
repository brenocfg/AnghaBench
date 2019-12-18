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

__attribute__((used)) static void
cam_strvis(char *dst, const char *src, int srclen, int dstlen)
{

	/* Trim leading/trailing spaces, nulls. */
	while (srclen > 0 && src[0] == ' ')
		src++, srclen--;
	while (srclen > 0
	    && (src[srclen-1] == ' ' || src[srclen-1] == '\0'))
		srclen--;

	while (srclen > 0 && dstlen > 1) {
		char *cur_pos = dst;

		if (*src < 0x20) {
			/* SCSI-II Specifies that these should never occur. */
			/* non-printable character */
			if (dstlen > 4) {
				*cur_pos++ = '\\';
				*cur_pos++ = ((*src & 0300) >> 6) + '0';
				*cur_pos++ = ((*src & 0070) >> 3) + '0';
				*cur_pos++ = ((*src & 0007) >> 0) + '0';
			} else {
				*cur_pos++ = '?';
			}
		} else {
			/* normal character */
			*cur_pos++ = *src;
		}
		src++;
		srclen--;
		dstlen -= cur_pos - dst;
		dst = cur_pos;
	}
	*dst = '\0';
}