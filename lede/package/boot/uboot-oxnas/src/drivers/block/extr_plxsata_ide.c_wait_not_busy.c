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

/* Variables and functions */
 unsigned long ATA_STATUS_BSY_BIT ; 
 unsigned long SATA_COMMAND_BIT ; 
 int SATA_ORB2_OFF ; 
 unsigned long** sata_regs_base ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int wait_not_busy(int device, unsigned long timeout_secs)
{
	int busy = 1;
	unsigned long loops = (timeout_secs * 1000) / 50;
	do {
		// Test the ATA status register BUSY flag
		if (!((*(sata_regs_base[device] + SATA_ORB2_OFF)
			>> SATA_COMMAND_BIT) & (1UL << ATA_STATUS_BSY_BIT))) {
			/* Not busy, so stop polling */
			busy = 0;
			break;
		}

		// Wait for 50mS before sampling ATA status register again
		udelay(50000);
	} while (--loops);

	return busy;
}