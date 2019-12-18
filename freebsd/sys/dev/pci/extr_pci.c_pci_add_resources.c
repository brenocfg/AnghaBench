#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct resource_list {int dummy; } ;
struct pci_quirk {int devid; scalar_t__ type; scalar_t__ arg1; } ;
struct TYPE_3__ {int device; int vendor; int nummaps; scalar_t__ intpin; int /*<<< orphan*/  intline; } ;
struct pci_devinfo {struct resource_list resources; TYPE_1__ cfg; } ;
typedef  TYPE_1__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCIC_SERIALBUS ; 
 scalar_t__ PCIC_STORAGE ; 
 scalar_t__ PCIP_SERIALBUS_USB_EHCI ; 
 scalar_t__ PCIP_SERIALBUS_USB_OHCI ; 
 scalar_t__ PCIP_SERIALBUS_USB_UHCI ; 
 scalar_t__ PCIP_SERIALBUS_USB_XHCI ; 
 scalar_t__ PCIP_STORAGE_IDE_MASTERDEV ; 
 scalar_t__ PCIR_BAR (int) ; 
 scalar_t__ PCIS_SERIALBUS_USB ; 
 scalar_t__ PCIS_STORAGE_IDE ; 
 scalar_t__ PCI_INTERRUPT_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_QUIRK_MAP_REG ; 
 scalar_t__ PCI_QUIRK_UNMAP_REG ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_early_takeover (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_early_takeover (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_add_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct resource_list*,int,int) ; 
 int /*<<< orphan*/  pci_add_resources_ea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_assign_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_ata_maps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource_list*,int,int) ; 
 scalar_t__ pci_ea_is_enabled (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_progif (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 struct pci_quirk* pci_quirks ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_reserve_secbus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct resource_list*) ; 
 scalar_t__ pci_usb_takeover ; 
 int /*<<< orphan*/ * resource_list_find (struct resource_list*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  uhci_early_takeover (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_early_takeover (int /*<<< orphan*/ ) ; 

void
pci_add_resources(device_t bus, device_t dev, int force, uint32_t prefetchmask)
{
	struct pci_devinfo *dinfo;
	pcicfgregs *cfg;
	struct resource_list *rl;
	const struct pci_quirk *q;
	uint32_t devid;
	int i;

	dinfo = device_get_ivars(dev);
	cfg = &dinfo->cfg;
	rl = &dinfo->resources;
	devid = (cfg->device << 16) | cfg->vendor;

	/* Allocate resources using Enhanced Allocation */
	pci_add_resources_ea(bus, dev, 0);

	/* ATA devices needs special map treatment */
	if ((pci_get_class(dev) == PCIC_STORAGE) &&
	    (pci_get_subclass(dev) == PCIS_STORAGE_IDE) &&
	    ((pci_get_progif(dev) & PCIP_STORAGE_IDE_MASTERDEV) ||
	     (!pci_read_config(dev, PCIR_BAR(0), 4) &&
	      !pci_read_config(dev, PCIR_BAR(2), 4))) )
		pci_ata_maps(bus, dev, rl, force, prefetchmask);
	else
		for (i = 0; i < cfg->nummaps;) {
			/* Skip resources already managed by EA */
			if ((resource_list_find(rl, SYS_RES_MEMORY, PCIR_BAR(i)) != NULL) ||
			    (resource_list_find(rl, SYS_RES_IOPORT, PCIR_BAR(i)) != NULL) ||
			    pci_ea_is_enabled(dev, PCIR_BAR(i))) {
				i++;
				continue;
			}

			/*
			 * Skip quirked resources.
			 */
			for (q = &pci_quirks[0]; q->devid != 0; q++)
				if (q->devid == devid &&
				    q->type == PCI_QUIRK_UNMAP_REG &&
				    q->arg1 == PCIR_BAR(i))
					break;
			if (q->devid != 0) {
				i++;
				continue;
			}
			i += pci_add_map(bus, dev, PCIR_BAR(i), rl, force,
			    prefetchmask & (1 << i));
		}

	/*
	 * Add additional, quirked resources.
	 */
	for (q = &pci_quirks[0]; q->devid != 0; q++)
		if (q->devid == devid && q->type == PCI_QUIRK_MAP_REG)
			pci_add_map(bus, dev, q->arg1, rl, force, 0);

	if (cfg->intpin > 0 && PCI_INTERRUPT_VALID(cfg->intline)) {
#ifdef __PCI_REROUTE_INTERRUPT
		/*
		 * Try to re-route interrupts. Sometimes the BIOS or
		 * firmware may leave bogus values in these registers.
		 * If the re-route fails, then just stick with what we
		 * have.
		 */
		pci_assign_interrupt(bus, dev, 1);
#else
		pci_assign_interrupt(bus, dev, 0);
#endif
	}

	if (pci_usb_takeover && pci_get_class(dev) == PCIC_SERIALBUS &&
	    pci_get_subclass(dev) == PCIS_SERIALBUS_USB) {
		if (pci_get_progif(dev) == PCIP_SERIALBUS_USB_XHCI)
			xhci_early_takeover(dev);
		else if (pci_get_progif(dev) == PCIP_SERIALBUS_USB_EHCI)
			ehci_early_takeover(dev);
		else if (pci_get_progif(dev) == PCIP_SERIALBUS_USB_OHCI)
			ohci_early_takeover(dev);
		else if (pci_get_progif(dev) == PCIP_SERIALBUS_USB_UHCI)
			uhci_early_takeover(dev);
	}

#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	/*
	 * Reserve resources for secondary bus ranges behind bridge
	 * devices.
	 */
	pci_reserve_secbus(bus, dev, cfg, rl);
#endif
}