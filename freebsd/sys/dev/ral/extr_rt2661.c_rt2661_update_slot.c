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
struct rt2661_softc {int dummy; } ;
struct ieee80211com {struct rt2661_softc* ic_softc; } ;

/* Variables and functions */
 int IEEE80211_GET_SLOTTIME (struct ieee80211com*) ; 
 int RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2661_MAC_CSR9 ; 

__attribute__((used)) static void
rt2661_update_slot(struct ieee80211com *ic)
{
	struct rt2661_softc *sc = ic->ic_softc;
	uint8_t slottime;
	uint32_t tmp;

	slottime = IEEE80211_GET_SLOTTIME(ic);

	tmp = RAL_READ(sc, RT2661_MAC_CSR9);
	tmp = (tmp & ~0xff) | slottime;
	RAL_WRITE(sc, RT2661_MAC_CSR9, tmp);
}