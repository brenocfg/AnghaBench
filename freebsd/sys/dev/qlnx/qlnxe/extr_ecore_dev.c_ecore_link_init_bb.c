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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_FPGA (int /*<<< orphan*/ ) ; 
 scalar_t__ MISC_REG_RESET_PL_PDA_VAUX ; 
 int MISC_REG_RESET_REG_2_XMAC_BIT ; 
 int MISC_REG_RESET_REG_2_XMAC_SOFT_BIT ; 
 scalar_t__ MISC_REG_XMAC_CORE_PORT_MODE_BB ; 
 scalar_t__ MISC_REG_XMAC_PHY_PORT_MODE_BB ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int) ; 
 scalar_t__ XMAC_REG_CTRL_BB ; 
 int XMAC_REG_CTRL_RX_EN_BB ; 
 int XMAC_REG_CTRL_TX_EN_BB ; 
 scalar_t__ XMAC_REG_MODE_BB ; 
 scalar_t__ XMAC_REG_RX_CTRL_BB ; 
 int XMAC_REG_RX_CTRL_PROCESS_VARIABLE_PREAMBLE_BB ; 
 scalar_t__ XMAC_REG_RX_MAX_SIZE_BB ; 
 scalar_t__ XMAC_REG_TX_CTRL_LO_BB ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int) ; 

__attribute__((used)) static void ecore_link_init_bb(struct ecore_hwfn *p_hwfn,
			       struct ecore_ptt *p_ptt,  u8 port)
{
	int port_offset = port ? 0x800 : 0;
	u32 xmac_rxctrl	= 0;

	/* Reset of XMAC */
	/* FIXME: move to common start */
	ecore_wr(p_hwfn, p_ptt, MISC_REG_RESET_PL_PDA_VAUX + 2*sizeof(u32),
		 MISC_REG_RESET_REG_2_XMAC_BIT); /* Clear */
	OSAL_MSLEEP(1);
	ecore_wr(p_hwfn, p_ptt, MISC_REG_RESET_PL_PDA_VAUX + sizeof(u32),
		 MISC_REG_RESET_REG_2_XMAC_BIT); /* Set */

	ecore_wr(p_hwfn, p_ptt, MISC_REG_XMAC_CORE_PORT_MODE_BB, 1);

	/* Set the number of ports on the Warp Core to 10G */
	ecore_wr(p_hwfn, p_ptt, MISC_REG_XMAC_PHY_PORT_MODE_BB, 3);

	/* Soft reset of XMAC */
	ecore_wr(p_hwfn, p_ptt, MISC_REG_RESET_PL_PDA_VAUX + 2 * sizeof(u32),
		 MISC_REG_RESET_REG_2_XMAC_SOFT_BIT);
	OSAL_MSLEEP(1);
	ecore_wr(p_hwfn, p_ptt, MISC_REG_RESET_PL_PDA_VAUX + sizeof(u32),
		 MISC_REG_RESET_REG_2_XMAC_SOFT_BIT);

	/* FIXME: move to common end */
	if (CHIP_REV_IS_FPGA(p_hwfn->p_dev))
		ecore_wr(p_hwfn, p_ptt, XMAC_REG_MODE_BB + port_offset, 0x20);

	/* Set Max packet size: initialize XMAC block register for port 0 */
	ecore_wr(p_hwfn, p_ptt, XMAC_REG_RX_MAX_SIZE_BB + port_offset, 0x2710);

	/* CRC append for Tx packets: init XMAC block register for port 1 */
	ecore_wr(p_hwfn, p_ptt, XMAC_REG_TX_CTRL_LO_BB + port_offset, 0xC800);

	/* Enable TX and RX: initialize XMAC block register for port 1 */
	ecore_wr(p_hwfn, p_ptt, XMAC_REG_CTRL_BB + port_offset,
		 XMAC_REG_CTRL_TX_EN_BB | XMAC_REG_CTRL_RX_EN_BB);
	xmac_rxctrl = ecore_rd(p_hwfn, p_ptt,
			       XMAC_REG_RX_CTRL_BB + port_offset);
	xmac_rxctrl |= XMAC_REG_RX_CTRL_PROCESS_VARIABLE_PREAMBLE_BB;
	ecore_wr(p_hwfn, p_ptt, XMAC_REG_RX_CTRL_BB + port_offset, xmac_rxctrl);
}