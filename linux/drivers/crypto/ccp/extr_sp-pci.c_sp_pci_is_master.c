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
struct sp_device {struct device* dev; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;
struct TYPE_3__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 TYPE_2__* sp_dev_master ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static bool sp_pci_is_master(struct sp_device *sp)
{
	struct device *dev_cur, *dev_new;
	struct pci_dev *pdev_cur, *pdev_new;

	dev_new = sp->dev;
	dev_cur = sp_dev_master->dev;

	pdev_new = to_pci_dev(dev_new);
	pdev_cur = to_pci_dev(dev_cur);

	if (pdev_new->bus->number < pdev_cur->bus->number)
		return true;

	if (PCI_SLOT(pdev_new->devfn) < PCI_SLOT(pdev_cur->devfn))
		return true;

	if (PCI_FUNC(pdev_new->devfn) < PCI_FUNC(pdev_cur->devfn))
		return true;

	return false;
}