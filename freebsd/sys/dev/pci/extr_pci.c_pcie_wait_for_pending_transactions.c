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
typedef  int uint16_t ;
typedef  int u_int ;
struct TYPE_3__ {int pcie_location; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_HARDCLOCK ; 
 int PCIEM_STA_TRANSACTION_PND ; 
 scalar_t__ PCIER_DEVICE_STA ; 
 int SBT_1MS ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_sbt (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

bool
pcie_wait_for_pending_transactions(device_t dev, u_int max_delay)
{
	struct pci_devinfo *dinfo = device_get_ivars(dev);
	uint16_t sta;
	int cap;

	cap = dinfo->cfg.pcie.pcie_location;
	if (cap == 0)
		return (true);

	sta = pci_read_config(dev, cap + PCIER_DEVICE_STA, 2);
	while (sta & PCIEM_STA_TRANSACTION_PND) {
		if (max_delay == 0)
			return (false);

		/* Poll once every 100 milliseconds up to the timeout. */
		if (max_delay > 100) {
			pause_sbt("pcietp", 100 * SBT_1MS, 0, C_HARDCLOCK);
			max_delay -= 100;
		} else {
			pause_sbt("pcietp", max_delay * SBT_1MS, 0,
			    C_HARDCLOCK);
			max_delay = 0;
		}
		sta = pci_read_config(dev, cap + PCIER_DEVICE_STA, 2);
	}

	return (true);
}