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
struct ural_softc {int dummy; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  RAL_TXRX_CSR11 ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ural_set_basicrates(struct ural_softc *sc, const struct ieee80211_channel *c)
{
	/* XXX wrong, take from rate set */
	/* update basic rate set */
	if (IEEE80211_IS_CHAN_5GHZ(c)) {
		/* 11a basic rates: 6, 12, 24Mbps */
		ural_write(sc, RAL_TXRX_CSR11, 0x150);
	} else if (IEEE80211_IS_CHAN_ANYG(c)) {
		/* 11g basic rates: 1, 2, 5.5, 11, 6, 12, 24Mbps */
		ural_write(sc, RAL_TXRX_CSR11, 0x15f);
	} else {
		/* 11b basic rates: 1, 2Mbps */
		ural_write(sc, RAL_TXRX_CSR11, 0x3);
	}
}