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
struct pci_dev {struct device_node* hdr_type; } ;
struct pci_bus {int dummy; } ;
struct eeh_dev {int mode; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EEH_DEV_REMOVED ; 
 int /*<<< orphan*/  PCI_DN (struct device_node*) ; 
 struct pci_dev* of_create_pci_dev (struct device_node*,struct pci_bus*,int) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int of_read_number (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (struct pci_bus*,int) ; 
 struct eeh_dev* pdn_to_eeh_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct device_node*) ; 

__attribute__((used)) static struct pci_dev *of_scan_pci_dev(struct pci_bus *bus,
			    struct device_node *dn)
{
	struct pci_dev *dev = NULL;
	const __be32 *reg;
	int reglen, devfn;
#ifdef CONFIG_EEH
	struct eeh_dev *edev = pdn_to_eeh_dev(PCI_DN(dn));
#endif

	pr_debug("  * %pOF\n", dn);
	if (!of_device_is_available(dn))
		return NULL;

	reg = of_get_property(dn, "reg", &reglen);
	if (reg == NULL || reglen < 20)
		return NULL;
	devfn = (of_read_number(reg, 1) >> 8) & 0xff;

	/* Check if the PCI device is already there */
	dev = pci_get_slot(bus, devfn);
	if (dev) {
		pci_dev_put(dev);
		return dev;
	}

	/* Device removed permanently ? */
#ifdef CONFIG_EEH
	if (edev && (edev->mode & EEH_DEV_REMOVED))
		return NULL;
#endif

	/* create a new pci_dev for this device */
	dev = of_create_pci_dev(dn, bus, devfn);
	if (!dev)
		return NULL;

	pr_debug("  dev header type: %x\n", dev->hdr_type);
	return dev;
}