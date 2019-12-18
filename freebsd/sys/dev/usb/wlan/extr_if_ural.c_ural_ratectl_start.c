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
struct ural_vap {int /*<<< orphan*/  ratectl_ch; } ;
struct ural_softc {int /*<<< orphan*/  sta; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_STA_CSR0 ; 
 struct ural_vap* URAL_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ural_ratectl_timeout ; 
 int /*<<< orphan*/  ural_read_multi (struct ural_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ural_vap*) ; 

__attribute__((used)) static void
ural_ratectl_start(struct ural_softc *sc, struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ural_vap *uvp = URAL_VAP(vap);

	/* clear statistic registers (STA_CSR0 to STA_CSR10) */
	ural_read_multi(sc, RAL_STA_CSR0, sc->sta, sizeof sc->sta);

	usb_callout_reset(&uvp->ratectl_ch, hz, ural_ratectl_timeout, uvp);
}