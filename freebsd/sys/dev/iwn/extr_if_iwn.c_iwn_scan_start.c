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
struct iwn_softc {int dummy; } ;
struct ieee80211com {struct iwn_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_LED_LINK ; 
 int /*<<< orphan*/  IWN_LOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  IWN_UNLOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  iwn_set_led (struct iwn_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
iwn_scan_start(struct ieee80211com *ic)
{
	struct iwn_softc *sc = ic->ic_softc;

	IWN_LOCK(sc);
	/* make the link LED blink while we're scanning */
	iwn_set_led(sc, IWN_LED_LINK, 20, 2);
	IWN_UNLOCK(sc);
}