#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ board_vendor; scalar_t__ board_type; int board_rev; int board_flags2; } ;
struct bwn_softc {TYPE_2__ sc_board_info; int /*<<< orphan*/  sc_dev; } ;
struct bwn_phy_n {int /*<<< orphan*/  gain_boost; } ;
struct TYPE_3__ {struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_softc* mac_sc; TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2055_C1_LNA_GAINBST ; 
 int /*<<< orphan*/  B2055_C1_RX_BB_LPF ; 
 int /*<<< orphan*/  B2055_C1_RX_BB_MIDACHP ; 
 int /*<<< orphan*/  B2055_C1_RX_BB_REG ; 
 int /*<<< orphan*/  B2055_C1_RX_RFSPC1 ; 
 int /*<<< orphan*/  B2055_C2_LNA_GAINBST ; 
 int /*<<< orphan*/  B2055_C2_RX_BB_LPF ; 
 int /*<<< orphan*/  B2055_C2_RX_BB_MIDACHP ; 
 int /*<<< orphan*/  B2055_C2_RX_BB_REG ; 
 int /*<<< orphan*/  B2055_C2_RX_RFSPC1 ; 
 int /*<<< orphan*/  B2055_CAL_COUT2 ; 
 int /*<<< orphan*/  B2055_CAL_LPOCTL ; 
 int /*<<< orphan*/  B2055_CAL_MISC ; 
 int /*<<< orphan*/  B2055_MASTER1 ; 
 int /*<<< orphan*/  B2055_RRCCAL_NOPTSEL ; 
 int BHND_BFL2_RXBB_INT_REG_DIS ; 
 scalar_t__ BHND_BOARD_BCM4321CB2 ; 
 int /*<<< orphan*/  BWN_ERRPRINTF (struct bwn_softc*,char*) ; 
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ PCI_VENDOR_BROADCOM ; 
 int bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_get_chan (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_radio_wait_value (struct bwn_mac*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  bwn_switch_channel (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_radio_init2055_post(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	bool workaround = false;

	if (bhnd_get_hwrev(sc->sc_dev) < 4)
		workaround =
		    (sc->sc_board_info.board_vendor != PCI_VENDOR_BROADCOM)
		    && (sc->sc_board_info.board_type == BHND_BOARD_BCM4321CB2)
		      && (sc->sc_board_info.board_rev >= 0x41);
	else
		workaround =
			!(sc->sc_board_info.board_flags2 & BHND_BFL2_RXBB_INT_REG_DIS);

	BWN_RF_MASK(mac, B2055_MASTER1, 0xFFF3);
	if (workaround) {
		BWN_RF_MASK(mac, B2055_C1_RX_BB_REG, 0x7F);
		BWN_RF_MASK(mac, B2055_C2_RX_BB_REG, 0x7F);
	}
	BWN_RF_SETMASK(mac, B2055_RRCCAL_NOPTSEL, 0xFFC0, 0x2C);
	BWN_RF_WRITE(mac, B2055_CAL_MISC, 0x3C);
	BWN_RF_MASK(mac, B2055_CAL_MISC, 0xFFBE);
	BWN_RF_SET(mac, B2055_CAL_LPOCTL, 0x80);
	BWN_RF_SET(mac, B2055_CAL_MISC, 0x1);
	DELAY(1000);
	BWN_RF_SET(mac, B2055_CAL_MISC, 0x40);
	if (!bwn_radio_wait_value(mac, B2055_CAL_COUT2, 0x80, 0x80, 10, 2000))
		BWN_ERRPRINTF(mac->mac_sc, "radio post init timeout\n");
	BWN_RF_MASK(mac, B2055_CAL_LPOCTL, 0xFF7F);
	bwn_switch_channel(mac, bwn_get_chan(mac));
	BWN_RF_WRITE(mac, B2055_C1_RX_BB_LPF, 0x9);
	BWN_RF_WRITE(mac, B2055_C2_RX_BB_LPF, 0x9);
	BWN_RF_WRITE(mac, B2055_C1_RX_BB_MIDACHP, 0x83);
	BWN_RF_WRITE(mac, B2055_C2_RX_BB_MIDACHP, 0x83);
	BWN_RF_SETMASK(mac, B2055_C1_LNA_GAINBST, 0xFFF8, 0x6);
	BWN_RF_SETMASK(mac, B2055_C2_LNA_GAINBST, 0xFFF8, 0x6);
	if (!nphy->gain_boost) {
		BWN_RF_SET(mac, B2055_C1_RX_RFSPC1, 0x2);
		BWN_RF_SET(mac, B2055_C2_RX_RFSPC1, 0x2);
	} else {
		BWN_RF_MASK(mac, B2055_C1_RX_RFSPC1, 0xFFFD);
		BWN_RF_MASK(mac, B2055_C2_RX_RFSPC1, 0xFFFD);
	}
	DELAY(2);
}