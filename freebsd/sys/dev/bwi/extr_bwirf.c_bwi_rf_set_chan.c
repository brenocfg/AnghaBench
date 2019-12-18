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
typedef  int u_int ;
struct bwi_softc {scalar_t__ sc_locale; } ;
struct TYPE_2__ {int rf_curchan; } ;
struct bwi_mac {TYPE_1__ mac_rf; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_CHAN ; 
 int /*<<< orphan*/  BWI_HFLAG_NOT_JAPAN ; 
 int /*<<< orphan*/  BWI_RF_2GHZ_CHAN (int) ; 
 int /*<<< orphan*/  BWI_RF_CHAN ; 
 int /*<<< orphan*/  BWI_RF_CHAN_EX ; 
 scalar_t__ BWI_SPROM_LOCALE_JAPAN ; 
 int /*<<< orphan*/  CSR_CLRBITS_2 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_SETBITS_2 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HFLAGS_CLRBITS (struct bwi_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFLAGS_SETBITS (struct bwi_mac*,int /*<<< orphan*/ ) ; 
 int IEEE80211_CHAN_ANY ; 
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwi_rf_work_around (struct bwi_mac*,int) ; 

void
bwi_rf_set_chan(struct bwi_mac *mac, u_int chan, int work_around)
{
	struct bwi_softc *sc = mac->mac_sc;

	if (chan == IEEE80211_CHAN_ANY)
		return;

	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_CHAN, chan);

	/* TODO: 11A */

	if (work_around)
		bwi_rf_work_around(mac, chan);

	CSR_WRITE_2(sc, BWI_RF_CHAN, BWI_RF_2GHZ_CHAN(chan));

	if (chan == 14) {
		if (sc->sc_locale == BWI_SPROM_LOCALE_JAPAN)
			HFLAGS_CLRBITS(mac, BWI_HFLAG_NOT_JAPAN);
		else
			HFLAGS_SETBITS(mac, BWI_HFLAG_NOT_JAPAN);
		CSR_SETBITS_2(sc, BWI_RF_CHAN_EX, (1 << 11)); /* XXX */
	} else {
		CSR_CLRBITS_2(sc, BWI_RF_CHAN_EX, 0x840); /* XXX */
	}
	DELAY(8000);	/* DELAY(2000); */

	mac->mac_rf.rf_curchan = chan;
}