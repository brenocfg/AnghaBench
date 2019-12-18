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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int pcie_location; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_HARDCLOCK ; 
 int PCIEM_CAP_FLR ; 
 int PCIEM_CTL_INITIATE_FLR ; 
 int PCIEM_STA_TRANSACTION_PND ; 
 scalar_t__ PCIER_DEVICE_CAP ; 
 scalar_t__ PCIER_DEVICE_CTL ; 
 scalar_t__ PCIER_DEVICE_STA ; 
 int PCIM_CMD_BUSMASTEREN ; 
 scalar_t__ PCIR_COMMAND ; 
 int SBT_1MS ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_sbt (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_printf (TYPE_2__*,char*,...) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int pcie_get_max_completion_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_wait_for_pending_transactions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
pcie_flr(device_t dev, u_int max_delay, bool force)
{
	struct pci_devinfo *dinfo = device_get_ivars(dev);
	uint16_t cmd, ctl;
	int compl_delay;
	int cap;

	cap = dinfo->cfg.pcie.pcie_location;
	if (cap == 0)
		return (false);

	if (!(pci_read_config(dev, cap + PCIER_DEVICE_CAP, 4) & PCIEM_CAP_FLR))
		return (false);

	/*
	 * Disable busmastering to prevent generation of new
	 * transactions while waiting for the device to go idle.  If
	 * the idle timeout fails, the command register is restored
	 * which will re-enable busmastering.
	 */
	cmd = pci_read_config(dev, PCIR_COMMAND, 2);
	pci_write_config(dev, PCIR_COMMAND, cmd & ~(PCIM_CMD_BUSMASTEREN), 2);
	if (!pcie_wait_for_pending_transactions(dev, max_delay)) {
		if (!force) {
			pci_write_config(dev, PCIR_COMMAND, cmd, 2);
			return (false);
		}
		pci_printf(&dinfo->cfg,
		    "Resetting with transactions pending after %d ms\n",
		    max_delay);

		/*
		 * Extend the post-FLR delay to cover the maximum
		 * Completion Timeout delay of anything in flight
		 * during the FLR delay.  Enforce a minimum delay of
		 * at least 10ms.
		 */
		compl_delay = pcie_get_max_completion_timeout(dev) / 1000;
		if (compl_delay < 10)
			compl_delay = 10;
	} else
		compl_delay = 0;

	/* Initiate the reset. */
	ctl = pci_read_config(dev, cap + PCIER_DEVICE_CTL, 2);
	pci_write_config(dev, cap + PCIER_DEVICE_CTL, ctl |
	    PCIEM_CTL_INITIATE_FLR, 2);

	/* Wait for 100ms. */
	pause_sbt("pcieflr", (100 + compl_delay) * SBT_1MS, 0, C_HARDCLOCK);

	if (pci_read_config(dev, cap + PCIER_DEVICE_STA, 2) &
	    PCIEM_STA_TRANSACTION_PND)
		pci_printf(&dinfo->cfg, "Transactions pending after FLR!\n");
	return (true);
}