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
typedef  char wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int INT_MAX ; 
 int /*<<< orphan*/  errno ; 

int xutftowcsn(wchar_t *wcs, const char *utfs, size_t wcslen, int utflen)
{
	int upos = 0, wpos = 0;
	const unsigned char *utf = (const unsigned char*) utfs;
	if (!utf || !wcs || wcslen < 1) {
		errno = EINVAL;
		return -1;
	}
	/* reserve space for \0 */
	wcslen--;
	if (utflen < 0)
		utflen = INT_MAX;

	while (upos < utflen) {
		int c = utf[upos++] & 0xff;
		if (utflen == INT_MAX && c == 0)
			break;

		if (wpos >= wcslen) {
			wcs[wpos] = 0;
			errno = ERANGE;
			return -1;
		}

		if (c < 0x80) {
			/* ASCII */
			wcs[wpos++] = c;
		} else if (c >= 0xc2 && c < 0xe0 && upos < utflen &&
				(utf[upos] & 0xc0) == 0x80) {
			/* 2-byte utf-8 */
			c = ((c & 0x1f) << 6);
			c |= (utf[upos++] & 0x3f);
			wcs[wpos++] = c;
		} else if (c >= 0xe0 && c < 0xf0 && upos + 1 < utflen &&
				!(c == 0xe0 && utf[upos] < 0xa0) && /* over-long encoding */
				(utf[upos] & 0xc0) == 0x80 &&
				(utf[upos + 1] & 0xc0) == 0x80) {
			/* 3-byte utf-8 */
			c = ((c & 0x0f) << 12);
			c |= ((utf[upos++] & 0x3f) << 6);
			c |= (utf[upos++] & 0x3f);
			wcs[wpos++] = c;
		} else if (c >= 0xf0 && c < 0xf5 && upos + 2 < utflen &&
				wpos + 1 < wcslen &&
				!(c == 0xf0 && utf[upos] < 0x90) && /* over-long encoding */
				!(c == 0xf4 && utf[upos] >= 0x90) && /* > \u10ffff */
				(utf[upos] & 0xc0) == 0x80 &&
				(utf[upos + 1] & 0xc0) == 0x80 &&
				(utf[upos + 2] & 0xc0) == 0x80) {
			/* 4-byte utf-8: convert to \ud8xx \udcxx surrogate pair */
			c = ((c & 0x07) << 18);
			c |= ((utf[upos++] & 0x3f) << 12);
			c |= ((utf[upos++] & 0x3f) << 6);
			c |= (utf[upos++] & 0x3f);
			c -= 0x10000;
			wcs[wpos++] = 0xd800 | (c >> 10);
			wcs[wpos++] = 0xdc00 | (c & 0x3ff);
		} else if (c >= 0xa0) {
			/* invalid utf-8 byte, printable unicode char: convert 1:1 */
			wcs[wpos++] = c;
		} else {
			/* invalid utf-8 byte, non-printable unicode: convert to hex */
			static const char *hex = "0123456789abcdef";
			wcs[wpos++] = hex[c >> 4];
			if (wpos < wcslen)
				wcs[wpos++] = hex[c & 0x0f];
		}
	}
	wcs[wpos] = 0;
	return wpos;
}