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
typedef  int /*<<< orphan*/  u_int ;
struct pci_devinfo {int dummy; } ;
struct TYPE_3__ {scalar_t__ intpin; } ;
struct TYPE_4__ {int /*<<< orphan*/  resources; TYPE_1__ cfg; } ;
struct ofw_pcibus_devinfo {TYPE_2__ opd_dinfo; int /*<<< orphan*/ * opd_dma_tag; int /*<<< orphan*/  opd_obdinfo; } ;
struct ofw_pci_register {int /*<<< orphan*/  phys_hi; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  pcir ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFW_PCI_PHYS_HI_DEVICE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFW_PCI_PHYS_HI_FUNCTION (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OF_getproplen (scalar_t__,char*) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  PCIB_WRITE_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PCIR_INTLINE ; 
 int PCI_INVALID_IRQ ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_intr_to_rl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_add_child (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_freecfg (struct pci_devinfo*) ; 
 scalar_t__ pci_read_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ofw_pcibus_enum_devtree(device_t dev, u_int domain, u_int busno)
{
	device_t pcib;
	struct ofw_pci_register pcir;
	struct ofw_pcibus_devinfo *dinfo;
	phandle_t node, child;
	u_int func, slot;
	int intline;

	pcib = device_get_parent(dev);
	node = ofw_bus_get_node(dev);

	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		if (OF_getencprop(child, "reg", (pcell_t *)&pcir,
		    sizeof(pcir)) == -1)
			continue;
		slot = OFW_PCI_PHYS_HI_DEVICE(pcir.phys_hi);
		func = OFW_PCI_PHYS_HI_FUNCTION(pcir.phys_hi);

		/* Some OFW device trees contain dupes. */
		if (pci_find_dbsf(domain, busno, slot, func) != NULL)
			continue;

		/*
		 * The preset in the intline register is usually bogus.  Reset
		 * it such that the PCI code will reroute the interrupt if
		 * needed.
		 */

		intline = PCI_INVALID_IRQ;
		if (OF_getproplen(child, "interrupts") > 0)
			intline = 0;
		PCIB_WRITE_CONFIG(pcib, busno, slot, func, PCIR_INTLINE,
		    intline, 1);

		/*
		 * Now set up the PCI and OFW bus layer devinfo and add it
		 * to the PCI bus.
		 */

		dinfo = (struct ofw_pcibus_devinfo *)pci_read_device(pcib, dev,
		    domain, busno, slot, func);
		if (dinfo == NULL)
			continue;
		if (ofw_bus_gen_setup_devinfo(&dinfo->opd_obdinfo, child) !=
		    0) {
			pci_freecfg((struct pci_devinfo *)dinfo);
			continue;
		}
		dinfo->opd_dma_tag = NULL;
		pci_add_child(dev, (struct pci_devinfo *)dinfo);

		/*
		 * Some devices don't have an intpin set, but do have
		 * interrupts. These are fully specified, and set in the
		 * interrupts property, so add that value to the device's
		 * resource list.
		 */
		if (dinfo->opd_dinfo.cfg.intpin == 0)
			ofw_bus_intr_to_rl(dev, child,
				&dinfo->opd_dinfo.resources, NULL);
	}
}