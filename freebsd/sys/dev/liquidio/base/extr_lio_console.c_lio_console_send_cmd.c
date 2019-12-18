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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_BOOTLOADER_PCI_READ_BUFFER_DATA_ADDR ; 
 int /*<<< orphan*/  LIO_BOOTLOADER_PCI_READ_BUFFER_LEN_ADDR ; 
 int /*<<< orphan*/  LIO_BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR ; 
 int LIO_BOOTLOADER_PCI_WRITE_BUFFER_STR_LEN ; 
 int LIO_PCI_IO_BUF_OWNER_OCTEON ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,char*) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,...) ; 
 int /*<<< orphan*/  lio_pci_write_core_mem (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lio_remote_lock () ; 
 int /*<<< orphan*/  lio_remote_unlock () ; 
 scalar_t__ lio_wait_for_bootloader (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_write_device_mem32 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
lio_console_send_cmd(struct octeon_device *oct, char *cmd_str,
		     uint32_t wait_hundredths)
{
	uint32_t	len = (uint32_t) strlen(cmd_str);

	lio_dev_dbg(oct, "sending \"%s\" to bootloader\n", cmd_str);

	if (len > LIO_BOOTLOADER_PCI_WRITE_BUFFER_STR_LEN - 1) {
		lio_dev_err(oct, "Command string too long, max length is: %d\n",
			    LIO_BOOTLOADER_PCI_WRITE_BUFFER_STR_LEN - 1);
		return (-1);
	}

	if (lio_wait_for_bootloader(oct, wait_hundredths)) {
		lio_dev_err(oct, "Bootloader not ready for command.\n");
		return (-1);
	}

	/* Write command to bootloader */
	lio_remote_lock();
	lio_pci_write_core_mem(oct, LIO_BOOTLOADER_PCI_READ_BUFFER_DATA_ADDR,
			       (uint8_t *) cmd_str, len);
	lio_write_device_mem32(oct, LIO_BOOTLOADER_PCI_READ_BUFFER_LEN_ADDR,
			       len);
	lio_write_device_mem32(oct, LIO_BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR,
			       LIO_PCI_IO_BUF_OWNER_OCTEON);

	/*
	 * Bootloader should accept command very quickly if it really was
	 * ready
	 */
	if (lio_wait_for_bootloader(oct, 200)) {
		lio_remote_unlock();
		lio_dev_err(oct, "Bootloader did not accept command.\n");
		return (-1);
	}

	lio_remote_unlock();
	return (0);
}