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
typedef  scalar_t__ usb_error_t ;
typedef  int uint16_t ;
struct ieee80211com {int ic_lintval; } ;
struct rum_softc {int /*<<< orphan*/  sc_sleep_time; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IEEE80211_TU_TO_TICKS (int) ; 
 int /*<<< orphan*/  RT2573_MAC_CSR11 ; 
 int RT2573_TBCN_DELAY (int) ; 
 int RT2573_TBCN_DELAY_MAX ; 
 int RT2573_TBCN_EXP (int) ; 
 int RT2573_TBCN_EXP_MAX ; 
 int /*<<< orphan*/  RUM_LOCK_ASSERT (struct rum_softc*) ; 
 scalar_t__ USB_ERR_NORMAL_COMPLETION ; 
 scalar_t__ rum_modbits (struct rum_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
rum_set_sleep_time(struct rum_softc *sc, uint16_t bintval)
{
	struct ieee80211com *ic = &sc->sc_ic;
	usb_error_t uerror;
	int exp, delay;

	RUM_LOCK_ASSERT(sc);

	exp = ic->ic_lintval / bintval;
	delay = ic->ic_lintval % bintval;

	if (exp > RT2573_TBCN_EXP_MAX)
		exp = RT2573_TBCN_EXP_MAX;
	if (delay > RT2573_TBCN_DELAY_MAX)
		delay = RT2573_TBCN_DELAY_MAX;

	uerror = rum_modbits(sc, RT2573_MAC_CSR11,
	    RT2573_TBCN_EXP(exp) |
	    RT2573_TBCN_DELAY(delay),
	    RT2573_TBCN_EXP(RT2573_TBCN_EXP_MAX) |
	    RT2573_TBCN_DELAY(RT2573_TBCN_DELAY_MAX));

	if (uerror != USB_ERR_NORMAL_COMPLETION)
		return (EIO);

	sc->sc_sleep_time = IEEE80211_TU_TO_TICKS(exp * bintval + delay);

	return (0);
}