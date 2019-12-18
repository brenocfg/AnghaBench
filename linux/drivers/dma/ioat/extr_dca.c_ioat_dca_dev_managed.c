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
struct pci_dev {int dummy; } ;
struct ioat_dca_priv {int max_requesters; TYPE_1__* req_slots; } ;
struct device {int dummy; } ;
struct dca_provider {int dummy; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 struct ioat_dca_priv* dca_priv (struct dca_provider*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int ioat_dca_dev_managed(struct dca_provider *dca,
				struct device *dev)
{
	struct ioat_dca_priv *ioatdca = dca_priv(dca);
	struct pci_dev *pdev;
	int i;

	pdev = to_pci_dev(dev);
	for (i = 0; i < ioatdca->max_requesters; i++) {
		if (ioatdca->req_slots[i].pdev == pdev)
			return 1;
	}
	return 0;
}