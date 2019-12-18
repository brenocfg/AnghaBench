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
struct pci_dev {int dummy; } ;
struct eeh_dev {TYPE_1__* pe; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int EEH_PE_ISOLATED ; 
 size_t EIO ; 
 size_t ENODEV ; 
 int /*<<< orphan*/  eeh_pe_state_clear (TYPE_1__*,int,int) ; 
 scalar_t__ eeh_unfreeze_pe (TYPE_1__*) ; 
 struct eeh_dev* pci_dev_to_eeh_dev (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t eeh_pe_state_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);

	if (!edev || !edev->pe)
		return -ENODEV;

	/* Nothing to do if it's not frozen */
	if (!(edev->pe->state & EEH_PE_ISOLATED))
		return count;

	if (eeh_unfreeze_pe(edev->pe))
		return -EIO;
	eeh_pe_state_clear(edev->pe, EEH_PE_ISOLATED, true);

	return count;
}