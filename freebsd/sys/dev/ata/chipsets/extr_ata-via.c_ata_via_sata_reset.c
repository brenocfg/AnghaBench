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
typedef  int uint8_t ;
struct ata_channel {scalar_t__ unit; scalar_t__ devices; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_DRIVE ; 
 int ATA_D_IBM ; 
 int ATA_D_LBA ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_MASTER ; 
 int /*<<< orphan*/  ATA_SLAVE ; 
 int /*<<< orphan*/  ATA_STATUS ; 
 int ATA_S_BUSY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ata_generic_reset (int /*<<< orphan*/ ) ; 
 int ata_sata_phy_reset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_via_sata_reset(device_t dev)
{
	struct ata_channel *ch = device_get_softc(dev);
	int devs, count;
	uint8_t status;

	if (ch->unit == 0) {
		devs = ata_sata_phy_reset(dev, 0, 0);
		count = 0;
		do {
			ATA_IDX_OUTB(ch, ATA_DRIVE, ATA_D_IBM | ATA_D_LBA |
			    ATA_DEV(ATA_MASTER));
			DELAY(1000);
			status = ATA_IDX_INB(ch, ATA_STATUS);
			count++;
		} while (status & ATA_S_BUSY && count < 100);

		devs += ata_sata_phy_reset(dev, 1, 0);
		count = 0;
		do {
			ATA_IDX_OUTB(ch, ATA_DRIVE, ATA_D_IBM | ATA_D_LBA |
			    ATA_DEV(ATA_SLAVE));
			DELAY(1000);
			status = ATA_IDX_INB(ch, ATA_STATUS);
			count++;
		} while (status & ATA_S_BUSY && count < 100);
	} else
		devs = 1;
	if (devs)
		ata_generic_reset(dev);
	else
		ch->devices = 0;
}