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
typedef  int wchar_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  show_mb (char const*) ; 
 int /*<<< orphan*/  werr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
towide_euc_impl(wchar_t *wc, const char *mb, unsigned n,
    uint8_t cs2, uint8_t cs2width, uint8_t cs3, uint8_t cs3width)
{
	int i;
	int width = 2;
	wchar_t	c;

	c = *(const uint8_t *)mb;

	/*
	 * All variations of EUC encode 7-bit ASCII as one byte, and use
	 * additional bytes for more than that.
	 */
	if ((c & 0x80) == 0) {
		/* 7-bit */
		*wc = c;
		return (1);
	}

	/*
	 * All EUC variants reserve 0xa1-0xff to identify CS1, which
	 * is always two bytes wide.  Note that unused CS will be zero,
	 * and that cannot be true because we know that the high order
	 * bit must be set.
	 */
	if (c >= 0xa1) {
		width = 2;
	} else if (c == cs2) {
		width = cs2width;
	} else if (c == cs3) {
		width = cs3width;
	}

	if ((int)n < width) {
		werr("incomplete character sequence (%s)", show_mb(mb));
		return (-1);
	}

	for (i = 1; i < width; i++) {
		/* pull in the next byte */
		c <<= 8;
		c |= (uint8_t)(mb[i]);
	}

	*wc = c;
	return (width);
}