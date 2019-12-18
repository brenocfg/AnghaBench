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
typedef  int /*<<< orphan*/  uintmax_t ;
struct resource_list_entry {scalar_t__ start; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  bsddev; } ;
struct pci_dev {TYPE_1__ dev; int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
typedef  unsigned long rman_res_t ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {int /*<<< orphan*/  number; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 scalar_t__ BUS_TRANSLATE_RESOURCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,unsigned long*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct resource_list_entry* linux_pci_get_bar (struct pci_dev*,int) ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned long
pci_resource_start(struct pci_dev *pdev, int bar)
{
	struct resource_list_entry *rle;
	rman_res_t newstart;
	device_t dev;

	if ((rle = linux_pci_get_bar(pdev, bar)) == NULL)
		return (0);
	dev = pci_find_dbsf(pdev->bus->domain, pdev->bus->number,
	    PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));
	MPASS(dev != NULL);
	if (BUS_TRANSLATE_RESOURCE(dev, rle->type, rle->start, &newstart)) {
		device_printf(pdev->dev.bsddev, "translate of %#jx failed\n",
		    (uintmax_t)rle->start);
		return (0);
	}
	return (newstart);
}