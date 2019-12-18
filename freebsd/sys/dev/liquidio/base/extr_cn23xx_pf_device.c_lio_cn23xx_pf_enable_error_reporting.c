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
typedef  int uint32_t ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CN23XX_CFG_PCIE_CORRECT_ERR_STATUS ; 
 int /*<<< orphan*/  LIO_CN23XX_CFG_PCIE_DEVCTL ; 
 int LIO_CN23XX_CFG_PCIE_DEVCTL_MASK ; 
 int /*<<< orphan*/  LIO_CN23XX_CFG_PCIE_UNCORRECT_ERR_MASK ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,int,int,int) ; 
 int lio_read_pci_cfg (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_pci_cfg (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lio_cn23xx_pf_enable_error_reporting(struct octeon_device *oct)
{
	uint32_t	corrtable_err_status, uncorrectable_err_mask, regval;

	regval = lio_read_pci_cfg(oct, LIO_CN23XX_CFG_PCIE_DEVCTL);
	if (regval & LIO_CN23XX_CFG_PCIE_DEVCTL_MASK) {
		uncorrectable_err_mask = 0;
		corrtable_err_status = 0;
		uncorrectable_err_mask =
		    lio_read_pci_cfg(oct,
				     LIO_CN23XX_CFG_PCIE_UNCORRECT_ERR_MASK);
		corrtable_err_status =
		    lio_read_pci_cfg(oct,
				     LIO_CN23XX_CFG_PCIE_CORRECT_ERR_STATUS);
		lio_dev_err(oct, "PCI-E Fatal error detected;\n"
			    "\tdev_ctl_status_reg = 0x%08x\n"
			    "\tuncorrectable_error_mask_reg = 0x%08x\n"
			    "\tcorrectable_error_status_reg = 0x%08x\n",
			    regval, uncorrectable_err_mask,
			    corrtable_err_status);
	}

	regval |= 0xf;	/* Enable Link error reporting */

	lio_dev_dbg(oct, "Enabling PCI-E error reporting..\n");
	lio_write_pci_cfg(oct, LIO_CN23XX_CFG_PCIE_DEVCTL, regval);
}