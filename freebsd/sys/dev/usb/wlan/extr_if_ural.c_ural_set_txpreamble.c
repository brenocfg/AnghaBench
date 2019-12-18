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
typedef  int /*<<< orphan*/  uint16_t ;
struct ieee80211com {int ic_flags; } ;
struct ural_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int IEEE80211_F_SHPREAMBLE ; 
 int /*<<< orphan*/  RAL_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  RAL_TXRX_CSR10 ; 
 int /*<<< orphan*/  ural_read (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ural_set_txpreamble(struct ural_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint16_t tmp;

	tmp = ural_read(sc, RAL_TXRX_CSR10);

	tmp &= ~RAL_SHORT_PREAMBLE;
	if (ic->ic_flags & IEEE80211_F_SHPREAMBLE)
		tmp |= RAL_SHORT_PREAMBLE;

	ural_write(sc, RAL_TXRX_CSR10, tmp);
}