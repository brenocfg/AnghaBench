#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  ic_macaddr; } ;
struct rtwn_softc {int ntxchains; TYPE_2__ sc_ic; int /*<<< orphan*/  thermal_meter; struct r92e_softc* sc_priv; } ;
struct r92e_tx_pwr_diff_2g {TYPE_3__* diff123; int /*<<< orphan*/  ht20_ofdm; } ;
struct r92e_tx_pwr_2g {int /*<<< orphan*/ * cck; int /*<<< orphan*/ * ht40; } ;
struct r92e_softc {int /*<<< orphan*/  regulatory; void*** bw40_tx_pwr_diff_2g; void*** bw20_tx_pwr_diff_2g; void*** ofdm_tx_pwr_diff_2g; void*** cck_tx_pwr_diff_2g; scalar_t__** cck_tx_pwr; scalar_t__** ht40_tx_pwr_2g; scalar_t__ crystalcap; } ;
struct r92e_rom {int /*<<< orphan*/  macaddr; int /*<<< orphan*/  rf_board_opt; TYPE_1__* tx_pwr; int /*<<< orphan*/  crystalcap; int /*<<< orphan*/  thermal_meter; } ;
struct TYPE_6__ {int /*<<< orphan*/  ht40_ht20; int /*<<< orphan*/  ofdm_cck; } ;
struct TYPE_4__ {struct r92e_tx_pwr_diff_2g pwr_diff_2g; struct r92e_tx_pwr_2g pwr_2g; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIGH_PART ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOW_PART ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_ROM_RF1_REGULATORY ; 
 scalar_t__ R92E_DEF_TX_PWR_2G ; 
 scalar_t__ R92E_DEF_TX_PWR_DIFF ; 
 scalar_t__ R92E_DEF_TX_PWR_HT20_DIFF ; 
 int R92E_GROUP_2G ; 
 scalar_t__ R92E_ROM_CRYSTALCAP_DEF ; 
 scalar_t__ RTWN_GET_ROM_VAR (int /*<<< orphan*/ ,scalar_t__) ; 
 void* RTWN_SIGN4TO8 (int /*<<< orphan*/ ) ; 
 int nitems (TYPE_3__*) ; 

void
r92e_parse_rom(struct rtwn_softc *sc, uint8_t *buf)
{
	struct r92e_softc *rs = sc->sc_priv;
	struct r92e_rom *rom = (struct r92e_rom *)buf;
	uint8_t pwr_diff;
	int i, j, k;

	sc->thermal_meter = rom->thermal_meter;
	rs->crystalcap = RTWN_GET_ROM_VAR(rom->crystalcap,
	    R92E_ROM_CRYSTALCAP_DEF);

	for (i = 0; i < sc->ntxchains; i++) {
		struct r92e_tx_pwr_2g *pwr_2g = &rom->tx_pwr[i].pwr_2g;
		struct r92e_tx_pwr_diff_2g *pwr_diff_2g =
		    &rom->tx_pwr[i].pwr_diff_2g;

		for (j = 0; j < R92E_GROUP_2G - 1; j++) {
			rs->cck_tx_pwr[i][j] =
			    RTWN_GET_ROM_VAR(pwr_2g->cck[j],
				R92E_DEF_TX_PWR_2G);
			rs->ht40_tx_pwr_2g[i][j] =
			    RTWN_GET_ROM_VAR(pwr_2g->ht40[j],
				R92E_DEF_TX_PWR_2G);
		}
		rs->cck_tx_pwr[i][j] = RTWN_GET_ROM_VAR(pwr_2g->cck[j],
		    R92E_DEF_TX_PWR_2G);

		rs->cck_tx_pwr_diff_2g[i][0] = 0;
		rs->ofdm_tx_pwr_diff_2g[i][0] = RTWN_SIGN4TO8(
		    MS(pwr_diff_2g->ht20_ofdm, LOW_PART));
		rs->bw20_tx_pwr_diff_2g[i][0] = RTWN_SIGN4TO8(
		    MS(pwr_diff_2g->ht20_ofdm, HIGH_PART));
		rs->bw40_tx_pwr_diff_2g[i][0] = 0;
		pwr_diff = RTWN_GET_ROM_VAR(pwr_diff_2g->ht20_ofdm,
		    R92E_DEF_TX_PWR_HT20_DIFF);
		if (pwr_diff != R92E_DEF_TX_PWR_HT20_DIFF) {
			rs->ofdm_tx_pwr_diff_2g[i][0] = RTWN_SIGN4TO8(
			    MS(pwr_diff_2g->ht20_ofdm, LOW_PART));
			rs->bw20_tx_pwr_diff_2g[i][0] = RTWN_SIGN4TO8(
			    MS(pwr_diff_2g->ht20_ofdm, HIGH_PART));
		} else {
			rs->ofdm_tx_pwr_diff_2g[i][0] =
			rs->bw20_tx_pwr_diff_2g[i][0] = pwr_diff;
		}

		for (j = 1, k = 0; k < nitems(pwr_diff_2g->diff123); j++, k++) {
			pwr_diff = RTWN_GET_ROM_VAR(
			    pwr_diff_2g->diff123[k].ofdm_cck,
			    R92E_DEF_TX_PWR_DIFF);
			if (pwr_diff != R92E_DEF_TX_PWR_DIFF) {
				rs->cck_tx_pwr_diff_2g[i][j] = RTWN_SIGN4TO8(
				    MS(pwr_diff_2g->diff123[k].ofdm_cck,
				    LOW_PART));
				rs->ofdm_tx_pwr_diff_2g[i][j] = RTWN_SIGN4TO8(
				    MS(pwr_diff_2g->diff123[k].ofdm_cck,
				    HIGH_PART));
			} else {
				rs->cck_tx_pwr_diff_2g[i][j] =
				rs->ofdm_tx_pwr_diff_2g[i][j] = pwr_diff;
			}
			pwr_diff = RTWN_GET_ROM_VAR(
			    pwr_diff_2g->diff123[k].ht40_ht20,
			    R92E_DEF_TX_PWR_DIFF);
			if (pwr_diff != R92E_DEF_TX_PWR_DIFF) {
				rs->bw20_tx_pwr_diff_2g[i][j] = RTWN_SIGN4TO8(
				    MS(pwr_diff_2g->diff123[k].ht40_ht20,
				    LOW_PART));
				rs->bw40_tx_pwr_diff_2g[i][j] = RTWN_SIGN4TO8(
				    MS(pwr_diff_2g->diff123[k].ht40_ht20,
				    HIGH_PART));
			} else {
				rs->bw20_tx_pwr_diff_2g[i][j] =
				rs->bw40_tx_pwr_diff_2g[i][j] = pwr_diff;
			}
		}
	}

	rs->regulatory = MS(rom->rf_board_opt, R92C_ROM_RF1_REGULATORY);

	/* Read MAC address. */
	IEEE80211_ADDR_COPY(sc->sc_ic.ic_macaddr, rom->macaddr);
}