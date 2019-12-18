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
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int ARMADA_37XX_NB_CPU_LOAD ; 
 unsigned int ARMADA_37XX_NB_CPU_LOAD_MASK ; 
 unsigned int ARMADA_37XX_NB_TBG_DIV_MASK ; 
 unsigned int ARMADA_37XX_NB_TBG_DIV_OFF ; 
 int /*<<< orphan*/  armada_3700_pm_dvfs_update_regs (unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,unsigned int,unsigned int*) ; 

__attribute__((used)) static unsigned int armada_3700_pm_dvfs_get_cpu_div(struct regmap *base)
{
	unsigned int reg = ARMADA_37XX_NB_CPU_LOAD;
	unsigned int offset = ARMADA_37XX_NB_TBG_DIV_OFF;
	unsigned int load_level, div;

	/*
	 * This function is always called after the function
	 * armada_3700_pm_dvfs_is_enabled, so no need to check again
	 * if the base is valid.
	 */
	regmap_read(base, reg, &load_level);

	/*
	 * The register and the offset inside this register accessed to
	 * read the current divider depend on the load level
	 */
	load_level &= ARMADA_37XX_NB_CPU_LOAD_MASK;
	armada_3700_pm_dvfs_update_regs(load_level, &reg, &offset);

	regmap_read(base, reg, &div);

	return (div >> offset) & ARMADA_37XX_NB_TBG_DIV_MASK;
}