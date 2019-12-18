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

/* Variables and functions */
 uintptr_t LONGPTR_MASK ; 
 unsigned long const mask01 ; 
 unsigned long const mask80 ; 
 int /*<<< orphan*/  testbyte (int) ; 

size_t
strlen(const char *str)
{
	const char *p;
	const unsigned long *lp;
	long va, vb;

	/*
	 * Before trying the hard (unaligned byte-by-byte access) way
	 * to figure out whether there is a nul character, try to see
	 * if there is a nul character is within this accessible word
	 * first.
	 *
	 * p and (p & ~LONGPTR_MASK) must be equally accessible since
	 * they always fall in the same memory page, as long as page
	 * boundaries is integral multiple of word size.
	 */
	lp = (const unsigned long *)((uintptr_t)str & ~LONGPTR_MASK);
	va = (*lp - mask01);
	vb = ((~*lp) & mask80);
	lp++;
	if (va & vb)
		/* Check if we have \0 in the first part */
		for (p = str; p < (const char *)lp; p++)
			if (*p == '\0')
				return (p - str);

	/* Scan the rest of the string using word sized operation */
	for (; ; lp++) {
		va = (*lp - mask01);
		vb = ((~*lp) & mask80);
		if (va & vb) {
			p = (const char *)(lp);
			testbyte(0);
			testbyte(1);
			testbyte(2);
			testbyte(3);
#if (LONG_BIT >= 64)
			testbyte(4);
			testbyte(5);
			testbyte(6);
			testbyte(7);
#endif
		}
	}

	/* NOTREACHED */
	return (0);
}