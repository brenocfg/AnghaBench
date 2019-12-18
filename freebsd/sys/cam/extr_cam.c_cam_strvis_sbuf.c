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
typedef  char u_int8_t ;
struct sbuf {int dummy; } ;

/* Variables and functions */
#define  CAM_STRVIS_FLAG_NONASCII_ESC 131 
 int CAM_STRVIS_FLAG_NONASCII_MASK ; 
#define  CAM_STRVIS_FLAG_NONASCII_RAW 130 
#define  CAM_STRVIS_FLAG_NONASCII_SPC 129 
#define  CAM_STRVIS_FLAG_NONASCII_TRIM 128 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char const) ; 

void
cam_strvis_sbuf(struct sbuf *sb, const u_int8_t *src, int srclen,
		uint32_t flags)
{

	/* Trim leading/trailing spaces, nulls. */
	while (srclen > 0 && src[0] == ' ')
		src++, srclen--;
	while (srclen > 0
	    && (src[srclen-1] == ' ' || src[srclen-1] == '\0'))
		srclen--;

	while (srclen > 0) {
		if (*src < 0x20 || *src >= 0x80) {
			/* SCSI-II Specifies that these should never occur. */
			/* non-printable character */
			switch (flags & CAM_STRVIS_FLAG_NONASCII_MASK) {
			case CAM_STRVIS_FLAG_NONASCII_ESC:
				sbuf_printf(sb, "\\%c%c%c", 
				    ((*src & 0300) >> 6) + '0',
				    ((*src & 0070) >> 3) + '0',
				    ((*src & 0007) >> 0) + '0');
				break;
			case CAM_STRVIS_FLAG_NONASCII_RAW:
				/*
				 * If we run into a NUL, just transform it
				 * into a space.
				 */
				if (*src != 0x00)
					sbuf_putc(sb, *src);
				else
					sbuf_putc(sb, ' ');
				break;
			case CAM_STRVIS_FLAG_NONASCII_SPC:
				sbuf_putc(sb, ' ');
				break;
			case CAM_STRVIS_FLAG_NONASCII_TRIM:
			default:
				break;
			}
		} else {
			/* normal character */
			sbuf_putc(sb, *src);
		}
		src++;
		srclen--;
	}
}