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
typedef  int /*<<< orphan*/  mtrr_type ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  cyrix_get_arr (int,unsigned long*,unsigned long*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cyrix_get_free_region(unsigned long base, unsigned long size, int replace_reg)
{
	unsigned long lbase, lsize;
	mtrr_type ltype;
	int i;

	switch (replace_reg) {
	case 7:
		if (size < 0x40)
			break;
		/* Else, fall through */
	case 6:
	case 5:
	case 4:
		return replace_reg;
	case 3:
	case 2:
	case 1:
	case 0:
		return replace_reg;
	}
	/* If we are to set up a region >32M then look at ARR7 immediately */
	if (size > 0x2000) {
		cyrix_get_arr(7, &lbase, &lsize, &ltype);
		if (lsize == 0)
			return 7;
		/* Else try ARR0-ARR6 first  */
	} else {
		for (i = 0; i < 7; i++) {
			cyrix_get_arr(i, &lbase, &lsize, &ltype);
			if (lsize == 0)
				return i;
		}
		/*
		 * ARR0-ARR6 isn't free
		 * try ARR7 but its size must be at least 256K
		 */
		cyrix_get_arr(i, &lbase, &lsize, &ltype);
		if ((lsize == 0) && (size >= 0x40))
			return i;
	}
	return -ENOSPC;
}