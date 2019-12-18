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
typedef  int uint16_t ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_phy_lp {int /*<<< orphan*/  plp_txpctlmode; } ;
struct TYPE_2__ {struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {struct bwn_softc* mac_sc; TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHYLP_TXPCTL_OFF ; 
 int /*<<< orphan*/  BWN_PHYLP_TXPCTL_ON_HW ; 
 int /*<<< orphan*/  BWN_PHYLP_TXPCTL_ON_SW ; 
 int /*<<< orphan*/  BWN_PHYLP_TXPCTL_UNKNOWN ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_TX_PWR_CTL_CMD ; 
 int BWN_PHY_TX_PWR_CTL_CMD_MODE ; 
#define  BWN_PHY_TX_PWR_CTL_CMD_MODE_HW 130 
#define  BWN_PHY_TX_PWR_CTL_CMD_MODE_OFF 129 
#define  BWN_PHY_TX_PWR_CTL_CMD_MODE_SW 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bwn_phy_lp_get_txpctlmode(struct bwn_mac *mac)
{
	struct bwn_phy_lp *plp = &mac->mac_phy.phy_lp;
	struct bwn_softc *sc = mac->mac_sc;
	uint16_t ctl;

	ctl = BWN_PHY_READ(mac, BWN_PHY_TX_PWR_CTL_CMD);
	switch (ctl & BWN_PHY_TX_PWR_CTL_CMD_MODE) {
	case BWN_PHY_TX_PWR_CTL_CMD_MODE_OFF:
		plp->plp_txpctlmode = BWN_PHYLP_TXPCTL_OFF;
		break;
	case BWN_PHY_TX_PWR_CTL_CMD_MODE_SW:
		plp->plp_txpctlmode = BWN_PHYLP_TXPCTL_ON_SW;
		break;
	case BWN_PHY_TX_PWR_CTL_CMD_MODE_HW:
		plp->plp_txpctlmode = BWN_PHYLP_TXPCTL_ON_HW;
		break;
	default:
		plp->plp_txpctlmode = BWN_PHYLP_TXPCTL_UNKNOWN;
		device_printf(sc->sc_dev, "unknown command mode\n");
		break;
	}
}