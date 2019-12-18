#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mtrr_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* get ) (int,unsigned long*,unsigned long*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOSPC ; 
 int centaur_mcr_reserved ; 
 TYPE_1__* mtrr_if ; 
 int num_var_ranges ; 
 int /*<<< orphan*/  stub1 (int,unsigned long*,unsigned long*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
centaur_get_free_region(unsigned long base, unsigned long size, int replace_reg)
{
	unsigned long lbase, lsize;
	mtrr_type ltype;
	int i, max;

	max = num_var_ranges;
	if (replace_reg >= 0 && replace_reg < max)
		return replace_reg;

	for (i = 0; i < max; ++i) {
		if (centaur_mcr_reserved & (1 << i))
			continue;
		mtrr_if->get(i, &lbase, &lsize, &ltype);
		if (lsize == 0)
			return i;
	}

	return -ENOSPC;
}