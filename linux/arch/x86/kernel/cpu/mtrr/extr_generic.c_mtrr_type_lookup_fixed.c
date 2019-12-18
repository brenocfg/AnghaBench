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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/ * fixed_ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTRR_TYPE_INVALID ; 
 TYPE_1__ mtrr_state ; 

__attribute__((used)) static u8 mtrr_type_lookup_fixed(u64 start, u64 end)
{
	int idx;

	if (start >= 0x100000)
		return MTRR_TYPE_INVALID;

	/* 0x0 - 0x7FFFF */
	if (start < 0x80000) {
		idx = 0;
		idx += (start >> 16);
		return mtrr_state.fixed_ranges[idx];
	/* 0x80000 - 0xBFFFF */
	} else if (start < 0xC0000) {
		idx = 1 * 8;
		idx += ((start - 0x80000) >> 14);
		return mtrr_state.fixed_ranges[idx];
	}

	/* 0xC0000 - 0xFFFFF */
	idx = 3 * 8;
	idx += ((start - 0xC0000) >> 12);
	return mtrr_state.fixed_ranges[idx];
}