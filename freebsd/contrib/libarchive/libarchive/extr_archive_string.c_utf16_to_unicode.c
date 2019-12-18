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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 scalar_t__ IS_HIGH_SURROGATE_LA (unsigned int) ; 
 scalar_t__ IS_LOW_SURROGATE_LA (unsigned int) ; 
 scalar_t__ IS_SURROGATE_PAIR_LA (unsigned int) ; 
 unsigned int UNICODE_MAX ; 
 unsigned int UNICODE_R_CHAR ; 
 unsigned int archive_be16dec (char const*) ; 
 unsigned int archive_le16dec (char const*) ; 
 unsigned int combine_surrogate_pair (unsigned int,unsigned int) ; 

__attribute__((used)) static int
utf16_to_unicode(uint32_t *pwc, const char *s, size_t n, int be)
{
	const char *utf16 = s;
	unsigned uc;

	if (n == 0)
		return (0);
	if (n == 1) {
		/* set the Replacement Character instead. */
		*pwc = UNICODE_R_CHAR;
		return (-1);
	}

	if (be)
		uc = archive_be16dec(utf16);
	else
		uc = archive_le16dec(utf16);
	utf16 += 2;
		
	/* If this is a surrogate pair, assemble the full code point.*/
	if (IS_HIGH_SURROGATE_LA(uc)) {
		unsigned uc2;

		if (n >= 4) {
			if (be)
				uc2 = archive_be16dec(utf16);
			else
				uc2 = archive_le16dec(utf16);
		} else
			uc2 = 0;
		if (IS_LOW_SURROGATE_LA(uc2)) {
			uc = combine_surrogate_pair(uc, uc2);
			utf16 += 2;
		} else {
	 		/* Undescribed code point should be U+FFFD
		 	* (replacement character). */
			*pwc = UNICODE_R_CHAR;
			return (-2);
		}
	}

	/*
	 * Surrogate pair values(0xd800 through 0xdfff) are only
	 * used by UTF-16, so, after above calculation, the code
	 * must not be surrogate values, and Unicode has no codes
	 * larger than 0x10ffff. Thus, those are not legal Unicode
	 * values.
	 */
	if (IS_SURROGATE_PAIR_LA(uc) || uc > UNICODE_MAX) {
	 	/* Undescribed code point should be U+FFFD
	 	* (replacement character). */
		*pwc = UNICODE_R_CHAR;
		return (((int)(utf16 - s)) * -1);
	}
	*pwc = uc;
	return ((int)(utf16 - s));
}