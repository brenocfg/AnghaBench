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
struct mlx4_dev_persistent {struct mlx4_dev* dev; } ;
struct mlx4_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int mlx4_pci_enable_device (struct mlx4_dev*) ; 
 struct mlx4_dev_persistent* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t mlx4_pci_slot_reset(struct pci_dev *pdev)
{
	struct mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	struct mlx4_dev	 *dev  = persist->dev;
	int err;

	mlx4_err(dev, "mlx4_pci_slot_reset was called\n");
	err = mlx4_pci_enable_device(dev);
	if (err) {
		mlx4_err(dev, "Can not re-enable device, err=%d\n", err);
		return PCI_ERS_RESULT_DISCONNECT;
	}

	pci_set_master(pdev);
	return PCI_ERS_RESULT_RECOVERED;
}