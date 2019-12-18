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
 int /*<<< orphan*/  OMAP2_RM_RSTCTRL ; 
 int /*<<< orphan*/  OMAP2_RM_RSTST ; 
 scalar_t__ omap2_prm_read_mod_bits_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap2_prm_rmw_mod_reg_bits (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_test_timeout (scalar_t__,int,int) ; 

int omap2_prm_deassert_hardreset(u8 rst_shift, u8 st_shift, u8 part,
				 s16 prm_mod, u16 rst_offset, u16 st_offset)
{
	u32 rst, st;
	int c;

	rst = 1 << rst_shift;
	st = 1 << st_shift;

	/* Check the current status to avoid de-asserting the line twice */
	if (omap2_prm_read_mod_bits_shift(prm_mod, OMAP2_RM_RSTCTRL, rst) == 0)
		return -EEXIST;

	/* Clear the reset status by writing 1 to the status bit */
	omap2_prm_rmw_mod_reg_bits(0xffffffff, st, prm_mod, OMAP2_RM_RSTST);
	/* de-assert the reset control line */
	omap2_prm_rmw_mod_reg_bits(rst, 0, prm_mod, OMAP2_RM_RSTCTRL);
	/* wait the status to be set */
	omap_test_timeout(omap2_prm_read_mod_bits_shift(prm_mod, OMAP2_RM_RSTST,
						  st),
			  MAX_MODULE_HARDRESET_WAIT, c);

	return (c == MAX_MODULE_HARDRESET_WAIT) ? -EBUSY : 0;
}