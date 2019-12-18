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
typedef  int uint8_t ;
struct rtwn_softc {int ntxchains; int sc_debug; } ;
struct ieee80211_channel {int dummy; } ;
typedef  int /*<<< orphan*/  power ;

/* Variables and functions */
 int RTWN_DEBUG_TXPWR ; 
 int RTWN_RIDX_CCK1 ; 
 int RTWN_RIDX_COUNT ; 
 int RTWN_RIDX_HT_MCS (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  r92c_write_txpower (struct rtwn_softc*,int,int*) ; 
 int /*<<< orphan*/  rtwn_r92c_get_txpower (struct rtwn_softc*,int,struct ieee80211_channel*,int*) ; 

__attribute__((used)) static void
r92c_set_txpower(struct rtwn_softc *sc, struct ieee80211_channel *c)
{
	uint8_t power[RTWN_RIDX_COUNT];
	int i;

	for (i = 0; i < sc->ntxchains; i++) {
		memset(power, 0, sizeof(power));
		/* Compute per-rate Tx power values. */
		rtwn_r92c_get_txpower(sc, i, c, power);
#ifdef RTWN_DEBUG
		if (sc->sc_debug & RTWN_DEBUG_TXPWR) {
			int max_mcs, ridx;

			max_mcs = RTWN_RIDX_HT_MCS(sc->ntxchains * 8 - 1);

			/* Dump per-rate Tx power values. */
			printf("Tx power for chain %d:\n", i);
			for (ridx = RTWN_RIDX_CCK1; ridx <= max_mcs; ridx++)
				printf("Rate %d = %u\n", ridx, power[ridx]);
		}
#endif
		/* Write per-rate Tx power values to hardware. */
		r92c_write_txpower(sc, i, power);
	}
}