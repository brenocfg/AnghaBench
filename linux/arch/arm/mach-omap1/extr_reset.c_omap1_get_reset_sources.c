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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SYSST ; 
 int ARM_SYSST_ARM_WDRST_SHIFT ; 
 int ARM_SYSST_EXT_RST_SHIFT ; 
 int ARM_SYSST_GLOB_SWRST_SHIFT ; 
 int ARM_SYSST_POR_SHIFT ; 
 int /*<<< orphan*/  OMAP1_IO_ADDRESS (int /*<<< orphan*/ ) ; 
 int OMAP_EXTWARM_RST_SRC_ID_SHIFT ; 
 int OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT ; 
 int OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT ; 
 int OMAP_MPU_WD_RST_SRC_ID_SHIFT ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 

u32 omap1_get_reset_sources(void)
{
	u32 ret = 0;
	u16 rs;

	rs = __raw_readw(OMAP1_IO_ADDRESS(ARM_SYSST));

	if (rs & (1 << ARM_SYSST_POR_SHIFT))
		ret |= 1 << OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT;
	if (rs & (1 << ARM_SYSST_EXT_RST_SHIFT))
		ret |= 1 << OMAP_EXTWARM_RST_SRC_ID_SHIFT;
	if (rs & (1 << ARM_SYSST_ARM_WDRST_SHIFT))
		ret |= 1 << OMAP_MPU_WD_RST_SRC_ID_SHIFT;
	if (rs & (1 << ARM_SYSST_GLOB_SWRST_SHIFT))
		ret |= 1 << OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT;

	return ret;
}