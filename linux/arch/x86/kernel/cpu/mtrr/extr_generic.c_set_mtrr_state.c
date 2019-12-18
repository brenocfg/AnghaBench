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
struct TYPE_2__ {int def_type; int enabled; int /*<<< orphan*/  fixed_ranges; scalar_t__ have_fixed; int /*<<< orphan*/ * var_ranges; } ;

/* Variables and functions */
 unsigned long MTRR_CHANGE_MASK_DEFTYPE ; 
 unsigned long MTRR_CHANGE_MASK_FIXED ; 
 unsigned long MTRR_CHANGE_MASK_VARIABLE ; 
 int deftype_lo ; 
 TYPE_1__ mtrr_state ; 
 unsigned int num_var_ranges ; 
 scalar_t__ set_fixed_ranges (int /*<<< orphan*/ ) ; 
 scalar_t__ set_mtrr_var_ranges (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long set_mtrr_state(void)
{
	unsigned long change_mask = 0;
	unsigned int i;

	for (i = 0; i < num_var_ranges; i++) {
		if (set_mtrr_var_ranges(i, &mtrr_state.var_ranges[i]))
			change_mask |= MTRR_CHANGE_MASK_VARIABLE;
	}

	if (mtrr_state.have_fixed && set_fixed_ranges(mtrr_state.fixed_ranges))
		change_mask |= MTRR_CHANGE_MASK_FIXED;

	/*
	 * Set_mtrr_restore restores the old value of MTRRdefType,
	 * so to set it we fiddle with the saved value:
	 */
	if ((deftype_lo & 0xff) != mtrr_state.def_type
	    || ((deftype_lo & 0xc00) >> 10) != mtrr_state.enabled) {

		deftype_lo = (deftype_lo & ~0xcff) | mtrr_state.def_type |
			     (mtrr_state.enabled << 10);
		change_mask |= MTRR_CHANGE_MASK_DEFTYPE;
	}

	return change_mask;
}