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
typedef  int u8 ;
typedef  int u64 ;
struct TYPE_2__ {int enabled; scalar_t__ have_fixed; } ;

/* Variables and functions */
 int MTRR_STATE_MTRR_ENABLED ; 
 int MTRR_STATE_MTRR_FIXED_ENABLED ; 
 int MTRR_TYPE_INVALID ; 
 int MTRR_TYPE_WRBACK ; 
 scalar_t__ check_type_overlap (int*,int*) ; 
 TYPE_1__ mtrr_state ; 
 int /*<<< orphan*/  mtrr_state_set ; 
 int mtrr_tom2 ; 
 int mtrr_type_lookup_fixed (int,int) ; 
 int mtrr_type_lookup_variable (int,int,int*,int*,int*) ; 

u8 mtrr_type_lookup(u64 start, u64 end, u8 *uniform)
{
	u8 type, prev_type, is_uniform = 1, dummy;
	int repeat;
	u64 partial_end;

	if (!mtrr_state_set)
		return MTRR_TYPE_INVALID;

	if (!(mtrr_state.enabled & MTRR_STATE_MTRR_ENABLED))
		return MTRR_TYPE_INVALID;

	/*
	 * Look up the fixed ranges first, which take priority over
	 * the variable ranges.
	 */
	if ((start < 0x100000) &&
	    (mtrr_state.have_fixed) &&
	    (mtrr_state.enabled & MTRR_STATE_MTRR_FIXED_ENABLED)) {
		is_uniform = 0;
		type = mtrr_type_lookup_fixed(start, end);
		goto out;
	}

	/*
	 * Look up the variable ranges.  Look of multiple ranges matching
	 * this address and pick type as per MTRR precedence.
	 */
	type = mtrr_type_lookup_variable(start, end, &partial_end,
					 &repeat, &is_uniform);

	/*
	 * Common path is with repeat = 0.
	 * However, we can have cases where [start:end] spans across some
	 * MTRR ranges and/or the default type.  Do repeated lookups for
	 * that case here.
	 */
	while (repeat) {
		prev_type = type;
		start = partial_end;
		is_uniform = 0;
		type = mtrr_type_lookup_variable(start, end, &partial_end,
						 &repeat, &dummy);

		if (check_type_overlap(&prev_type, &type))
			goto out;
	}

	if (mtrr_tom2 && (start >= (1ULL<<32)) && (end < mtrr_tom2))
		type = MTRR_TYPE_WRBACK;

out:
	*uniform = is_uniform;
	return type;
}