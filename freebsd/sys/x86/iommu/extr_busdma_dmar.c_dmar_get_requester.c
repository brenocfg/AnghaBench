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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  scalar_t__ devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCIEM_FLAGS_TYPE ; 
 int PCIEM_TYPE_PCI_BRIDGE ; 
 scalar_t__ PCIER_FLAGS ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int PCI_RID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ *) ; 
 int pci_get_rid (int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ *,scalar_t__,int) ; 

device_t
dmar_get_requester(device_t dev, uint16_t *rid)
{
	devclass_t pci_class;
	device_t l, pci, pcib, pcip, pcibp, requester;
	int cap_offset;
	uint16_t pcie_flags;
	bool bridge_is_pcie;

	pci_class = devclass_find("pci");
	l = requester = dev;

	*rid = pci_get_rid(dev);

	/*
	 * Walk the bridge hierarchy from the target device to the
	 * host port to find the translating bridge nearest the DMAR
	 * unit.
	 */
	for (;;) {
		pci = device_get_parent(l);
		KASSERT(pci != NULL, ("dmar_get_requester(%s): NULL parent "
		    "for %s", device_get_name(dev), device_get_name(l)));
		KASSERT(device_get_devclass(pci) == pci_class,
		    ("dmar_get_requester(%s): non-pci parent %s for %s",
		    device_get_name(dev), device_get_name(pci),
		    device_get_name(l)));

		pcib = device_get_parent(pci);
		KASSERT(pcib != NULL, ("dmar_get_requester(%s): NULL bridge "
		    "for %s", device_get_name(dev), device_get_name(pci)));

		/*
		 * The parent of our "bridge" isn't another PCI bus,
		 * so pcib isn't a PCI->PCI bridge but rather a host
		 * port, and the requester ID won't be translated
		 * further.
		 */
		pcip = device_get_parent(pcib);
		if (device_get_devclass(pcip) != pci_class)
			break;
		pcibp = device_get_parent(pcip);

		if (pci_find_cap(l, PCIY_EXPRESS, &cap_offset) == 0) {
			/*
			 * Do not stop the loop even if the target
			 * device is PCIe, because it is possible (but
			 * unlikely) to have a PCI->PCIe bridge
			 * somewhere in the hierarchy.
			 */
			l = pcib;
		} else {
			/*
			 * Device is not PCIe, it cannot be seen as a
			 * requester by DMAR unit.  Check whether the
			 * bridge is PCIe.
			 */
			bridge_is_pcie = pci_find_cap(pcib, PCIY_EXPRESS,
			    &cap_offset) == 0;
			requester = pcib;

			/*
			 * Check for a buggy PCIe/PCI bridge that
			 * doesn't report the express capability.  If
			 * the bridge above it is express but isn't a
			 * PCI bridge, then we know pcib is actually a
			 * PCIe/PCI bridge.
			 */
			if (!bridge_is_pcie && pci_find_cap(pcibp,
			    PCIY_EXPRESS, &cap_offset) == 0) {
				pcie_flags = pci_read_config(pcibp,
				    cap_offset + PCIER_FLAGS, 2);
				if ((pcie_flags & PCIEM_FLAGS_TYPE) !=
				    PCIEM_TYPE_PCI_BRIDGE)
					bridge_is_pcie = true;
			}

			if (bridge_is_pcie) {
				/*
				 * The current device is not PCIe, but
				 * the bridge above it is.  This is a
				 * PCIe->PCI bridge.  Assume that the
				 * requester ID will be the secondary
				 * bus number with slot and function
				 * set to zero.
				 *
				 * XXX: Doesn't handle the case where
				 * the bridge is PCIe->PCI-X, and the
				 * bridge will only take ownership of
				 * requests in some cases.  We should
				 * provide context entries with the
				 * same page tables for taken and
				 * non-taken transactions.
				 */
				*rid = PCI_RID(pci_get_bus(l), 0, 0);
				l = pcibp;
			} else {
				/*
				 * Neither the device nor the bridge
				 * above it are PCIe.  This is a
				 * conventional PCI->PCI bridge, which
				 * will use the bridge's BSF as the
				 * requester ID.
				 */
				*rid = pci_get_rid(pcib);
				l = pcib;
			}
		}
	}
	return (requester);
}