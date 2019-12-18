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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int rd64 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

void
ixl_stat_update48(struct i40e_hw *hw, u32 hireg, u32 loreg,
	bool offset_loaded, u64 *offset, u64 *stat)
{
	u64 new_data;

#if defined(__FreeBSD__) && (__FreeBSD_version >= 1000000) && defined(__amd64__)
	new_data = rd64(hw, loreg);
#else
	/*
	 * Use two rd32's instead of one rd64; FreeBSD versions before
	 * 10 don't support 64-bit bus reads/writes.
	 */
	new_data = rd32(hw, loreg);
	new_data |= ((u64)(rd32(hw, hireg) & 0xFFFF)) << 32;
#endif

	if (!offset_loaded)
		*offset = new_data;
	if (new_data >= *offset)
		*stat = new_data - *offset;
	else
		*stat = (new_data + ((u64)1 << 48)) - *offset;
	*stat &= 0xFFFFFFFFFFFFULL;
}