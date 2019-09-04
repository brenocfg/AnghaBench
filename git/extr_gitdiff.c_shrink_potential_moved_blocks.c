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
struct moved_block {scalar_t__ match; } ;
typedef  int /*<<< orphan*/  pmb ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct moved_block*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int shrink_potential_moved_blocks(struct moved_block *pmb,
					 int pmb_nr)
{
	int lp, rp;

	/* Shrink the set of potential block to the remaining running */
	for (lp = 0, rp = pmb_nr - 1; lp <= rp;) {
		while (lp < pmb_nr && pmb[lp].match)
			lp++;
		/* lp points at the first NULL now */

		while (rp > -1 && !pmb[rp].match)
			rp--;
		/* rp points at the last non-NULL */

		if (lp < pmb_nr && rp > -1 && lp < rp) {
			pmb[lp] = pmb[rp];
			memset(&pmb[rp], 0, sizeof(pmb[rp]));
			rp--;
			lp++;
		}
	}

	/* Remember the number of running sets */
	return rp + 1;
}