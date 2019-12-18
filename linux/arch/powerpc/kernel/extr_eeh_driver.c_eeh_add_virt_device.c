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
struct pci_driver {scalar_t__ err_handler; } ;
struct pci_dev {int dummy; } ;
struct eeh_dev {int /*<<< orphan*/  physfn; } ;
struct TYPE_2__ {int /*<<< orphan*/  vf_index; } ;

/* Variables and functions */
 struct pci_dev* eeh_dev_to_pci_dev (struct eeh_dev*) ; 
 TYPE_1__* eeh_dev_to_pdn (struct eeh_dev*) ; 
 int /*<<< orphan*/  eeh_edev_warn (struct eeh_dev*,char*) ; 
 struct pci_driver* eeh_pcid_get (struct pci_dev*) ; 
 int /*<<< orphan*/  eeh_pcid_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iov_add_virtfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *eeh_add_virt_device(struct eeh_dev *edev)
{
	struct pci_driver *driver;
	struct pci_dev *dev = eeh_dev_to_pci_dev(edev);

	if (!(edev->physfn)) {
		eeh_edev_warn(edev, "Not for VF\n");
		return NULL;
	}

	driver = eeh_pcid_get(dev);
	if (driver) {
		if (driver->err_handler) {
			eeh_pcid_put(dev);
			return NULL;
		}
		eeh_pcid_put(dev);
	}

#ifdef CONFIG_PCI_IOV
	pci_iov_add_virtfn(edev->physfn, eeh_dev_to_pdn(edev)->vf_index);
#endif
	return NULL;
}