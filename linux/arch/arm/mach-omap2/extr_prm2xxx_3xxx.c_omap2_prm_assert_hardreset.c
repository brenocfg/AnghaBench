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
 int /*<<< orphan*/  OMAP2_RM_RSTCTRL ; 
 int /*<<< orphan*/  omap2_prm_rmw_mod_reg_bits (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap2_prm_assert_hardreset(u8 shift, u8 part, s16 prm_mod, u16 offset)
{
	u32 mask;

	mask = 1 << shift;
	omap2_prm_rmw_mod_reg_bits(mask, mask, prm_mod, OMAP2_RM_RSTCTRL);

	return 0;
}