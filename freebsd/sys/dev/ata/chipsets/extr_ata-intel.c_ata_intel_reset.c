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
typedef  int u_char ;
struct ata_pci_controller {TYPE_1__* chip; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pm_read; } ;
struct ata_channel {int flags; int devices; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int cfg1; } ;

/* Variables and functions */
 int ATA_ATAPI_MASTER ; 
 int ATA_ATA_MASTER ; 
 int ATA_ATA_SLAVE ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int* ATA_INTEL_SMAP (struct ata_pci_controller*,struct ata_channel*) ; 
 int ATA_NO_SLAVE ; 
 int ATA_SATA ; 
 int /*<<< orphan*/  ATA_STATUS ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int INTEL_6CH ; 
 int INTEL_6CH2 ; 
 void ata_generic_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_sata_phy_reset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ata_udelay (int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
ata_intel_reset(device_t dev)
{
	device_t parent = device_get_parent(dev);
	struct ata_pci_controller *ctlr = device_get_softc(parent);
	struct ata_channel *ch = device_get_softc(dev);
	int mask, pshift, timeout, devs;
	u_char *smap;
	uint16_t pcs;

	/* In combined mode, skip SATA stuff for PATA channel. */
	if ((ch->flags & ATA_SATA) == 0)
		return (ata_generic_reset(dev));

	/* Do hard-reset on respective SATA ports. */
	smap = ATA_INTEL_SMAP(ctlr, ch);
	mask = 1 << smap[0];
	if ((ch->flags & ATA_NO_SLAVE) == 0)
		mask |= (1 << smap[1]);
	pci_write_config(parent, 0x92,
	    pci_read_config(parent, 0x92, 2) & ~mask, 2);
	DELAY(100);
	pci_write_config(parent, 0x92,
	    pci_read_config(parent, 0x92, 2) | mask, 2);

	/* Wait up to 1 sec for "connect well". */
	if (ctlr->chip->cfg1 & (INTEL_6CH | INTEL_6CH2))
		pshift = 8;
	else
		pshift = 4;
	for (timeout = 0; timeout < 100 ; timeout++) {
		pcs = (pci_read_config(parent, 0x92, 2) >> pshift) & mask;
		if ((pcs == mask) && (ATA_IDX_INB(ch, ATA_STATUS) != 0xff))
			break;
		ata_udelay(10000);
	}

	if (bootverbose)
		device_printf(dev, "SATA reset: ports status=0x%02x\n", pcs);
	/* If any device found, do soft-reset. */
	if (ch->hw.pm_read != NULL) {
		devs = ata_sata_phy_reset(dev, 0, 2) ? ATA_ATA_MASTER : 0;
		if ((ch->flags & ATA_NO_SLAVE) == 0)
			devs |= ata_sata_phy_reset(dev, 1, 2) ?
			    ATA_ATA_SLAVE : 0;
	} else {
		devs = (pcs & (1 << smap[0])) ? ATA_ATA_MASTER : 0;
		if ((ch->flags & ATA_NO_SLAVE) == 0)
			devs |= (pcs & (1 << smap[1])) ?
			    ATA_ATA_SLAVE : 0;
	}
	if (devs) {
		ata_generic_reset(dev);
		/* Reset may give fake slave when only ATAPI master present. */
		ch->devices &= (devs | (devs * ATA_ATAPI_MASTER));
	} else
		ch->devices = 0;
}