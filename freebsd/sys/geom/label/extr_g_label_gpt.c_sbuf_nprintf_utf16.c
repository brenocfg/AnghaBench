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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_int ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIG_ENDIAN ; 
 scalar_t__ LITTLE_ENDIAN ; 
 void* be16toh (scalar_t__) ; 
 void* le16toh (scalar_t__) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int,...) ; 

__attribute__((used)) static void
sbuf_nprintf_utf16(struct sbuf *sb, uint16_t *str, size_t len)
{
	u_int bo;
	uint32_t ch;
	uint16_t c;

	bo = LITTLE_ENDIAN;	/* GPT is little-endian */
	while (len > 0 && *str != 0) {
		ch = (bo == BIG_ENDIAN) ? be16toh(*str) : le16toh(*str);
		str++, len--;
		if ((ch & 0xf800) == 0xd800) {
			if (len > 0) {
				c = (bo == BIG_ENDIAN) ? be16toh(*str)
				    : le16toh(*str);
				str++, len--;
			} else
				c = 0xfffd;
			if ((ch & 0x400) == 0 && (c & 0xfc00) == 0xdc00) {
				ch = ((ch & 0x3ff) << 10) + (c & 0x3ff);
				ch += 0x10000;
			} else
				ch = 0xfffd;
		} else if (ch == 0xfffe) { /* BOM (U+FEFF) swapped. */
			bo = (bo == BIG_ENDIAN) ? LITTLE_ENDIAN : BIG_ENDIAN;
			continue;
		} else if (ch == 0xfeff) /* BOM (U+FEFF) unswapped. */
			continue;

		/* Write the Unicode character in UTF-8 */
		if (ch < 0x80)
			sbuf_printf(sb, "%c", ch);
		else if (ch < 0x800)
			sbuf_printf(sb, "%c%c", 0xc0 | (ch >> 6),
			    0x80 | (ch & 0x3f));
		else if (ch < 0x10000)
			sbuf_printf(sb, "%c%c%c", 0xe0 | (ch >> 12),
			    0x80 | ((ch >> 6) & 0x3f), 0x80 | (ch & 0x3f));
		else if (ch < 0x200000)
			sbuf_printf(sb, "%c%c%c%c", 0xf0 | (ch >> 18),
			    0x80 | ((ch >> 12) & 0x3f),
			    0x80 | ((ch >> 6) & 0x3f), 0x80 | (ch & 0x3f));
	}
}