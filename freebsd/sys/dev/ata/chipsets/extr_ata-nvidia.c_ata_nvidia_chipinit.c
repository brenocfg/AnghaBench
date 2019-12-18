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
struct ata_pci_controller {int r_rid2; void* setmode; int /*<<< orphan*/  getrev; int /*<<< orphan*/  r_res2; TYPE_1__* chip; int /*<<< orphan*/  reset; int /*<<< orphan*/  ch_detach; int /*<<< orphan*/  ch_attach; int /*<<< orphan*/  r_type2; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg1; scalar_t__ max_dma; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_OUTB (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ATA_SA150 ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int NV4 ; 
 int NVAHCI ; 
 int NVQ ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 int /*<<< orphan*/  ata_nvidia_ch_attach ; 
 int /*<<< orphan*/  ata_nvidia_ch_attach_dumb ; 
 int /*<<< orphan*/  ata_nvidia_reset ; 
 void* ata_nvidia_setmode ; 
 int /*<<< orphan*/  ata_pci_ch_detach ; 
 int /*<<< orphan*/  ata_sata_getrev ; 
 void* ata_sata_setmode ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_nvidia_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;

    if (ctlr->chip->cfg1 & NVAHCI) {
	ctlr->ch_attach = ata_nvidia_ch_attach_dumb;
	ctlr->setmode = ata_sata_setmode;
    } else if (ctlr->chip->max_dma >= ATA_SA150) {
	if (pci_read_config(dev, PCIR_BAR(5), 1) & 1)
	    ctlr->r_type2 = SYS_RES_IOPORT;
	else
	    ctlr->r_type2 = SYS_RES_MEMORY;
	ctlr->r_rid2 = PCIR_BAR(5);
	if ((ctlr->r_res2 = bus_alloc_resource_any(dev, ctlr->r_type2,
						   &ctlr->r_rid2, RF_ACTIVE))) {
	    int offset = ctlr->chip->cfg1 & NV4 ? 0x0440 : 0x0010;

	    ctlr->ch_attach = ata_nvidia_ch_attach;
	    ctlr->ch_detach = ata_pci_ch_detach;
	    ctlr->reset = ata_nvidia_reset;

	    /* enable control access */
	    pci_write_config(dev, 0x50, pci_read_config(dev, 0x50, 1) | 0x04,1);
	    /* MCP55 seems to need some time to allow r_res2 read. */
	    DELAY(10);
	    if (ctlr->chip->cfg1 & NVQ) {
		/* clear interrupt status */
		ATA_OUTL(ctlr->r_res2, offset, 0x00ff00ff);

		/* enable device and PHY state change interrupts */
		ATA_OUTL(ctlr->r_res2, offset + 4, 0x000d000d);

		/* disable NCQ support */
		ATA_OUTL(ctlr->r_res2, 0x0400,
			 ATA_INL(ctlr->r_res2, 0x0400) & 0xfffffff9);
	    } 
	    else {
		/* clear interrupt status */
		ATA_OUTB(ctlr->r_res2, offset, 0xff);

		/* enable device and PHY state change interrupts */
		ATA_OUTB(ctlr->r_res2, offset + 1, 0xdd);
	    }
	}
	ctlr->setmode = ata_sata_setmode;
	ctlr->getrev = ata_sata_getrev;
    }
    else {
	/* disable prefetch, postwrite */
	pci_write_config(dev, 0x51, pci_read_config(dev, 0x51, 1) & 0x0f, 1);
	ctlr->setmode = ata_nvidia_setmode;
    }
    return 0;
}