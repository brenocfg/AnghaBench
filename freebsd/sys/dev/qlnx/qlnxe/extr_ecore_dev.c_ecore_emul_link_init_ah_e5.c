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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int port_id; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 scalar_t__ CNIG_REG_NIG_PORT0_CONF_K2_E5 ; 
 int CNIG_REG_NIG_PORT0_CONF_NIG_PORT_ENABLE_0_K2_E5_SHIFT ; 
 int CNIG_REG_NIG_PORT0_CONF_NIG_PORT_NWM_PORT_MAP_0_K2_E5_SHIFT ; 
 int CNIG_REG_NIG_PORT0_CONF_NIG_PORT_RATE_0_K2_E5_SHIFT ; 
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ETH_MAC_REG_COMMAND_CONFIG_K2_E5 ; 
 int ETH_MAC_REG_FRM_LENGTH_FRM_LENGTH_K2_E5_SHIFT ; 
 scalar_t__ ETH_MAC_REG_FRM_LENGTH_K2_E5 ; 
 scalar_t__ ETH_MAC_REG_RX_FIFO_SECTIONS_K2_E5 ; 
 int ETH_MAC_REG_RX_FIFO_SECTIONS_RX_SECTION_FULL_K2_E5_SHIFT ; 
 scalar_t__ ETH_MAC_REG_TX_FIFO_SECTIONS_K2_E5 ; 
 int ETH_MAC_REG_TX_FIFO_SECTIONS_TX_SECTION_EMPTY_K2_E5_SHIFT ; 
 int ETH_MAC_REG_TX_FIFO_SECTIONS_TX_SECTION_FULL_K2_E5_SHIFT ; 
 scalar_t__ ETH_MAC_REG_TX_IPG_LENGTH_K2_E5 ; 
 int ETH_MAC_REG_TX_IPG_LENGTH_TXIPG_K2_E5_SHIFT ; 
 scalar_t__ ETH_MAC_REG_XIF_MODE_K2_E5 ; 
 int ETH_MAC_REG_XIF_MODE_XGMII_K2_E5_SHIFT ; 
 scalar_t__ NWM_REG_MAC0_K2_E5 ; 
 int NWM_REG_MAC0_SIZE ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int) ; 

__attribute__((used)) static void ecore_emul_link_init_ah_e5(struct ecore_hwfn *p_hwfn,
				       struct ecore_ptt *p_ptt)
{
	u8 port = p_hwfn->port_id;
	u32 mac_base = NWM_REG_MAC0_K2_E5 + (port << 2) * NWM_REG_MAC0_SIZE;

	DP_INFO(p_hwfn->p_dev, "Configurating Emulation Link %02x\n", port);

	ecore_wr(p_hwfn, p_ptt, CNIG_REG_NIG_PORT0_CONF_K2_E5 + (port << 2),
		 (1 << CNIG_REG_NIG_PORT0_CONF_NIG_PORT_ENABLE_0_K2_E5_SHIFT) |
		 (port <<
		  CNIG_REG_NIG_PORT0_CONF_NIG_PORT_NWM_PORT_MAP_0_K2_E5_SHIFT) |
		 (0 << CNIG_REG_NIG_PORT0_CONF_NIG_PORT_RATE_0_K2_E5_SHIFT));

	ecore_wr(p_hwfn, p_ptt, mac_base + ETH_MAC_REG_XIF_MODE_K2_E5,
		 1 << ETH_MAC_REG_XIF_MODE_XGMII_K2_E5_SHIFT);

	ecore_wr(p_hwfn, p_ptt, mac_base + ETH_MAC_REG_FRM_LENGTH_K2_E5,
		 9018 << ETH_MAC_REG_FRM_LENGTH_FRM_LENGTH_K2_E5_SHIFT);

	ecore_wr(p_hwfn, p_ptt, mac_base + ETH_MAC_REG_TX_IPG_LENGTH_K2_E5,
		 0xc << ETH_MAC_REG_TX_IPG_LENGTH_TXIPG_K2_E5_SHIFT);

	ecore_wr(p_hwfn, p_ptt, mac_base + ETH_MAC_REG_RX_FIFO_SECTIONS_K2_E5,
		 8 << ETH_MAC_REG_RX_FIFO_SECTIONS_RX_SECTION_FULL_K2_E5_SHIFT);

	ecore_wr(p_hwfn, p_ptt, mac_base + ETH_MAC_REG_TX_FIFO_SECTIONS_K2_E5,
		 (0xA <<
		  ETH_MAC_REG_TX_FIFO_SECTIONS_TX_SECTION_EMPTY_K2_E5_SHIFT) |
		 (8 <<
		  ETH_MAC_REG_TX_FIFO_SECTIONS_TX_SECTION_FULL_K2_E5_SHIFT));

	ecore_wr(p_hwfn, p_ptt, mac_base + ETH_MAC_REG_COMMAND_CONFIG_K2_E5,
		 0xa853);
}