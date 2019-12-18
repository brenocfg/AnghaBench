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
struct octeon_device {int pf_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CN23XX_PCIE_SRIOV_FDL ; 
 int LIO_CN23XX_PCIE_SRIOV_FDL_BIT_POS ; 
 int LIO_CN23XX_PCIE_SRIOV_FDL_MASK ; 
 int lio_read_pci_cfg (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_cn23xx_pf_get_pf_num(struct octeon_device *oct)
{
	uint32_t	fdl_bit;

	/* Read Function Dependency Link reg to get the function number */
	fdl_bit = lio_read_pci_cfg(oct, LIO_CN23XX_PCIE_SRIOV_FDL);
	oct->pf_num = ((fdl_bit >> LIO_CN23XX_PCIE_SRIOV_FDL_BIT_POS) &
		       LIO_CN23XX_PCIE_SRIOV_FDL_MASK);
}