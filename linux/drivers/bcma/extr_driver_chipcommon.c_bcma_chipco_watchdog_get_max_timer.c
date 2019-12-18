#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bcma_drv_cc {TYPE_3__* core; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct bcma_bus {TYPE_1__ chipinfo; } ;
struct TYPE_5__ {int rev; } ;
struct TYPE_6__ {TYPE_2__ id; struct bcma_bus* bus; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM4706 ; 
 scalar_t__ bcma_core_cc_has_pmu_watchdog (struct bcma_drv_cc*) ; 

__attribute__((used)) static u32 bcma_chipco_watchdog_get_max_timer(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;
	u32 nb;

	if (bcma_core_cc_has_pmu_watchdog(cc)) {
		if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706)
			nb = 32;
		else if (cc->core->id.rev < 26)
			nb = 16;
		else
			nb = (cc->core->id.rev >= 37) ? 32 : 24;
	} else {
		nb = 28;
	}
	if (nb == 32)
		return 0xffffffff;
	else
		return (1 << nb) - 1;
}