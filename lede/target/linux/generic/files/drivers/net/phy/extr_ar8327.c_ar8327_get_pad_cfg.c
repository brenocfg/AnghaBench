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
typedef  int u32 ;
struct ar8327_pad_cfg {int mode; int txclk_delay_sel; int rxclk_delay_sel; int /*<<< orphan*/  txclk_delay_en; int /*<<< orphan*/  rxclk_delay_en; int /*<<< orphan*/  txclk_sel; int /*<<< orphan*/  rxclk_sel; int /*<<< orphan*/  pipe_rxclk_sel; int /*<<< orphan*/  sgmii_delay_en; } ;

/* Variables and functions */
#define  AR8327_PAD_MAC2MAC_GMII 137 
#define  AR8327_PAD_MAC2MAC_MII 136 
#define  AR8327_PAD_MAC2PHY_GMII 135 
#define  AR8327_PAD_MAC2PHY_MII 134 
 int AR8327_PAD_MAC_GMII_EN ; 
 int AR8327_PAD_MAC_GMII_RXCLK_SEL ; 
 int AR8327_PAD_MAC_GMII_TXCLK_SEL ; 
 int AR8327_PAD_MAC_MII_EN ; 
 int AR8327_PAD_MAC_MII_RXCLK_SEL ; 
 int AR8327_PAD_MAC_MII_TXCLK_SEL ; 
#define  AR8327_PAD_MAC_RGMII 133 
#define  AR8327_PAD_MAC_SGMII 132 
#define  AR8327_PAD_NC 131 
 int AR8327_PAD_PHYX_GMII_EN ; 
 int AR8327_PAD_PHYX_MII_EN ; 
 int AR8327_PAD_PHYX_RGMII_EN ; 
#define  AR8327_PAD_PHY_GMII 130 
 int AR8327_PAD_PHY_GMII_EN ; 
 int AR8327_PAD_PHY_GMII_PIPE_RXCLK_SEL ; 
 int AR8327_PAD_PHY_GMII_RXCLK_SEL ; 
 int AR8327_PAD_PHY_GMII_TXCLK_SEL ; 
#define  AR8327_PAD_PHY_MII 129 
 int AR8327_PAD_PHY_MII_EN ; 
 int AR8327_PAD_PHY_MII_RXCLK_SEL ; 
 int AR8327_PAD_PHY_MII_TXCLK_SEL ; 
#define  AR8327_PAD_PHY_RGMII 128 
 int AR8327_PAD_RGMII_EN ; 
 int AR8327_PAD_RGMII_RXCLK_DELAY_EN ; 
 int AR8327_PAD_RGMII_RXCLK_DELAY_SEL_S ; 
 int AR8327_PAD_RGMII_TXCLK_DELAY_EN ; 
 int AR8327_PAD_RGMII_TXCLK_DELAY_SEL_S ; 
 int AR8327_PAD_SGMII_DELAY_EN ; 
 int AR8327_PAD_SGMII_EN ; 

__attribute__((used)) static u32
ar8327_get_pad_cfg(struct ar8327_pad_cfg *cfg)
{
	u32 t;

	if (!cfg)
		return 0;

	t = 0;
	switch (cfg->mode) {
	case AR8327_PAD_NC:
		break;

	case AR8327_PAD_MAC2MAC_MII:
		t = AR8327_PAD_MAC_MII_EN;
		if (cfg->rxclk_sel)
			t |= AR8327_PAD_MAC_MII_RXCLK_SEL;
		if (cfg->txclk_sel)
			t |= AR8327_PAD_MAC_MII_TXCLK_SEL;
		break;

	case AR8327_PAD_MAC2MAC_GMII:
		t = AR8327_PAD_MAC_GMII_EN;
		if (cfg->rxclk_sel)
			t |= AR8327_PAD_MAC_GMII_RXCLK_SEL;
		if (cfg->txclk_sel)
			t |= AR8327_PAD_MAC_GMII_TXCLK_SEL;
		break;

	case AR8327_PAD_MAC_SGMII:
		t = AR8327_PAD_SGMII_EN;

		/*
		 * WAR for the QUalcomm Atheros AP136 board.
		 * It seems that RGMII TX/RX delay settings needs to be
		 * applied for SGMII mode as well, The ethernet is not
		 * reliable without this.
		 */
		t |= cfg->txclk_delay_sel << AR8327_PAD_RGMII_TXCLK_DELAY_SEL_S;
		t |= cfg->rxclk_delay_sel << AR8327_PAD_RGMII_RXCLK_DELAY_SEL_S;
		if (cfg->rxclk_delay_en)
			t |= AR8327_PAD_RGMII_RXCLK_DELAY_EN;
		if (cfg->txclk_delay_en)
			t |= AR8327_PAD_RGMII_TXCLK_DELAY_EN;

		if (cfg->sgmii_delay_en)
			t |= AR8327_PAD_SGMII_DELAY_EN;

		break;

	case AR8327_PAD_MAC2PHY_MII:
		t = AR8327_PAD_PHY_MII_EN;
		if (cfg->rxclk_sel)
			t |= AR8327_PAD_PHY_MII_RXCLK_SEL;
		if (cfg->txclk_sel)
			t |= AR8327_PAD_PHY_MII_TXCLK_SEL;
		break;

	case AR8327_PAD_MAC2PHY_GMII:
		t = AR8327_PAD_PHY_GMII_EN;
		if (cfg->pipe_rxclk_sel)
			t |= AR8327_PAD_PHY_GMII_PIPE_RXCLK_SEL;
		if (cfg->rxclk_sel)
			t |= AR8327_PAD_PHY_GMII_RXCLK_SEL;
		if (cfg->txclk_sel)
			t |= AR8327_PAD_PHY_GMII_TXCLK_SEL;
		break;

	case AR8327_PAD_MAC_RGMII:
		t = AR8327_PAD_RGMII_EN;
		t |= cfg->txclk_delay_sel << AR8327_PAD_RGMII_TXCLK_DELAY_SEL_S;
		t |= cfg->rxclk_delay_sel << AR8327_PAD_RGMII_RXCLK_DELAY_SEL_S;
		if (cfg->rxclk_delay_en)
			t |= AR8327_PAD_RGMII_RXCLK_DELAY_EN;
		if (cfg->txclk_delay_en)
			t |= AR8327_PAD_RGMII_TXCLK_DELAY_EN;
		break;

	case AR8327_PAD_PHY_GMII:
		t = AR8327_PAD_PHYX_GMII_EN;
		break;

	case AR8327_PAD_PHY_RGMII:
		t = AR8327_PAD_PHYX_RGMII_EN;
		break;

	case AR8327_PAD_PHY_MII:
		t = AR8327_PAD_PHYX_MII_EN;
		break;
	}

	return t;
}