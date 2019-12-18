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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  OMAP_MEM0_RETSTATE_MASK ; 
 int /*<<< orphan*/  OMAP_MEM1_RETSTATE_MASK ; 
 int /*<<< orphan*/  OMAP_MEM2_RETSTATE_MASK ; 
 int /*<<< orphan*/  OMAP_MEM3_RETSTATE_MASK ; 
 int /*<<< orphan*/  OMAP_MEM4_RETSTATE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

u32 omap2_pwrdm_get_mem_bank_retst_mask(u8 bank)
{
	switch (bank) {
	case 0:
		return OMAP_MEM0_RETSTATE_MASK;
	case 1:
		return OMAP_MEM1_RETSTATE_MASK;
	case 2:
		return OMAP_MEM2_RETSTATE_MASK;
	case 3:
		return OMAP_MEM3_RETSTATE_MASK;
	case 4:
		return OMAP_MEM4_RETSTATE_MASK;
	default:
		WARN_ON(1); /* should never happen */
		return -EEXIST;
	}
	return 0;
}