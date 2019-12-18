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
struct pci_controller {int /*<<< orphan*/  is_dynamic; struct device_node* dn; int /*<<< orphan*/  list_node; int /*<<< orphan*/  global_number; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  PHB_SET_NODE (struct pci_controller*,int) ; 
 int /*<<< orphan*/  get_phb_number (struct device_node*) ; 
 int /*<<< orphan*/  hose_list ; 
 int /*<<< orphan*/  hose_spinlock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_online (int) ; 
 int of_node_to_nid (struct device_node*) ; 
 int /*<<< orphan*/  slab_is_available () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct pci_controller* zalloc_maybe_bootmem (int,int /*<<< orphan*/ ) ; 

struct pci_controller *pcibios_alloc_controller(struct device_node *dev)
{
	struct pci_controller *phb;

	phb = zalloc_maybe_bootmem(sizeof(struct pci_controller), GFP_KERNEL);
	if (phb == NULL)
		return NULL;
	spin_lock(&hose_spinlock);
	phb->global_number = get_phb_number(dev);
	list_add_tail(&phb->list_node, &hose_list);
	spin_unlock(&hose_spinlock);
	phb->dn = dev;
	phb->is_dynamic = slab_is_available();
#ifdef CONFIG_PPC64
	if (dev) {
		int nid = of_node_to_nid(dev);

		if (nid < 0 || !node_online(nid))
			nid = NUMA_NO_NODE;

		PHB_SET_NODE(phb, nid);
	}
#endif
	return phb;
}