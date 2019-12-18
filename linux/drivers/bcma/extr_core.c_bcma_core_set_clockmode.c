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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ id; } ;
struct bcma_device {int /*<<< orphan*/  bus; TYPE_1__ id; } ;
typedef  enum bcma_clkmode { ____Placeholder_bcma_clkmode } bcma_clkmode ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CLKCTLST ; 
 int /*<<< orphan*/  BCMA_CLKCTLST_FORCEHT ; 
 int BCMA_CLKCTLST_HAVEHT ; 
#define  BCMA_CLKMODE_DYNAMIC 129 
#define  BCMA_CLKMODE_FAST 128 
 scalar_t__ BCMA_CORE_80211 ; 
 scalar_t__ BCMA_CORE_CHIPCOMMON ; 
 scalar_t__ BCMA_CORE_PCIE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bcma_err (int /*<<< orphan*/ ,char*) ; 
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set32 (struct bcma_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void bcma_core_set_clockmode(struct bcma_device *core,
			     enum bcma_clkmode clkmode)
{
	u16 i;

	WARN_ON(core->id.id != BCMA_CORE_CHIPCOMMON &&
		core->id.id != BCMA_CORE_PCIE &&
		core->id.id != BCMA_CORE_80211);

	switch (clkmode) {
	case BCMA_CLKMODE_FAST:
		bcma_set32(core, BCMA_CLKCTLST, BCMA_CLKCTLST_FORCEHT);
		usleep_range(64, 300);
		for (i = 0; i < 1500; i++) {
			if (bcma_read32(core, BCMA_CLKCTLST) &
			    BCMA_CLKCTLST_HAVEHT) {
				i = 0;
				break;
			}
			udelay(10);
		}
		if (i)
			bcma_err(core->bus, "HT force timeout\n");
		break;
	case BCMA_CLKMODE_DYNAMIC:
		bcma_set32(core, BCMA_CLKCTLST, ~BCMA_CLKCTLST_FORCEHT);
		break;
	}
}