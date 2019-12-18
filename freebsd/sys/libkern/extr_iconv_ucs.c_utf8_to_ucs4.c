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

__attribute__((used)) static uint32_t
utf8_to_ucs4(const char *src, size_t *utf8width, size_t srclen)
{
	size_t i, w = 0;
	uint32_t ucs4 = 0;

	/*
	 * get leading 1 byte from utf-8
	 */
	if ((*src & 0x80) == 0) {
		/*
		 * leading 1 bit is "0"
		 *  utf-8: 0xxxxxxx
		 *  ucs-4: 00000000 00000000 00000000 0xxxxxxx
		 */
		w = 1;
		/* get trailing 7 bits */
		ucs4 = *src & 0x7f;
	} else if ((*src & 0xe0) == 0xc0) {
		/*
		 * leading 3 bits are "110"
		 *  utf-8: 110xxxxx 10yyyyyy
		 *  ucs-4: 00000000 00000000 00000xxx xxyyyyyy
		 */
		w = 2;
		/* get trailing 5 bits */
		ucs4 = *src & 0x1f;
	} else if ((*src & 0xf0) == 0xe0) {
		/*
		 * leading 4 bits are "1110"
		 *  utf-8: 1110xxxx 10yyyyyy 10zzzzzz
		 *  ucs-4: 00000000 00000000 xxxxyyyy yyzzzzzz
		 */
		w = 3;
		/* get trailing 4 bits */
		ucs4 = *src & 0x0f;
	} else if ((*src & 0xf8) == 0xf0) {
		/*
		 * leading 5 bits are "11110"
		 *  utf-8: 11110www 10xxxxxx 10yyyyyy 10zzzzzz
		 *  ucs-4: 00000000 000wwwxx xxxxyyyy yyzzzzzz
		 */
		w = 4;
		/* get trailing 3 bits */
		ucs4 = *src & 0x07;
	} else {
		/* out of utf-16 range or having illegal bits */
		return (0);
	}

	if (srclen < w)
		return (0);

	/*
	 * get left parts from utf-8
	 */
	for (i = 1 ; i < w ; i++) {
		if ((*(src + i) & 0xc0) != 0x80) {
			/* invalid: leading 2 bits are not "10" */
			return (0);
		}
		/* concatenate trailing 6 bits into ucs4 */
		ucs4 <<= 6;
		ucs4 |= *(src + i) & 0x3f;
	}

	*utf8width = w;
	return (ucs4);
}