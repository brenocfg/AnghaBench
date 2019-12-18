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
struct rum_vap {int /*<<< orphan*/  ratectl_ch; } ;
struct rum_softc {int /*<<< orphan*/  sta; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2573_STA_CSR0 ; 
 struct rum_vap* RUM_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  rum_ratectl_timeout ; 
 int /*<<< orphan*/  rum_read_multi (struct rum_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rum_vap*) ; 

__attribute__((used)) static void
rum_ratectl_start(struct rum_softc *sc, struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct rum_vap *rvp = RUM_VAP(vap);

	/* clear statistic registers (STA_CSR0 to STA_CSR5) */
	rum_read_multi(sc, RT2573_STA_CSR0, sc->sta, sizeof sc->sta);

	usb_callout_reset(&rvp->ratectl_ch, hz, rum_ratectl_timeout, rvp);
}