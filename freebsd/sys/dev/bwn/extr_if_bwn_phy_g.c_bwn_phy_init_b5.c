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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {scalar_t__ board_vendor; scalar_t__ board_type; } ;
struct bwn_softc {TYPE_1__ sc_board_info; } ;
struct bwn_phy_g {int /*<<< orphan*/  pg_txctl; int /*<<< orphan*/  pg_rfatt; int /*<<< orphan*/  pg_bbatt; } ;
struct bwn_phy {int analog; int rf_ver; int rev; int chan; scalar_t__ gmode; struct bwn_phy_g phy_g; } ;
struct bwn_mac {int mac_flags; struct bwn_softc* mac_sc; struct bwn_phy mac_phy; } ;

/* Variables and functions */
 scalar_t__ BHND_BOARD_BU4306 ; 
 int BWN_MAC_FLAG_BADFRAME_PREEMP ; 
 int BWN_PHY_RADIO ; 
 int BWN_PHY_RADIO_BITFIELD ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int,int) ; 
 int BWN_READ_2 (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int,int) ; 
 scalar_t__ PCI_VENDOR_BROADCOM ; 
 int /*<<< orphan*/  bwn_phy_g_set_txpwr_sub (struct bwn_mac*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_g_switch_chan (struct bwn_mac*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_phy_init_b5(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_g *pg = &phy->phy_g;
	struct bwn_softc *sc = mac->mac_sc;
	uint16_t offset, value;
	uint8_t old_channel;

	if (phy->analog == 1)
		BWN_RF_SET(mac, 0x007a, 0x0050);
	if ((sc->sc_board_info.board_vendor != PCI_VENDOR_BROADCOM) &&
	    (sc->sc_board_info.board_type != BHND_BOARD_BU4306)) {
		value = 0x2120;
		for (offset = 0x00a8; offset < 0x00c7; offset++) {
			BWN_PHY_WRITE(mac, offset, value);
			value += 0x202;
		}
	}
	BWN_PHY_SETMASK(mac, 0x0035, 0xf0ff, 0x0700);
	if (phy->rf_ver == 0x2050)
		BWN_PHY_WRITE(mac, 0x0038, 0x0667);

	if (phy->gmode || phy->rev >= 2) {
		if (phy->rf_ver == 0x2050) {
			BWN_RF_SET(mac, 0x007a, 0x0020);
			BWN_RF_SET(mac, 0x0051, 0x0004);
		}
		BWN_WRITE_2(mac, BWN_PHY_RADIO, 0x0000);

		BWN_PHY_SET(mac, 0x0802, 0x0100);
		BWN_PHY_SET(mac, 0x042b, 0x2000);

		BWN_PHY_WRITE(mac, 0x001c, 0x186a);

		BWN_PHY_SETMASK(mac, 0x0013, 0x00ff, 0x1900);
		BWN_PHY_SETMASK(mac, 0x0035, 0xffc0, 0x0064);
		BWN_PHY_SETMASK(mac, 0x005d, 0xff80, 0x000a);
	}

	if (mac->mac_flags & BWN_MAC_FLAG_BADFRAME_PREEMP)
		BWN_PHY_SET(mac, BWN_PHY_RADIO_BITFIELD, (1 << 11));

	if (phy->analog == 1) {
		BWN_PHY_WRITE(mac, 0x0026, 0xce00);
		BWN_PHY_WRITE(mac, 0x0021, 0x3763);
		BWN_PHY_WRITE(mac, 0x0022, 0x1bc3);
		BWN_PHY_WRITE(mac, 0x0023, 0x06f9);
		BWN_PHY_WRITE(mac, 0x0024, 0x037e);
	} else
		BWN_PHY_WRITE(mac, 0x0026, 0xcc00);
	BWN_PHY_WRITE(mac, 0x0030, 0x00c6);
	BWN_WRITE_2(mac, 0x03ec, 0x3f22);

	if (phy->analog == 1)
		BWN_PHY_WRITE(mac, 0x0020, 0x3e1c);
	else
		BWN_PHY_WRITE(mac, 0x0020, 0x301c);

	if (phy->analog == 0)
		BWN_WRITE_2(mac, 0x03e4, 0x3000);

	old_channel = phy->chan;
	bwn_phy_g_switch_chan(mac, 7, 0);

	if (phy->rf_ver != 0x2050) {
		BWN_RF_WRITE(mac, 0x0075, 0x0080);
		BWN_RF_WRITE(mac, 0x0079, 0x0081);
	}

	BWN_RF_WRITE(mac, 0x0050, 0x0020);
	BWN_RF_WRITE(mac, 0x0050, 0x0023);

	if (phy->rf_ver == 0x2050) {
		BWN_RF_WRITE(mac, 0x0050, 0x0020);
		BWN_RF_WRITE(mac, 0x005a, 0x0070);
	}

	BWN_RF_WRITE(mac, 0x005b, 0x007b);
	BWN_RF_WRITE(mac, 0x005c, 0x00b0);
	BWN_RF_SET(mac, 0x007a, 0x0007);

	bwn_phy_g_switch_chan(mac, old_channel, 0);
	BWN_PHY_WRITE(mac, 0x0014, 0x0080);
	BWN_PHY_WRITE(mac, 0x0032, 0x00ca);
	BWN_PHY_WRITE(mac, 0x002a, 0x88a3);

	bwn_phy_g_set_txpwr_sub(mac, &pg->pg_bbatt, &pg->pg_rfatt,
	    pg->pg_txctl);

	if (phy->rf_ver == 0x2050)
		BWN_RF_WRITE(mac, 0x005d, 0x000d);

	BWN_WRITE_2(mac, 0x03e4, (BWN_READ_2(mac, 0x03e4) & 0xffc0) | 0x0004);
}