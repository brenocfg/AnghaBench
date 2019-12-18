#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct resource_list_entry {int dummy; } ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  msix_alloc; } ;
struct TYPE_4__ {int /*<<< orphan*/  msi_alloc; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdrtype; int /*<<< orphan*/  intpin; int /*<<< orphan*/  intline; TYPE_2__ msix; TYPE_1__ msi; } ;
struct pci_devinfo {TYPE_3__ cfg; struct resource_list resources; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  TYPE_3__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIM_HDRTYPE_BRIDGE ; 
#define  PCIR_IOBASEL_1 134 
#define  PCIR_MEMBASE_1 133 
#define  PCIR_PMBASEL_1 132 
 int /*<<< orphan*/  PCI_INTERRUPT_VALID (int /*<<< orphan*/ ) ; 
#define  PCI_RES_BUS 131 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 struct resource* bus_generic_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct resource* pci_alloc_secbus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_assign_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* pci_reserve_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* resource_list_alloc (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

struct resource *
pci_alloc_multi_resource(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_long num,
    u_int flags)
{
	struct pci_devinfo *dinfo;
	struct resource_list *rl;
	struct resource_list_entry *rle;
	struct resource *res;
	pcicfgregs *cfg;

	/*
	 * Perform lazy resource allocation
	 */
	dinfo = device_get_ivars(child);
	rl = &dinfo->resources;
	cfg = &dinfo->cfg;
	switch (type) {
#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	case PCI_RES_BUS:
		return (pci_alloc_secbus(dev, child, rid, start, end, count,
		    flags));
#endif
	case SYS_RES_IRQ:
		/*
		 * Can't alloc legacy interrupt once MSI messages have
		 * been allocated.
		 */
		if (*rid == 0 && (cfg->msi.msi_alloc > 0 ||
		    cfg->msix.msix_alloc > 0))
			return (NULL);

		/*
		 * If the child device doesn't have an interrupt
		 * routed and is deserving of an interrupt, try to
		 * assign it one.
		 */
		if (*rid == 0 && !PCI_INTERRUPT_VALID(cfg->intline) &&
		    (cfg->intpin != 0))
			pci_assign_interrupt(dev, child, 0);
		break;
	case SYS_RES_IOPORT:
	case SYS_RES_MEMORY:
#ifdef NEW_PCIB
		/*
		 * PCI-PCI bridge I/O window resources are not BARs.
		 * For those allocations just pass the request up the
		 * tree.
		 */
		if (cfg->hdrtype == PCIM_HDRTYPE_BRIDGE) {
			switch (*rid) {
			case PCIR_IOBASEL_1:
			case PCIR_MEMBASE_1:
			case PCIR_PMBASEL_1:
				/*
				 * XXX: Should we bother creating a resource
				 * list entry?
				 */
				return (bus_generic_alloc_resource(dev, child,
				    type, rid, start, end, count, flags));
			}
		}
#endif
		/* Reserve resources for this BAR if needed. */
		rle = resource_list_find(rl, type, *rid);
		if (rle == NULL) {
			res = pci_reserve_map(dev, child, type, rid, start, end,
			    count, num, flags);
			if (res == NULL)
				return (NULL);
		}
	}
	return (resource_list_alloc(rl, dev, child, type, rid,
	    start, end, count, flags));
}