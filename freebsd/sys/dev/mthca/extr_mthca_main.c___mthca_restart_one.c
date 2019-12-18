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
struct pci_dev {int dummy; } ;
struct mthca_dev {int hca_type; } ;

/* Variables and functions */
 int ENODEV ; 
 int __mthca_init_one (struct pci_dev*,int) ; 
 int /*<<< orphan*/  __mthca_remove_one (struct pci_dev*) ; 
 struct mthca_dev* pci_get_drvdata (struct pci_dev*) ; 

int __mthca_restart_one(struct pci_dev *pdev)
{
	struct mthca_dev *mdev;
	int hca_type;

	mdev = pci_get_drvdata(pdev);
	if (!mdev)
		return -ENODEV;
	hca_type = mdev->hca_type;
	__mthca_remove_one(pdev);
	return __mthca_init_one(pdev, hca_type);
}