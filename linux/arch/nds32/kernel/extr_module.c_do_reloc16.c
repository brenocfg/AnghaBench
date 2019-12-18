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

void do_reloc16(unsigned int val, unsigned int *loc, unsigned int val_mask,
		unsigned int val_shift, unsigned int loc_mask,
		unsigned int partial_in_place, unsigned int swap)
{
	unsigned int tmp = 0, tmp2 = 0;

	__asm__ __volatile__("\tlhi.bi\t%0, [%2], 0\n"
			     "\tbeqz\t%3, 1f\n"
			     "\twsbh\t%0, %1\n"
			     "1:\n":"=r"(tmp):"0"(tmp), "r"(loc), "r"(swap)
	    );

	tmp2 = tmp & loc_mask;
	if (partial_in_place) {
		tmp &= (~loc_mask);
		tmp =
		    tmp2 | ((tmp + ((val & val_mask) >> val_shift)) & val_mask);
	} else {
		tmp = tmp2 | ((val & val_mask) >> val_shift);
	}

	__asm__ __volatile__("\tbeqz\t%3, 2f\n"
			     "\twsbh\t%0, %1\n"
			     "2:\n"
			     "\tshi.bi\t%0, [%2], 0\n":"=r"(tmp):"0"(tmp),
			     "r"(loc), "r"(swap)
	    );
}