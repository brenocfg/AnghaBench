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
typedef  int u32 ;
struct device_node {struct device_node* sibling; struct device_node* parent; struct device_node* child; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_CARDBUS ; 
 int PCI_CLASS_BRIDGE_PCI ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_read_number (int /*<<< orphan*/  const*,int) ; 

void *pci_traverse_device_nodes(struct device_node *start,
				void *(*fn)(struct device_node *, void *),
				void *data)
{
	struct device_node *dn, *nextdn;
	void *ret;

	/* We started with a phb, iterate all childs */
	for (dn = start->child; dn; dn = nextdn) {
		const __be32 *classp;
		u32 class = 0;

		nextdn = NULL;
		classp = of_get_property(dn, "class-code", NULL);
		if (classp)
			class = of_read_number(classp, 1);

		if (fn) {
			ret = fn(dn, data);
			if (ret)
				return ret;
		}

		/* If we are a PCI bridge, go down */
		if (dn->child && ((class >> 8) == PCI_CLASS_BRIDGE_PCI ||
				  (class >> 8) == PCI_CLASS_BRIDGE_CARDBUS))
			/* Depth first...do children */
			nextdn = dn->child;
		else if (dn->sibling)
			/* ok, try next sibling instead. */
			nextdn = dn->sibling;
		if (!nextdn) {
			/* Walk up to next valid sibling. */
			do {
				dn = dn->parent;
				if (dn == start)
					return NULL;
			} while (dn->sibling == NULL);
			nextdn = dn->sibling;
		}
	}
	return NULL;
}