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
typedef  int uint32_t ;
struct octeon_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIEM_CTL_INITIATE_FLR ; 
 int PCIEM_STA_TRANSACTION_PND ; 
 int PCIER_DEVICE_CTL ; 
 int PCIER_DEVICE_STA ; 
 int /*<<< orphan*/  PCIM_CMD_INTxDIS ; 
 int PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int /*<<< orphan*/  lio_dev_info (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_mdelay (int) ; 
 int /*<<< orphan*/  pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lio_pci_flr(struct octeon_device *oct)
{
	uint32_t	exppos, status;

	pci_find_cap(oct->device, PCIY_EXPRESS, &exppos);

	pci_save_state(oct->device);

	/* Quiesce the device completely */
	pci_write_config(oct->device, PCIR_COMMAND, PCIM_CMD_INTxDIS, 2);

	/* Wait for Transaction Pending bit clean */
	lio_mdelay(100);

	status = pci_read_config(oct->device, exppos + PCIER_DEVICE_STA, 2);
	if (status & PCIEM_STA_TRANSACTION_PND) {
		lio_dev_info(oct, "Function reset incomplete after 100ms, sleeping for 5 seconds\n");
		lio_mdelay(5);

		status = pci_read_config(oct->device, exppos + PCIER_DEVICE_STA, 2);
		if (status & PCIEM_STA_TRANSACTION_PND)
			lio_dev_info(oct, "Function reset still incomplete after 5s, reset anyway\n");
	}

	pci_write_config(oct->device, exppos + PCIER_DEVICE_CTL, PCIEM_CTL_INITIATE_FLR, 2);
	lio_mdelay(100);

	pci_restore_state(oct->device);
}