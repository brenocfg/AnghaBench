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
typedef  int /*<<< orphan*/  uint8_t ;
struct rtwn_softc {int ntxchains; } ;
struct ieee80211_channel {int dummy; } ;
typedef  int /*<<< orphan*/  power ;

/* Variables and functions */
 int RTWN_RIDX_COUNT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r92c_write_txpower (struct rtwn_softc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r92e_get_txpower (struct rtwn_softc*,int,struct ieee80211_channel*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
r92e_set_txpower(struct rtwn_softc *sc, struct ieee80211_channel *c)
{
	uint8_t power[RTWN_RIDX_COUNT];
	int i;

	for (i = 0; i < sc->ntxchains; i++) {
		memset(power, 0, sizeof(power));
		/* Compute per-rate Tx power values. */
		r92e_get_txpower(sc, i, c, power);
		/* Write per-rate Tx power values to hardware. */
		r92c_write_txpower(sc, i, power);
	}
}