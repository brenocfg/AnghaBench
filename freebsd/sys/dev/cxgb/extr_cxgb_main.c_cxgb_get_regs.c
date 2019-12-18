#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ch_ifconf_regs {int version; } ;
struct TYPE_6__ {int rev; } ;
struct TYPE_7__ {TYPE_1__ params; } ;
typedef  TYPE_2__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_CPL_MAP_TBL_DATA ; 
 int /*<<< orphan*/  A_CPL_SWITCH_CNTRL ; 
 int /*<<< orphan*/  A_MPS_INT_CAUSE ; 
 int /*<<< orphan*/  A_SG_HI_DRB_HI_THRSH ; 
 int /*<<< orphan*/  A_SG_RSPQ_CREDIT_RETURN ; 
 int /*<<< orphan*/  A_SMB_GLOBAL_TIME_CFG ; 
 int /*<<< orphan*/  A_ULPRX_PBL_ULIMIT ; 
 int /*<<< orphan*/  A_ULPTX_CONFIG ; 
 int /*<<< orphan*/  A_XGM_RX_SPI4_SOP_EOP_CNT ; 
 int /*<<< orphan*/  A_XGM_SERDES_STAT3 ; 
 int /*<<< orphan*/  A_XGM_SERDES_STATUS0 ; 
 int /*<<< orphan*/  XGM_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxgb_get_regs_len () ; 
 int is_pcie (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_block_dump (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cxgb_get_regs(adapter_t *sc, struct ch_ifconf_regs *regs, uint8_t *buf)
{	    
	
	/*
	 * Version scheme:
	 * bits 0..9: chip version
	 * bits 10..15: chip revision
	 * bit 31: set for PCIe cards
	 */
	regs->version = 3 | (sc->params.rev << 10) | (is_pcie(sc) << 31);

	/*
	 * We skip the MAC statistics registers because they are clear-on-read.
	 * Also reading multi-register stats would need to synchronize with the
	 * periodic mac stats accumulation.  Hard to justify the complexity.
	 */
	memset(buf, 0, cxgb_get_regs_len());
	reg_block_dump(sc, buf, 0, A_SG_RSPQ_CREDIT_RETURN);
	reg_block_dump(sc, buf, A_SG_HI_DRB_HI_THRSH, A_ULPRX_PBL_ULIMIT);
	reg_block_dump(sc, buf, A_ULPTX_CONFIG, A_MPS_INT_CAUSE);
	reg_block_dump(sc, buf, A_CPL_SWITCH_CNTRL, A_CPL_MAP_TBL_DATA);
	reg_block_dump(sc, buf, A_SMB_GLOBAL_TIME_CFG, A_XGM_SERDES_STAT3);
	reg_block_dump(sc, buf, A_XGM_SERDES_STATUS0,
		       XGM_REG(A_XGM_SERDES_STAT3, 1));
	reg_block_dump(sc, buf, XGM_REG(A_XGM_SERDES_STATUS0, 1),
		       XGM_REG(A_XGM_RX_SPI4_SOP_EOP_CNT, 1));
}