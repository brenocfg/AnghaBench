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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int NETIOR_XGMAC_RX_PFC_EN_POS ; 
 int NETIOR_XGMAC_STATS_EN_POS ; 
 int NETIOR_XGMAC_TX_PAUSE_POS ; 
 int NETIOR_XGMAC_TX_PFC_EN_POS ; 
 int NETIOR_XGMAC_VLAN_DC_POS ; 
 int /*<<< orphan*/  XAUI_CONFIG0 (int) ; 
 int /*<<< orphan*/  XAUI_CONFIG1 (int) ; 
 int XAUI_CONFIG_GENFCS ; 
 int XAUI_CONFIG_LENCHK ; 
 int XAUI_CONFIG_PAD_64 ; 
 int /*<<< orphan*/  XAUI_NETIOR_XGMAC_CTRL1 (int) ; 
 int /*<<< orphan*/  XAUI_NETIOR_XGMAC_CTRL2 (int) ; 
 int /*<<< orphan*/  XAUI_NETIOR_XGMAC_CTRL3 (int) ; 
 int /*<<< orphan*/  nlm_config_xaui_mtu (int /*<<< orphan*/ ,int,int,int) ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_config_xaui(uint64_t nae_base, int nblock,
    int max_tx_frame_sz, int max_rx_frame_sz, int vlan_pri_en)
{
	uint32_t val;

	val = nlm_read_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL1(nblock));
	val &= ~(0x1 << 11);	/* clear soft reset */
	nlm_write_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL1(nblock), val);

	val = nlm_read_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL1(nblock));
	val &= ~(0x3 << 11);	/* clear soft reset and hard reset */
	nlm_write_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL1(nblock), val);
	nlm_write_nae_reg(nae_base, XAUI_CONFIG0(nblock), 0xffffffff);
	nlm_write_nae_reg(nae_base, XAUI_CONFIG0(nblock), 0);

	/* Enable tx/rx frame */
	val = 0x000010A8;
	val |= XAUI_CONFIG_LENCHK;
	val |= XAUI_CONFIG_GENFCS;
	val |= XAUI_CONFIG_PAD_64;
	nlm_write_nae_reg(nae_base, XAUI_CONFIG1(nblock), val);

	/* write max frame length */
	nlm_config_xaui_mtu(nae_base, nblock, max_tx_frame_sz,
	    max_rx_frame_sz);

	/* set stats counter */
	val = nlm_read_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL1(nblock));
	val |= (0x1 << NETIOR_XGMAC_VLAN_DC_POS);
	val |= (0x1 << NETIOR_XGMAC_STATS_EN_POS);
	if (vlan_pri_en) {
		val |= (0x1 << NETIOR_XGMAC_TX_PFC_EN_POS);
		val |= (0x1 << NETIOR_XGMAC_RX_PFC_EN_POS);
		val |= (0x1 << NETIOR_XGMAC_TX_PAUSE_POS);
	} else {
		val &= ~(0x1 << NETIOR_XGMAC_TX_PFC_EN_POS);
		val |= (0x1 << NETIOR_XGMAC_TX_PAUSE_POS);
	}
	nlm_write_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL1(nblock), val);
	/* configure on / off timer */
	if (vlan_pri_en)
		val = 0xF1230000; /* PFC mode, offtimer = 0xf123, ontimer = 0 */
	else
		val = 0x0000F123; /* link level FC mode, offtimer = 0xf123 */
	nlm_write_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL2(nblock), val);

	/* set xaui tx threshold */
	val = nlm_read_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL3(nblock));
	val &= ~(0x1f << 10);
	val |= ~(15 << 10);
	nlm_write_nae_reg(nae_base, XAUI_NETIOR_XGMAC_CTRL3(nblock), val);
}