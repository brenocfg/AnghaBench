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
 int APL_NUM_CHANNELS ; 
 int ENODEV ; 
 scalar_t__ RD_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RD_REGP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apl_dports ; 
 int /*<<< orphan*/  asym_2way ; 
 int /*<<< orphan*/  b_cr_asym_2way_mem_region_mchbar ; 
 int /*<<< orphan*/  d_cr_drp0 ; 
 int /*<<< orphan*/ * drp0 ; 

__attribute__((used)) static int apl_get_registers(void)
{
	int ret = -ENODEV;
	int i;

	if (RD_REG(&asym_2way, b_cr_asym_2way_mem_region_mchbar))
		return -ENODEV;

	/*
	 * RD_REGP() will fail for unpopulated or non-existent
	 * DIMM slots. Return success if we find at least one DIMM.
	 */
	for (i = 0; i < APL_NUM_CHANNELS; i++)
		if (!RD_REGP(&drp0[i], d_cr_drp0, apl_dports[i]))
			ret = 0;

	return ret;
}