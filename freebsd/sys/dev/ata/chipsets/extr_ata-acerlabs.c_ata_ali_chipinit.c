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
struct ata_pci_controller {void* setmode; int /*<<< orphan*/  reset; void* ch_detach; int /*<<< orphan*/  ch_attach; TYPE_1__* chip; struct ali_sata_resources* chipset_data; int /*<<< orphan*/  getrev; int /*<<< orphan*/  channels; } ;
struct ali_sata_resources {int /*<<< orphan*/ ** bars; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg2; int chiprev; int /*<<< orphan*/  cfg1; } ;

/* Variables and functions */
#define  ALI_NEW 130 
#define  ALI_OLD 129 
#define  ALI_SATA 128 
 int ENXIO ; 
 int /*<<< orphan*/  M_ATAPCI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  ata_ali_ch_attach ; 
 int /*<<< orphan*/  ata_ali_reset ; 
 int /*<<< orphan*/  ata_ali_sata_ch_attach ; 
 void* ata_ali_setmode ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 void* ata_pci_ch_detach ; 
 int /*<<< orphan*/  ata_sata_getrev ; 
 void* ata_sata_setmode ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct ali_sata_resources*,int /*<<< orphan*/ ) ; 
 struct ali_sata_resources* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_ali_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);
    struct ali_sata_resources *res;
    int i, rid;

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;

    switch (ctlr->chip->cfg2) {
    case ALI_SATA:
	ctlr->channels = ctlr->chip->cfg1;
	ctlr->ch_attach = ata_ali_sata_ch_attach;
	ctlr->ch_detach = ata_pci_ch_detach;
	ctlr->setmode = ata_sata_setmode;
	ctlr->getrev = ata_sata_getrev;

	/* Allocate resources for later use by channel attach routines. */
	res = malloc(sizeof(struct ali_sata_resources), M_ATAPCI, M_WAITOK);
	for (i = 0; i < 4; i++) {
		rid = PCIR_BAR(i);
		res->bars[i] = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid,
		    RF_ACTIVE);
		if (res->bars[i] == NULL) {
			device_printf(dev, "Failed to allocate BAR %d\n", i);
			for (i--; i >=0; i--)
				bus_release_resource(dev, SYS_RES_IOPORT,
				    PCIR_BAR(i), res->bars[i]);
			free(res, M_ATAPCI);
			return ENXIO;
		}
	}
	ctlr->chipset_data = res;
	break;

    case ALI_NEW:
	/* use device interrupt as byte count end */
	pci_write_config(dev, 0x4a, pci_read_config(dev, 0x4a, 1) | 0x20, 1);

	/* enable cable detection and UDMA support on revisions < 0xc7 */
	if (ctlr->chip->chiprev < 0xc7)
	    pci_write_config(dev, 0x4b, pci_read_config(dev, 0x4b, 1) |
		0x09, 1);

	/* enable ATAPI UDMA mode (even if we are going to do PIO) */
	pci_write_config(dev, 0x53, pci_read_config(dev, 0x53, 1) |
	    (ctlr->chip->chiprev >= 0xc7 ? 0x03 : 0x01), 1);

	/* only chips with revision > 0xc4 can do 48bit DMA */
	if (ctlr->chip->chiprev <= 0xc4)
	    device_printf(dev,
			  "using PIO transfers above 137GB as workaround for "
			  "48bit DMA access bug, expect reduced performance\n");
	ctlr->ch_attach = ata_ali_ch_attach;
	ctlr->ch_detach = ata_pci_ch_detach;
	ctlr->reset = ata_ali_reset;
	ctlr->setmode = ata_ali_setmode;
	break;

    case ALI_OLD:
	/* deactivate the ATAPI FIFO and enable ATAPI UDMA */
	pci_write_config(dev, 0x53, pci_read_config(dev, 0x53, 1) | 0x03, 1);
	ctlr->setmode = ata_ali_setmode;
	break;
    }
    return 0;
}