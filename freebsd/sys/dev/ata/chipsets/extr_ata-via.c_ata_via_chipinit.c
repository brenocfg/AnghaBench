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
struct ata_pci_controller {int channels; int /*<<< orphan*/  setmode; TYPE_1__* chip; int /*<<< orphan*/  getrev; int /*<<< orphan*/  reset; int /*<<< orphan*/  ch_detach; int /*<<< orphan*/  ch_attach; int /*<<< orphan*/  r_rid2; int /*<<< orphan*/  r_type2; int /*<<< orphan*/  r_res2; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg2; scalar_t__ max_dma; } ;

/* Variables and functions */
 scalar_t__ ATA_SA150 ; 
 int DEV_BSIZE ; 
 int ENXIO ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int VIABAR ; 
 int VIABUG ; 
 int VIACLK ; 
 int VIASATA ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 int /*<<< orphan*/  ata_sata_getrev ; 
 int /*<<< orphan*/  ata_sata_setmode ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_via_ch_attach ; 
 int /*<<< orphan*/  ata_via_ch_detach ; 
 int /*<<< orphan*/  ata_via_new_setmode ; 
 int /*<<< orphan*/  ata_via_old_setmode ; 
 int /*<<< orphan*/  ata_via_reset ; 
 int /*<<< orphan*/  ata_via_sata_ch_attach ; 
 int /*<<< orphan*/  ata_via_sata_getrev ; 
 int /*<<< orphan*/  ata_via_sata_reset ; 
 int /*<<< orphan*/  ata_via_sata_setmode ; 
 int /*<<< orphan*/  ata_via_southbridge_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_via_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;

    /* 2 SATA with "SATA registers" at PCI config space + PATA on secondary */
    if (ctlr->chip->cfg2 & VIASATA) {
	ctlr->ch_attach = ata_via_sata_ch_attach;
	ctlr->setmode = ata_via_sata_setmode;
	ctlr->getrev = ata_via_sata_getrev;
	ctlr->reset = ata_via_sata_reset;
	return 0;
    }
    /* Legacy SATA/SATA+PATA with SATA registers in BAR(5). */
    if (ctlr->chip->max_dma >= ATA_SA150) {
	ctlr->r_type2 = SYS_RES_IOPORT;
	ctlr->r_rid2 = PCIR_BAR(5);
	if ((ctlr->r_res2 = bus_alloc_resource_any(dev, ctlr->r_type2,
						   &ctlr->r_rid2, RF_ACTIVE))) {
	    ctlr->ch_attach = ata_via_ch_attach;
	    ctlr->ch_detach = ata_via_ch_detach;
	    ctlr->reset = ata_via_reset;
	}
	if (ctlr->chip->cfg2 & VIABAR) {
	    ctlr->channels = 3;
	    ctlr->setmode = ata_via_new_setmode;
	} else
	    ctlr->setmode = ata_sata_setmode;
	ctlr->getrev = ata_sata_getrev;
	return 0;
    }

    /* prepare for ATA-66 on the 82C686a and 82C596b */
    if (ctlr->chip->cfg2 & VIACLK)
	pci_write_config(dev, 0x50, 0x030b030b, 4);       

    /* the southbridge might need the data corruption fix */
    if (ctlr->chip->cfg2 & VIABUG)
	ata_via_southbridge_fixup(dev);

    /* set fifo configuration half'n'half */
    pci_write_config(dev, 0x43, 
		     (pci_read_config(dev, 0x43, 1) & 0x90) | 0x2a, 1);

    /* set status register read retry */
    pci_write_config(dev, 0x44, pci_read_config(dev, 0x44, 1) | 0x08, 1);

    /* set DMA read & end-of-sector fifo flush */
    pci_write_config(dev, 0x46, 
		     (pci_read_config(dev, 0x46, 1) & 0x0c) | 0xf0, 1);

    /* set sector size */
    pci_write_config(dev, 0x60, DEV_BSIZE, 2);
    pci_write_config(dev, 0x68, DEV_BSIZE, 2);

    ctlr->setmode = ata_via_old_setmode;
    return 0;
}