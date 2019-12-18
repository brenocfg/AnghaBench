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
struct r12a_softc {int bt_coex; int bt_ant_num; void* ext_lna_5g; void* ext_lna_2g; int /*<<< orphan*/  ext_pa_5g; int /*<<< orphan*/  ext_pa_2g; } ;
struct r12a_rom {int rf_bt_opt; int /*<<< orphan*/  macaddr_21a; int /*<<< orphan*/  lna_type_5g; int /*<<< orphan*/  lna_type_2g; int /*<<< orphan*/  pa_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int R12A_RF_BT_OPT_ANT_NUM ; 
 void* R21A_ROM_IS_LNA_EXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R21A_ROM_IS_PA_EXT_2GHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R21A_ROM_IS_PA_EXT_5GHZ (int /*<<< orphan*/ ) ; 
 int R92C_MULTI_BT_FUNC_EN ; 
 int /*<<< orphan*/  R92C_MULTI_FUNC_CTRL ; 
 int /*<<< orphan*/  RTWN_GET_ROM_VAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  r12a_parse_rom_common (struct rtwn_softc*,int /*<<< orphan*/ *) ; 
 int rtwn_read_4 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 

void
r21a_parse_rom(struct rtwn_softc *sc, uint8_t *buf)
{
	struct r12a_softc *rs = sc->sc_priv;
	struct r12a_rom *rom = (struct r12a_rom *)buf;
	uint8_t pa_type, lna_type_2g, lna_type_5g;

	/* Read PA/LNA types. */
	pa_type = RTWN_GET_ROM_VAR(rom->pa_type, 0);
	lna_type_2g = RTWN_GET_ROM_VAR(rom->lna_type_2g, 0);
	lna_type_5g = RTWN_GET_ROM_VAR(rom->lna_type_5g, 0);

	rs->ext_pa_2g = R21A_ROM_IS_PA_EXT_2GHZ(pa_type);
	rs->ext_pa_5g = R21A_ROM_IS_PA_EXT_5GHZ(pa_type);
	rs->ext_lna_2g = R21A_ROM_IS_LNA_EXT(lna_type_2g);
	rs->ext_lna_5g = R21A_ROM_IS_LNA_EXT(lna_type_5g);

	RTWN_LOCK(sc);
	rs->bt_coex =
	    !!(rtwn_read_4(sc, R92C_MULTI_FUNC_CTRL) & R92C_MULTI_BT_FUNC_EN);
	RTWN_UNLOCK(sc);
	rs->bt_ant_num = (rom->rf_bt_opt & R12A_RF_BT_OPT_ANT_NUM);

	/* Read MAC address. */
	IEEE80211_ADDR_COPY(sc->sc_ic.ic_macaddr, rom->macaddr_21a);

	/* Execute common part of initialization. */
	r12a_parse_rom_common(sc, buf);
}