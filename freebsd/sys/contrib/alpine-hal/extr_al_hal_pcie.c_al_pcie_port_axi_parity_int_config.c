#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/ * global; } ;
struct TYPE_5__ {int /*<<< orphan*/  en_axi; } ;
struct TYPE_8__ {TYPE_3__* int_grp_a; TYPE_2__ ctrl; TYPE_1__ parity; } ;
struct al_pcie_regs {TYPE_4__ axi; } ;
struct al_pcie_port {scalar_t__ rev_id; struct al_pcie_regs* regs; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_7__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 scalar_t__ AL_PCIE_REV_ID_3 ; 
 scalar_t__ AL_TRUE ; 
 int PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERROR_AXI ; 
 int PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_DATA_PATH_RD ; 
 int PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_ADDR_RD ; 
 int PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_ADDR_WR ; 
 int PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_DATA_WR ; 
 int PCIE_AXI_PARITY_EN_AXI_U4_RAM2P ; 
 int PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_CALC_EN_MSTR ; 
 int PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_CALC_EN_SLV ; 
 int PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_ERR_EN_RD ; 
 int PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_ERR_EN_WR ; 
 int PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_CALC_EN_MSTR ; 
 int PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_CALC_EN_SLV ; 
 int PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_ERR_EN_RD ; 
 int PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_ERR_EN_WR ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
al_pcie_port_axi_parity_int_config(
	struct al_pcie_port *pcie_port,
	al_bool enable)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	uint32_t parity_enable_mask = 0xffffffff;

	/**
	 * Addressing RMN: 5603
	 *
	 * RMN description:
	 * u4_ram2p signal false parity error
	 *
	 * Software flow:
	 * Disable parity check for this memory
	 */
	if (pcie_port->rev_id >= AL_PCIE_REV_ID_3)
		parity_enable_mask &= ~PCIE_AXI_PARITY_EN_AXI_U4_RAM2P;

	al_reg_write32(regs->axi.parity.en_axi,
		       (enable == AL_TRUE) ? parity_enable_mask : 0x0);

	if (pcie_port->rev_id == AL_PCIE_REV_ID_3) {
		al_reg_write32_masked(regs->axi.ctrl.global,
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_CALC_EN_MSTR |
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_ERR_EN_RD |
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_CALC_EN_SLV |
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_ERR_EN_WR,
			(enable == AL_TRUE) ?
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_CALC_EN_MSTR |
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_ERR_EN_RD |
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_CALC_EN_SLV |
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_ERR_EN_WR :
			PCIE_REV3_AXI_CTRL_GLOBAL_PARITY_CALC_EN_SLV);
	} else {
		al_reg_write32_masked(regs->axi.ctrl.global,
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_CALC_EN_MSTR |
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_ERR_EN_RD |
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_CALC_EN_SLV |
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_ERR_EN_WR,
			(enable == AL_TRUE) ?
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_CALC_EN_MSTR |
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_ERR_EN_RD |
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_CALC_EN_SLV |
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_ERR_EN_WR :
			PCIE_REV1_2_AXI_CTRL_GLOBAL_PARITY_CALC_EN_SLV);
	}

	al_reg_write32_masked(&regs->axi.int_grp_a->mask,
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_DATA_PATH_RD |
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_ADDR_RD |
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_ADDR_WR |
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_DATA_WR |
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERROR_AXI,
		(enable != AL_TRUE) ?
		(PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_DATA_PATH_RD |
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_ADDR_RD |
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_ADDR_WR |
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERR_OUT_DATA_WR |
		PCIE_AXI_INT_GRP_A_CAUSE_PARITY_ERROR_AXI) : 0);
}