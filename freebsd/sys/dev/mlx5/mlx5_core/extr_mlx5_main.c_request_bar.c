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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_bar(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev = pci_get_drvdata(pdev);
	int err = 0;

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
		mlx5_core_err(dev, "Missing registers BAR, aborting\n");
		return -ENODEV;
	}

	err = pci_request_regions(pdev, DRIVER_NAME);
	if (err)
		mlx5_core_err(dev, "Couldn't get PCI resources, aborting\n");

	return err;
}