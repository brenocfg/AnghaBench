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
struct TYPE_2__ {int /*<<< orphan*/  pci_win_rd_data; int /*<<< orphan*/  pci_win_wr_data; int /*<<< orphan*/  pci_win_wr_data_lo; int /*<<< orphan*/  pci_win_wr_data_hi; void* pci_win_rd_addr; void* pci_win_rd_addr_lo; int /*<<< orphan*/  pci_win_rd_addr_hi; int /*<<< orphan*/  pci_win_wr_addr; } ;
struct octeon_device {int /*<<< orphan*/  pf_num; int /*<<< orphan*/  pcie_port; int /*<<< orphan*/  msix_on; TYPE_1__ reg_list; scalar_t__ chip; } ;
struct lio_cn23xx_pf {int /*<<< orphan*/  intr_enb_reg64; int /*<<< orphan*/  intr_sum_reg64; int /*<<< orphan*/  intr_mask64; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CN23XX_INTR_MASK ; 
 int /*<<< orphan*/  LIO_CN23XX_INTR_PKT_TIME ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_MAC_PF_INT_ENB64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_MAC_PF_INT_SUM64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* LIO_CN23XX_SLI_WIN_RD_ADDR64 ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_WIN_RD_ADDR_HI ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_WIN_RD_DATA64 ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_WIN_WR_ADDR64 ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_WIN_WR_DATA64 ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_WIN_WR_DATA_HI ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_WIN_WR_DATA_LO ; 
 int /*<<< orphan*/  lio_cn23xx_pf_get_pcie_qlmport (struct octeon_device*) ; 

__attribute__((used)) static void
lio_cn23xx_pf_setup_reg_address(struct octeon_device *oct)
{
	struct lio_cn23xx_pf	*cn23xx = (struct lio_cn23xx_pf *)oct->chip;

	oct->reg_list.pci_win_wr_addr = LIO_CN23XX_SLI_WIN_WR_ADDR64;

	oct->reg_list.pci_win_rd_addr_hi = LIO_CN23XX_SLI_WIN_RD_ADDR_HI;
	oct->reg_list.pci_win_rd_addr_lo = LIO_CN23XX_SLI_WIN_RD_ADDR64;
	oct->reg_list.pci_win_rd_addr = LIO_CN23XX_SLI_WIN_RD_ADDR64;

	oct->reg_list.pci_win_wr_data_hi = LIO_CN23XX_SLI_WIN_WR_DATA_HI;
	oct->reg_list.pci_win_wr_data_lo = LIO_CN23XX_SLI_WIN_WR_DATA_LO;
	oct->reg_list.pci_win_wr_data = LIO_CN23XX_SLI_WIN_WR_DATA64;

	oct->reg_list.pci_win_rd_data = LIO_CN23XX_SLI_WIN_RD_DATA64;

	lio_cn23xx_pf_get_pcie_qlmport(oct);

	cn23xx->intr_mask64 = LIO_CN23XX_INTR_MASK;
	if (!oct->msix_on)
		cn23xx->intr_mask64 |= LIO_CN23XX_INTR_PKT_TIME;

	cn23xx->intr_sum_reg64 =
	    LIO_CN23XX_SLI_MAC_PF_INT_SUM64(oct->pcie_port, oct->pf_num);
	cn23xx->intr_enb_reg64 =
	    LIO_CN23XX_SLI_MAC_PF_INT_ENB64(oct->pcie_port, oct->pf_num);
}