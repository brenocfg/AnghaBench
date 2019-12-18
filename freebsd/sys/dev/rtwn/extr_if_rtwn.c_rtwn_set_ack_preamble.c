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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211com {int ic_flags; } ;
struct rtwn_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int IEEE80211_F_SHPREAMBLE ; 
 int /*<<< orphan*/  R92C_WMAC_TRXPTCL_CTL ; 
 int /*<<< orphan*/  R92C_WMAC_TRXPTCL_SHPRE ; 
 int /*<<< orphan*/  rtwn_read_4 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtwn_set_ack_preamble(struct rtwn_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t reg;

	reg = rtwn_read_4(sc, R92C_WMAC_TRXPTCL_CTL);
	if (ic->ic_flags & IEEE80211_F_SHPREAMBLE)
		reg |= R92C_WMAC_TRXPTCL_SHPRE;
	else
		reg &= ~R92C_WMAC_TRXPTCL_SHPRE;
	rtwn_write_4(sc, R92C_WMAC_TRXPTCL_CTL, reg);
}