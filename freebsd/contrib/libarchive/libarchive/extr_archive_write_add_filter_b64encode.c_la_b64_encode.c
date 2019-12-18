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
struct archive_string {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char) ; 
 char* base64 ; 

__attribute__((used)) static void
la_b64_encode(struct archive_string *as, const unsigned char *p, size_t len)
{
	int c;

	for (; len >= 3; p += 3, len -= 3) {
		c = p[0] >> 2;
		archive_strappend_char(as, base64[c]);
		c = ((p[0] & 0x03) << 4) | ((p[1] & 0xf0) >> 4);
		archive_strappend_char(as, base64[c]);
		c = ((p[1] & 0x0f) << 2) | ((p[2] & 0xc0) >> 6);
		archive_strappend_char(as, base64[c]);
		c = p[2] & 0x3f;
		archive_strappend_char(as, base64[c]);
	}
	if (len > 0) {
		c = p[0] >> 2;
		archive_strappend_char(as, base64[c]);
		c = (p[0] & 0x03) << 4;
		if (len == 1) {
			archive_strappend_char(as, base64[c]);
			archive_strappend_char(as, '=');
			archive_strappend_char(as, '=');
		} else {
			c |= (p[1] & 0xf0) >> 4;
			archive_strappend_char(as, base64[c]);
			c = (p[1] & 0x0f) << 2;
			archive_strappend_char(as, base64[c]);
			archive_strappend_char(as, '=');
		}
	}
	archive_strappend_char(as, '\n');
}