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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  ic_macaddr; } ;
struct rtwn_softc {TYPE_1__ sc_ic; struct r12a_softc* sc_priv; } ;
struct r12a_softc {int bt_coex; int bt_ant_num; int type_pa_2g; int type_pa_5g; int type_lna_2g; int type_lna_5g; int rfe_type; void* ext_lna_5g; scalar_t__ ext_pa_5g; void* ext_lna_2g; scalar_t__ ext_pa_2g; } ;
struct r12a_rom {int rf_bt_opt; int rfe_option; int /*<<< orphan*/  macaddr_12a; int /*<<< orphan*/  rf_board_opt; int /*<<< orphan*/  lna_type_5g; int /*<<< orphan*/  lna_type_2g; int /*<<< orphan*/  pa_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int R12A_GET_ROM_LNA_TYPE (int /*<<< orphan*/ ,int) ; 
 int R12A_GET_ROM_PA_TYPE (int /*<<< orphan*/ ,int) ; 
 int R12A_RF_BT_OPT_ANT_NUM ; 
 scalar_t__ R12A_ROM_IS_PA_EXT_2GHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ R12A_ROM_IS_PA_EXT_5GHZ (int /*<<< orphan*/ ) ; 
 void* R21A_ROM_IS_LNA_EXT (int /*<<< orphan*/ ) ; 
 scalar_t__ R92C_BOARD_TYPE_HIGHPA ; 
 int /*<<< orphan*/  R92C_ROM_RF1_BOARD_TYPE ; 
 int /*<<< orphan*/  RTWN_GET_ROM_VAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r12a_parse_rom_common (struct rtwn_softc*,int /*<<< orphan*/ *) ; 

void
r12a_parse_rom(struct rtwn_softc *sc, uint8_t *buf)
{
	struct r12a_softc *rs = sc->sc_priv;
	struct r12a_rom *rom = (struct r12a_rom *)buf;
	uint8_t pa_type, lna_type_2g, lna_type_5g;

	/* Read PA/LNA types. */
	pa_type = RTWN_GET_ROM_VAR(rom->pa_type, 0);
	lna_type_2g = RTWN_GET_ROM_VAR(rom->lna_type_2g, 0);
	lna_type_5g = RTWN_GET_ROM_VAR(rom->lna_type_5g, 0);

	rs->ext_pa_2g = R12A_ROM_IS_PA_EXT_2GHZ(pa_type);
	rs->ext_pa_5g = R12A_ROM_IS_PA_EXT_5GHZ(pa_type);
	rs->ext_lna_2g = R21A_ROM_IS_LNA_EXT(lna_type_2g);
	rs->ext_lna_5g = R21A_ROM_IS_LNA_EXT(lna_type_5g);
	rs->bt_coex = (MS(rom->rf_board_opt, R92C_ROM_RF1_BOARD_TYPE) ==
	    R92C_BOARD_TYPE_HIGHPA);
	rs->bt_ant_num = (rom->rf_bt_opt & R12A_RF_BT_OPT_ANT_NUM);

	if (rs->ext_pa_2g) {
		rs->type_pa_2g =
		    R12A_GET_ROM_PA_TYPE(lna_type_2g, 0) |
		    (R12A_GET_ROM_PA_TYPE(lna_type_2g, 1) << 2);
	}
	if (rs->ext_pa_5g) {
		rs->type_pa_5g =
		    R12A_GET_ROM_PA_TYPE(lna_type_5g, 0) |
		    (R12A_GET_ROM_PA_TYPE(lna_type_5g, 1) << 2);
	}
	if (rs->ext_lna_2g) {
		rs->type_lna_2g =
		    R12A_GET_ROM_LNA_TYPE(lna_type_2g, 0) |
		    (R12A_GET_ROM_LNA_TYPE(lna_type_2g, 1) << 2);
	}
	if (rs->ext_lna_5g) {
		rs->type_lna_5g =
		    R12A_GET_ROM_LNA_TYPE(lna_type_5g, 0) |
		    (R12A_GET_ROM_LNA_TYPE(lna_type_5g, 1) << 2);
	}

	if (rom->rfe_option & 0x80) {
		if (rs->ext_lna_5g) {
			if (rs->ext_pa_5g) {
				if (rs->ext_pa_2g && rs->ext_lna_2g)
					rs->rfe_type = 3;
				else
					rs->rfe_type = 0;
			} else
				rs->rfe_type = 2;
		} else
			rs->rfe_type = 4;
	} else {
		rs->rfe_type = rom->rfe_option & 0x3f;

		/* workaround for incorrect EFUSE map */
		if (rs->rfe_type == 4 &&
		    rs->ext_pa_2g && rs->ext_lna_2g &&
		    rs->ext_pa_5g && rs->ext_lna_5g)
			rs->rfe_type = 0;
	}

	/* Read MAC address. */
	IEEE80211_ADDR_COPY(sc->sc_ic.ic_macaddr, rom->macaddr_12a);

	/* Execute common part of initialization. */
	r12a_parse_rom_common(sc, buf);
}