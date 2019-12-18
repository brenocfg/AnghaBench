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
typedef  int u_int32_t ;
struct ata_pci_controller {int channels; int ichannels; scalar_t__ legacy; scalar_t__ (* chipinit ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  r_rid1; int /*<<< orphan*/  r_type1; int /*<<< orphan*/  r_res1; int /*<<< orphan*/ * dev; int /*<<< orphan*/  ch_detach; int /*<<< orphan*/  ch_attach; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BMADDR_RID ; 
 int ENXIO ; 
 int IOMASK ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  ata_devclass ; 
 scalar_t__ ata_legacy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_pci_ch_attach ; 
 int /*<<< orphan*/  ata_pci_ch_detach ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int devclass_find_free_unit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

int
ata_pci_attach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);
    device_t child;
    u_int32_t cmd;
    int unit;

    /* do chipset specific setups only needed once */
    ctlr->legacy = ata_legacy(dev);
    if (ctlr->legacy || pci_read_config(dev, PCIR_BAR(2), 4) & IOMASK)
	ctlr->channels = 2;
    else
	ctlr->channels = 1;
    ctlr->ichannels = -1;
    ctlr->ch_attach = ata_pci_ch_attach;
    ctlr->ch_detach = ata_pci_ch_detach;
    ctlr->dev = dev;

    /* if needed try to enable busmastering */
    pci_enable_busmaster(dev);
    cmd = pci_read_config(dev, PCIR_COMMAND, 2);

    /* if busmastering mode "stuck" use it */
    if ((cmd & PCIM_CMD_BUSMASTEREN) == PCIM_CMD_BUSMASTEREN) {
	ctlr->r_type1 = SYS_RES_IOPORT;
	ctlr->r_rid1 = ATA_BMADDR_RID;
	ctlr->r_res1 = bus_alloc_resource_any(dev, ctlr->r_type1, &ctlr->r_rid1,
					      RF_ACTIVE);
    }

    if (ctlr->chipinit(dev))
	return ENXIO;

    /* attach all channels on this controller */
    for (unit = 0; unit < ctlr->channels; unit++) {
	if ((ctlr->ichannels & (1 << unit)) == 0)
	    continue;
	child = device_add_child(dev, "ata",
	    ((unit == 0 || unit == 1) && ctlr->legacy) ?
	    unit : devclass_find_free_unit(ata_devclass, 2));
	if (child == NULL)
	    device_printf(dev, "failed to add ata child device\n");
	else
	    device_set_ivars(child, (void *)(intptr_t)unit);
    }
    bus_generic_attach(dev);
    return 0;
}