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
typedef  scalar_t__ uint32_t ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR ; 
 scalar_t__ LIO_PCI_IO_BUF_OWNER_HOST ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,scalar_t__) ; 
 scalar_t__ lio_mem_access_ok (struct octeon_device*) ; 
 scalar_t__ lio_read_device_mem32 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_sleep_timeout (int) ; 

int
lio_wait_for_bootloader(struct octeon_device *oct,
			uint32_t wait_time_hundredths)
{
	lio_dev_dbg(oct, "waiting %d0 ms for bootloader\n",
		    wait_time_hundredths);

	if (lio_mem_access_ok(oct))
		return (-1);

	while (wait_time_hundredths > 0 &&
	       lio_read_device_mem32(oct,
				LIO_BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR) !=
	       LIO_PCI_IO_BUF_OWNER_HOST) {
		if (--wait_time_hundredths <= 0)
			return (-1);

		lio_sleep_timeout(10);
	}

	return (0);
}