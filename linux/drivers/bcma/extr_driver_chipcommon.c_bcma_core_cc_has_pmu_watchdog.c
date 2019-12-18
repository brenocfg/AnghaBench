#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bcma_drv_cc {int capabilities; TYPE_1__* core; } ;
struct TYPE_4__ {scalar_t__ id; int rev; } ;
struct bcma_bus {TYPE_2__ chipinfo; } ;
struct TYPE_3__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int BCMA_CC_CAP_PMU ; 
 scalar_t__ BCMA_CHIP_ID_BCM53573 ; 
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static bool bcma_core_cc_has_pmu_watchdog(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;

	if (cc->capabilities & BCMA_CC_CAP_PMU) {
		if (bus->chipinfo.id == BCMA_CHIP_ID_BCM53573) {
			WARN(bus->chipinfo.rev <= 1, "No watchdog available\n");
			/* 53573B0 and 53573B1 have bugged PMU watchdog. It can
			 * be enabled but timer can't be bumped. Use CC one
			 * instead.
			 */
			return false;
		}
		return true;
	} else {
		return false;
	}
}