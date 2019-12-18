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
struct mthca_uar {int index; int pfn; } ;
struct TYPE_2__ {int /*<<< orphan*/  alloc; } ;
struct mthca_dev {int /*<<< orphan*/  pdev; TYPE_1__ uar_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int mthca_alloc (int /*<<< orphan*/ *) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int) ; 

int mthca_uar_alloc(struct mthca_dev *dev, struct mthca_uar *uar)
{
	uar->index = mthca_alloc(&dev->uar_table.alloc);
	if (uar->index == -1)
		return -ENOMEM;

	uar->pfn = (pci_resource_start(dev->pdev, 2) >> PAGE_SHIFT) + uar->index;

	return 0;
}