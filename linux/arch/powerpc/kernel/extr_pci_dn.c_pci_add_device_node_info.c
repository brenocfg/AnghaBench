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
typedef  int u32 ;
struct pci_dn {int busno; int devfn; int vendor_id; int device_id; int class_code; TYPE_1__* parent; int /*<<< orphan*/  list; int /*<<< orphan*/  child_list; int /*<<< orphan*/  pci_ext_config_space; int /*<<< orphan*/  pe_number; struct pci_controller* phb; } ;
struct pci_controller {int dummy; } ;
struct eeh_dev {int dummy; } ;
struct device_node {struct pci_dn* data; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  child_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IODA_INVALID_PE ; 
 TYPE_1__* PCI_DN (struct device_node*) ; 
 struct eeh_dev* eeh_dev_init (struct pci_dn*) ; 
 int /*<<< orphan*/  kfree (struct pci_dn*) ; 
 struct pci_dn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_read_number (int /*<<< orphan*/  const*,int) ; 

struct pci_dn *pci_add_device_node_info(struct pci_controller *hose,
					struct device_node *dn)
{
	const __be32 *type = of_get_property(dn, "ibm,pci-config-space-type", NULL);
	const __be32 *regs;
	struct device_node *parent;
	struct pci_dn *pdn;
#ifdef CONFIG_EEH
	struct eeh_dev *edev;
#endif

	pdn = kzalloc(sizeof(*pdn), GFP_KERNEL);
	if (pdn == NULL)
		return NULL;
	dn->data = pdn;
	pdn->phb = hose;
	pdn->pe_number = IODA_INVALID_PE;
	regs = of_get_property(dn, "reg", NULL);
	if (regs) {
		u32 addr = of_read_number(regs, 1);

		/* First register entry is addr (00BBSS00)  */
		pdn->busno = (addr >> 16) & 0xff;
		pdn->devfn = (addr >> 8) & 0xff;
	}

	/* vendor/device IDs and class code */
	regs = of_get_property(dn, "vendor-id", NULL);
	pdn->vendor_id = regs ? of_read_number(regs, 1) : 0;
	regs = of_get_property(dn, "device-id", NULL);
	pdn->device_id = regs ? of_read_number(regs, 1) : 0;
	regs = of_get_property(dn, "class-code", NULL);
	pdn->class_code = regs ? of_read_number(regs, 1) : 0;

	/* Extended config space */
	pdn->pci_ext_config_space = (type && of_read_number(type, 1) == 1);

	/* Create EEH device */
#ifdef CONFIG_EEH
	edev = eeh_dev_init(pdn);
	if (!edev) {
		kfree(pdn);
		return NULL;
	}
#endif

	/* Attach to parent node */
	INIT_LIST_HEAD(&pdn->child_list);
	INIT_LIST_HEAD(&pdn->list);
	parent = of_get_parent(dn);
	pdn->parent = parent ? PCI_DN(parent) : NULL;
	if (pdn->parent)
		list_add_tail(&pdn->list, &pdn->parent->child_list);

	return pdn;
}