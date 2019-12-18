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
typedef  int u16 ;
struct TYPE_3__ {unsigned int vpd_cap_addr; } ;
struct TYPE_4__ {TYPE_1__ pci; } ;
struct adapter {int vpd_flag; scalar_t__ vpd_busy; TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_DELAY ; 
 int EEPROM_MAX_POLL ; 
 int ETIMEDOUT ; 
 scalar_t__ PCI_VPD_ADDR ; 
 int PCI_VPD_ADDR_F ; 
 int /*<<< orphan*/  t4_os_pci_read_cfg2 (struct adapter*,scalar_t__,int*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t4_seeprom_wait(struct adapter *adapter)
{
	unsigned int base = adapter->params.pci.vpd_cap_addr;
	int max_poll;

	/*
	 * If no VPD Access is in flight, we can just return success right
	 * away.
	 */
	if (!adapter->vpd_busy)
		return 0;

	/*
	 * Poll the VPD Capability Address/Flag register waiting for it
	 * to indicate that the operation is complete.
	 */
	max_poll = EEPROM_MAX_POLL;
	do {
		u16 val;

		udelay(EEPROM_DELAY);
		t4_os_pci_read_cfg2(adapter, base + PCI_VPD_ADDR, &val);

		/*
		 * If the operation is complete, mark the VPD as no longer
		 * busy and return success.
		 */
		if ((val & PCI_VPD_ADDR_F) == adapter->vpd_flag) {
			adapter->vpd_busy = 0;
			return 0;
		}
	} while (--max_poll);

	/*
	 * Failure!  Note that we leave the VPD Busy status set in order to
	 * avoid pushing a new VPD Access request into the VPD Capability till
	 * the current operation eventually succeeds.  It's a bug to issue a
	 * new request when an existing request is in flight and will result
	 * in corrupt hardware state.
	 */
	return -ETIMEDOUT;
}