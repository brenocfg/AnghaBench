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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int MAX_MODULE_HARDRESET_WAIT ; 
 scalar_t__ am33xx_prm_is_hardreset_asserted (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am33xx_prm_rmw_reg_bits (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_test_timeout (scalar_t__,int,int) ; 

__attribute__((used)) static int am33xx_prm_deassert_hardreset(u8 shift, u8 st_shift, u8 part,
					 s16 inst, u16 rstctrl_offs,
					 u16 rstst_offs)
{
	int c;
	u32 mask = 1 << st_shift;

	/* Check the current status to avoid  de-asserting the line twice */
	if (am33xx_prm_is_hardreset_asserted(shift, 0, inst, rstctrl_offs) == 0)
		return -EEXIST;

	/* Clear the reset status by writing 1 to the status bit */
	am33xx_prm_rmw_reg_bits(0xffffffff, mask, inst, rstst_offs);

	/* de-assert the reset control line */
	mask = 1 << shift;

	am33xx_prm_rmw_reg_bits(mask, 0, inst, rstctrl_offs);

	/* wait the status to be set */
	omap_test_timeout(am33xx_prm_is_hardreset_asserted(st_shift, 0, inst,
							   rstst_offs),
			  MAX_MODULE_HARDRESET_WAIT, c);

	return (c == MAX_MODULE_HARDRESET_WAIT) ? -EBUSY : 0;
}