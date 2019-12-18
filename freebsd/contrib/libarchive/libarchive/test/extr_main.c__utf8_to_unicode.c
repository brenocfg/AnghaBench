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

/* Variables and functions */

__attribute__((used)) static int
_utf8_to_unicode(uint32_t *pwc, const char *s, size_t n)
{
	static const char utf8_count[256] = {
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,/* 00 - 0F */
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,/* 10 - 1F */
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,/* 20 - 2F */
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,/* 30 - 3F */
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,/* 40 - 4F */
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,/* 50 - 5F */
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,/* 60 - 6F */
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,/* 70 - 7F */
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/* 80 - 8F */
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/* 90 - 9F */
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/* A0 - AF */
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/* B0 - BF */
		 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,/* C0 - CF */
		 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,/* D0 - DF */
		 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,/* E0 - EF */
		 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /* F0 - FF */
	};
	int ch;
	int cnt;
	uint32_t wc;

	*pwc = 0;

	/* Sanity check. */
	if (n == 0)
		return (0);
	/*
	 * Decode 1-4 bytes depending on the value of the first byte.
	 */
	ch = (unsigned char)*s;
	if (ch == 0)
		return (0); /* Standard:  return 0 for end-of-string. */
	cnt = utf8_count[ch];

	/* Invalid sequence or there are not plenty bytes. */
	if (n < (size_t)cnt)
		return (-1);

	/* Make a Unicode code point from a single UTF-8 sequence. */
	switch (cnt) {
	case 1:	/* 1 byte sequence. */
		*pwc = ch & 0x7f;
		return (cnt);
	case 2:	/* 2 bytes sequence. */
		if ((s[1] & 0xc0) != 0x80) return (-1);
		*pwc = ((ch & 0x1f) << 6) | (s[1] & 0x3f);
		return (cnt);
	case 3:	/* 3 bytes sequence. */
		if ((s[1] & 0xc0) != 0x80) return (-1);
		if ((s[2] & 0xc0) != 0x80) return (-1);
		wc = ((ch & 0x0f) << 12)
		    | ((s[1] & 0x3f) << 6)
		    | (s[2] & 0x3f);
		if (wc < 0x800)
			return (-1);/* Overlong sequence. */
		break;
	case 4:	/* 4 bytes sequence. */
		if (n < 4)
			return (-1);
		if ((s[1] & 0xc0) != 0x80) return (-1);
		if ((s[2] & 0xc0) != 0x80) return (-1);
		if ((s[3] & 0xc0) != 0x80) return (-1);
		wc = ((ch & 0x07) << 18)
		    | ((s[1] & 0x3f) << 12)
		    | ((s[2] & 0x3f) << 6)
		    | (s[3] & 0x3f);
		if (wc < 0x10000)
			return (-1);/* Overlong sequence. */
		break;
	default:
		return (-1);
	}

	/* The code point larger than 0x10FFFF is not legal
	 * Unicode values. */
	if (wc > 0x10FFFF)
		return (-1);
	/* Correctly gets a Unicode, returns used bytes. */
	*pwc = wc;
	return (cnt);
}