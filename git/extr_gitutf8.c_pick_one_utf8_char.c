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
typedef  unsigned char ucs_char_t ;

/* Variables and functions */

__attribute__((used)) static ucs_char_t pick_one_utf8_char(const char **start, size_t *remainder_p)
{
	unsigned char *s = (unsigned char *)*start;
	ucs_char_t ch;
	size_t remainder, incr;

	/*
	 * A caller that assumes NUL terminated text can choose
	 * not to bother with the remainder length.  We will
	 * stop at the first NUL.
	 */
	remainder = (remainder_p ? *remainder_p : 999);

	if (remainder < 1) {
		goto invalid;
	} else if (*s < 0x80) {
		/* 0xxxxxxx */
		ch = *s;
		incr = 1;
	} else if ((s[0] & 0xe0) == 0xc0) {
		/* 110XXXXx 10xxxxxx */
		if (remainder < 2 ||
		    (s[1] & 0xc0) != 0x80 ||
		    (s[0] & 0xfe) == 0xc0)
			goto invalid;
		ch = ((s[0] & 0x1f) << 6) | (s[1] & 0x3f);
		incr = 2;
	} else if ((s[0] & 0xf0) == 0xe0) {
		/* 1110XXXX 10Xxxxxx 10xxxxxx */
		if (remainder < 3 ||
		    (s[1] & 0xc0) != 0x80 ||
		    (s[2] & 0xc0) != 0x80 ||
		    /* overlong? */
		    (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||
		    /* surrogate? */
		    (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||
		    /* U+FFFE or U+FFFF? */
		    (s[0] == 0xef && s[1] == 0xbf &&
		     (s[2] & 0xfe) == 0xbe))
			goto invalid;
		ch = ((s[0] & 0x0f) << 12) |
			((s[1] & 0x3f) << 6) | (s[2] & 0x3f);
		incr = 3;
	} else if ((s[0] & 0xf8) == 0xf0) {
		/* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
		if (remainder < 4 ||
		    (s[1] & 0xc0) != 0x80 ||
		    (s[2] & 0xc0) != 0x80 ||
		    (s[3] & 0xc0) != 0x80 ||
		    /* overlong? */
		    (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||
		    /* > U+10FFFF? */
		    (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4)
			goto invalid;
		ch = ((s[0] & 0x07) << 18) | ((s[1] & 0x3f) << 12) |
			((s[2] & 0x3f) << 6) | (s[3] & 0x3f);
		incr = 4;
	} else {
invalid:
		*start = NULL;
		return 0;
	}

	*start += incr;
	if (remainder_p)
		*remainder_p = remainder - incr;
	return ch;
}