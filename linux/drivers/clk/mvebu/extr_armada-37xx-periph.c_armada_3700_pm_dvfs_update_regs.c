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
 unsigned int ARMADA_37XX_DVFS_LOAD_0 ; 
 unsigned int ARMADA_37XX_DVFS_LOAD_1 ; 
 unsigned int ARMADA_37XX_DVFS_LOAD_2 ; 
 scalar_t__ ARMADA_37XX_NB_CONFIG_SHIFT ; 
 unsigned int ARMADA_37XX_NB_L0L1 ; 
 unsigned int ARMADA_37XX_NB_L2L3 ; 

__attribute__((used)) static void armada_3700_pm_dvfs_update_regs(unsigned int load_level,
					    unsigned int *reg,
					    unsigned int *offset)
{
	if (load_level <= ARMADA_37XX_DVFS_LOAD_1)
		*reg = ARMADA_37XX_NB_L0L1;
	else
		*reg = ARMADA_37XX_NB_L2L3;

	if (load_level == ARMADA_37XX_DVFS_LOAD_0 ||
	    load_level ==  ARMADA_37XX_DVFS_LOAD_2)
		*offset += ARMADA_37XX_NB_CONFIG_SHIFT;
}