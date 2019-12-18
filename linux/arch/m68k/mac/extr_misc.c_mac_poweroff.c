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
struct TYPE_2__ {scalar_t__ adb_type; } ;

/* Variables and functions */
 scalar_t__ MAC_ADB_CUDA ; 
 scalar_t__ MAC_ADB_EGRET ; 
 scalar_t__ MAC_ADB_II ; 
 scalar_t__ MAC_ADB_PB2 ; 
 int /*<<< orphan*/  cuda_shutdown () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 TYPE_1__* macintosh_config ; 
 scalar_t__ oss_present ; 
 int /*<<< orphan*/  oss_shutdown () ; 
 int /*<<< orphan*/  pmu_shutdown () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  via_shutdown () ; 

void mac_poweroff(void)
{
	if (oss_present) {
		oss_shutdown();
	} else if (macintosh_config->adb_type == MAC_ADB_II) {
		via_shutdown();
#ifdef CONFIG_ADB_CUDA
	} else if (macintosh_config->adb_type == MAC_ADB_EGRET ||
	           macintosh_config->adb_type == MAC_ADB_CUDA) {
		cuda_shutdown();
#endif
#ifdef CONFIG_ADB_PMU
	} else if (macintosh_config->adb_type == MAC_ADB_PB2) {
		pmu_shutdown();
#endif
	}

	pr_crit("It is now safe to turn off your Macintosh.\n");
	local_irq_disable();
	while(1);
}