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
typedef  int uint8_t ;
struct ata_pci_controller {int channels; int ichannels; int /*<<< orphan*/  setmode; int /*<<< orphan*/  ch_attach; void* chipset_data; TYPE_1__* chip; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {scalar_t__ cfg1; int chipid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ATI_ID ; 
#define  ATA_ATI_IXP600 129 
#define  ATA_ATI_IXP700 128 
 scalar_t__ ATI_AHCI ; 
 int ENXIO ; 
 int /*<<< orphan*/  ata_ati_dumb_ch_attach ; 
 int /*<<< orphan*/  ata_ati_ixp700_ch_attach ; 
 int /*<<< orphan*/  ata_ati_setmode ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 int /*<<< orphan*/  ata_sata_setmode ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootverbose ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * pci_find_device (int /*<<< orphan*/ ,int) ; 
 int pci_read_config (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
ata_ati_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);
    device_t smbdev;
    uint8_t satacfg;

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;

    if (ctlr->chip->cfg1 == ATI_AHCI) {
	ctlr->ch_attach = ata_ati_dumb_ch_attach;
	ctlr->setmode = ata_sata_setmode;
	return (0);
    }
    switch (ctlr->chip->chipid) {
    case ATA_ATI_IXP600:
	/* IXP600 only has 1 PATA channel */
	ctlr->channels = 1;
	break;
    case ATA_ATI_IXP700:
	/*
	 * When "combined mode" is enabled, an additional PATA channel is
	 * emulated with two SATA ports and appears on this device.
	 * This mode can only be detected via SMB controller.
	 */
	smbdev = pci_find_device(ATA_ATI_ID, 0x4385);
	if (smbdev != NULL) {
	    satacfg = pci_read_config(smbdev, 0xad, 1);
	    if (bootverbose)
		device_printf(dev, "SATA controller %s (%s%s channel)\n",
		    (satacfg & 0x01) == 0 ? "disabled" : "enabled",
		    (satacfg & 0x08) == 0 ? "" : "combined mode, ",
		    (satacfg & 0x10) == 0 ? "primary" : "secondary");
	    ctlr->chipset_data = (void *)(uintptr_t)satacfg;
	    /*
	     * If SATA controller is enabled but combined mode is disabled,
	     * we have only one PATA channel.  Ignore a non-existent channel.
	     */
	    if ((satacfg & 0x09) == 0x01)
		ctlr->ichannels &= ~(1 << ((satacfg & 0x10) >> 4));
	    else {
	        ctlr->ch_attach = ata_ati_ixp700_ch_attach;
	    }
	}
	break;
    }

    ctlr->setmode = ata_ati_setmode;
    return 0;
}