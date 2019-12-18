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
typedef  unsigned int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  htole16 (int) ; 

__attribute__((used)) static void
g_gpt_utf8_to_utf16(const uint8_t *s8, uint16_t *s16, size_t s16len)
{
	size_t s16idx, s8idx;
	uint32_t utfchar;
	unsigned int c, utfbytes;

	s8idx = s16idx = 0;
	utfchar = 0;
	utfbytes = 0;
	bzero(s16, s16len << 1);
	while (s8[s8idx] != 0 && s16idx < s16len) {
		c = s8[s8idx++];
		if ((c & 0xc0) != 0x80) {
			/* Initial characters. */
			if (utfbytes != 0) {
				/* Incomplete encoding of previous char. */
				s16[s16idx++] = htole16(0xfffd);
			}
			if ((c & 0xf8) == 0xf0) {
				utfchar = c & 0x07;
				utfbytes = 3;
			} else if ((c & 0xf0) == 0xe0) {
				utfchar = c & 0x0f;
				utfbytes = 2;
			} else if ((c & 0xe0) == 0xc0) {
				utfchar = c & 0x1f;
				utfbytes = 1;
			} else {
				utfchar = c & 0x7f;
				utfbytes = 0;
			}
		} else {
			/* Followup characters. */
			if (utfbytes > 0) {
				utfchar = (utfchar << 6) + (c & 0x3f);
				utfbytes--;
			} else if (utfbytes == 0)
				utfbytes = ~0;
		}
		/*
		 * Write the complete Unicode character as UTF-16 when we
		 * have all the UTF-8 charactars collected.
		 */
		if (utfbytes == 0) {
			/*
			 * If we need to write 2 UTF-16 characters, but
			 * we only have room for 1, then we truncate the
			 * string by writing a 0 instead.
			 */
			if (utfchar >= 0x10000 && s16idx < s16len - 1) {
				s16[s16idx++] =
				    htole16(0xd800 | ((utfchar >> 10) - 0x40));
				s16[s16idx++] =
				    htole16(0xdc00 | (utfchar & 0x3ff));
			} else
				s16[s16idx++] = (utfchar >= 0x10000) ? 0 :
				    htole16(utfchar);
		}
	}
	/*
	 * If our input string was truncated, append an invalid encoding
	 * character to the output string.
	 */
	if (utfbytes != 0 && s16idx < s16len)
		s16[s16idx++] = htole16(0xfffd);
}