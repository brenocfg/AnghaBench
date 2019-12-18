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
struct dfl_fpga_cdev {int dummy; } ;
struct cci_drvdata {struct dfl_fpga_cdev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dfl_fpga_cdev_config_ports_pf (struct dfl_fpga_cdev*) ; 
 int dfl_fpga_cdev_config_ports_vf (struct dfl_fpga_cdev*,int) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 struct cci_drvdata* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static int cci_pci_sriov_configure(struct pci_dev *pcidev, int num_vfs)
{
	struct cci_drvdata *drvdata = pci_get_drvdata(pcidev);
	struct dfl_fpga_cdev *cdev = drvdata->cdev;
	int ret = 0;

	if (!num_vfs) {
		/*
		 * disable SRIOV and then put released ports back to default
		 * PF access mode.
		 */
		pci_disable_sriov(pcidev);

		dfl_fpga_cdev_config_ports_pf(cdev);

	} else {
		/*
		 * before enable SRIOV, put released ports into VF access mode
		 * first of all.
		 */
		ret = dfl_fpga_cdev_config_ports_vf(cdev, num_vfs);
		if (ret)
			return ret;

		ret = pci_enable_sriov(pcidev, num_vfs);
		if (ret)
			dfl_fpga_cdev_config_ports_pf(cdev);
	}

	return ret;
}