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
struct wpi_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ic_printf (struct ieee80211com*,char*) ; 
 int /*<<< orphan*/  ieee80211_restart_all (struct ieee80211com*) ; 

__attribute__((used)) static void
wpi_tx_timeout(void *arg)
{
	struct wpi_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;

	ic_printf(ic, "device timeout\n");
	ieee80211_restart_all(ic);
}