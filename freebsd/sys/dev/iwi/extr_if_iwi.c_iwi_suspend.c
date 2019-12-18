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
struct iwi_softc {struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iwi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_suspend_all (struct ieee80211com*) ; 

__attribute__((used)) static int
iwi_suspend(device_t dev)
{
	struct iwi_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;

	ieee80211_suspend_all(ic);
	return 0;
}