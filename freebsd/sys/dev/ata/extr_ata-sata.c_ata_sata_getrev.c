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
struct ata_channel {TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ res; } ;

/* Variables and functions */
 int ATA_IDX_INL (struct ata_channel*,size_t) ; 
 size_t ATA_SSTATUS ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

int
ata_sata_getrev(device_t dev, int target)
{
	struct ata_channel *ch = device_get_softc(dev);

	if (ch->r_io[ATA_SSTATUS].res)
		return ((ATA_IDX_INL(ch, ATA_SSTATUS) & 0x0f0) >> 4);
	return (0xff);
}