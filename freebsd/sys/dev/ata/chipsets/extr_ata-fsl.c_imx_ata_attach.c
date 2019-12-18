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
struct ata_pci_controller {int channels; int ichannels; scalar_t__ legacy; int /*<<< orphan*/  setmode; int /*<<< orphan*/  ch_attach; scalar_t__ r_rid1; int /*<<< orphan*/  r_type1; int /*<<< orphan*/  r_res1; int /*<<< orphan*/ * dev; int /*<<< orphan*/  ch_detach; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ata_devclass ; 
 scalar_t__ ata_legacy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_pci_ch_attach ; 
 int /*<<< orphan*/  ata_pci_ch_detach ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int devclass_find_free_unit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  imx_ata_ch_attach ; 
 int /*<<< orphan*/  imx_ata_intr ; 
 int /*<<< orphan*/  imx_ata_setmode ; 

__attribute__((used)) static int
imx_ata_attach(device_t dev)
{
	struct ata_pci_controller *ctrl;
	device_t child;
	int unit;

	ctrl = device_get_softc(dev);
	/* do chipset specific setups only needed once */
	ctrl->legacy = ata_legacy(dev);
	ctrl->channels = 1;
	ctrl->ichannels = -1;
	ctrl->ch_attach = ata_pci_ch_attach;
	ctrl->ch_detach = ata_pci_ch_detach;
	ctrl->dev = dev;

	ctrl->r_type1 = SYS_RES_MEMORY;
	ctrl->r_rid1 = 0;
	ctrl->r_res1 = bus_alloc_resource_any(dev, ctrl->r_type1,
	    &ctrl->r_rid1, RF_ACTIVE);

	if (ata_setup_interrupt(dev, imx_ata_intr)) {
		device_printf(dev, "failed to setup interrupt\n");
    		return ENXIO;
	}

	ctrl->channels = 1;

	ctrl->ch_attach = imx_ata_ch_attach;
	ctrl->setmode = imx_ata_setmode;

	/* attach all channels on this controller */
	unit = 0;
	child = device_add_child(dev, "ata", ((unit == 0) && ctrl->legacy) ?
		    unit : devclass_find_free_unit(ata_devclass, 2));
	if (child == NULL)
		device_printf(dev, "failed to add ata child device\n");
	else
		device_set_ivars(child, (void *)(intptr_t)unit);

	bus_generic_attach(dev);
	return 0;
}