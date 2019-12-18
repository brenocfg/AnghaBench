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
struct ieee80211com {int dummy; } ;
struct iwi_softc {int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_notify_radio (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_rfkill_poll (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_stop_locked (struct iwi_softc*) ; 

__attribute__((used)) static void
iwi_radio_off(void *arg, int pending)
{
	struct iwi_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;
	IWI_LOCK_DECL;

	device_printf(sc->sc_dev, "radio turned off\n");

	ieee80211_notify_radio(ic, 0);

	IWI_LOCK(sc);
	iwi_stop_locked(sc);
	iwi_rfkill_poll(sc);
	IWI_UNLOCK(sc);
}