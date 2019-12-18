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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct rt2560_softc {int dummy; } ;
struct ieee80211com {scalar_t__ ic_curmode; struct rt2560_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct rt2560_softc*,char*,int) ; 
 int IEEE80211_DUR_DIFS (int,int) ; 
 int IEEE80211_DUR_SLOT ; 
 int IEEE80211_GET_SLOTTIME (struct ieee80211com*) ; 
 scalar_t__ IEEE80211_MODE_11B ; 
 int RAL_READ (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int RAL_SIFS ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2560_CSR11 ; 
 int /*<<< orphan*/  RT2560_CSR18 ; 
 int /*<<< orphan*/  RT2560_CSR19 ; 
 int RT2560_TXRX_TURNAROUND ; 

__attribute__((used)) static void
rt2560_update_slot(struct ieee80211com *ic)
{
	struct rt2560_softc *sc = ic->ic_softc;
	uint8_t slottime;
	uint16_t tx_sifs, tx_pifs, tx_difs, eifs;
	uint32_t tmp;

#ifndef FORCE_SLOTTIME
	slottime = IEEE80211_GET_SLOTTIME(ic);
#else
	/*
	 * Setting slot time according to "short slot time" capability
	 * in beacon/probe_resp seems to cause problem to acknowledge
	 * certain AP's data frames transimitted at CCK/DS rates: the
	 * problematic AP keeps retransmitting data frames, probably
	 * because MAC level acks are not received by hardware.
	 * So we cheat a little bit here by claiming we are capable of
	 * "short slot time" but setting hardware slot time to the normal
	 * slot time.  ral(4) does not seem to have trouble to receive
	 * frames transmitted using short slot time even if hardware
	 * slot time is set to normal slot time.  If we didn't use this
	 * trick, we would have to claim that short slot time is not
	 * supported; this would give relative poor RX performance
	 * (-1Mb~-2Mb lower) and the _whole_ BSS would stop using short
	 * slot time.
	 */
	slottime = IEEE80211_DUR_SLOT;
#endif

	/* update the MAC slot boundaries */
	tx_sifs = RAL_SIFS - RT2560_TXRX_TURNAROUND;
	tx_pifs = tx_sifs + slottime;
	tx_difs = IEEE80211_DUR_DIFS(tx_sifs, slottime);
	eifs = (ic->ic_curmode == IEEE80211_MODE_11B) ? 364 : 60;

	tmp = RAL_READ(sc, RT2560_CSR11);
	tmp = (tmp & ~0x1f00) | slottime << 8;
	RAL_WRITE(sc, RT2560_CSR11, tmp);

	tmp = tx_pifs << 16 | tx_sifs;
	RAL_WRITE(sc, RT2560_CSR18, tmp);

	tmp = eifs << 16 | tx_difs;
	RAL_WRITE(sc, RT2560_CSR19, tmp);

	DPRINTF(sc, "setting slottime to %uus\n", slottime);
}