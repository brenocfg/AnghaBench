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
struct resource {scalar_t__ end; scalar_t__ start; } ;
struct pci_controller {int /*<<< orphan*/ * io_base_alloc; int /*<<< orphan*/ * dn; } ;
struct pci_bus {scalar_t__ self; struct resource** resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ _IO_BASE ; 
 int /*<<< orphan*/  __flush_hash_table_range (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  init_mm ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/ * pci_name (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

int pcibios_unmap_io_space(struct pci_bus *bus)
{
	struct pci_controller *hose;

	WARN_ON(bus == NULL);

	/* If this is not a PHB, we only flush the hash table over
	 * the area mapped by this bridge. We don't play with the PTE
	 * mappings since we might have to deal with sub-page alignments
	 * so flushing the hash table is the only sane way to make sure
	 * that no hash entries are covering that removed bridge area
	 * while still allowing other busses overlapping those pages
	 *
	 * Note: If we ever support P2P hotplug on Book3E, we'll have
	 * to do an appropriate TLB flush here too
	 */
	if (bus->self) {
#ifdef CONFIG_PPC_BOOK3S_64
		struct resource *res = bus->resource[0];
#endif

		pr_debug("IO unmapping for PCI-PCI bridge %s\n",
			 pci_name(bus->self));

#ifdef CONFIG_PPC_BOOK3S_64
		__flush_hash_table_range(&init_mm, res->start + _IO_BASE,
					 res->end + _IO_BASE + 1);
#endif
		return 0;
	}

	/* Get the host bridge */
	hose = pci_bus_to_host(bus);

	/* Check if we have IOs allocated */
	if (hose->io_base_alloc == NULL)
		return 0;

	pr_debug("IO unmapping for PHB %pOF\n", hose->dn);
	pr_debug("  alloc=0x%p\n", hose->io_base_alloc);

	/* This is a PHB, we fully unmap the IO area */
	vunmap(hose->io_base_alloc);

	return 0;
}