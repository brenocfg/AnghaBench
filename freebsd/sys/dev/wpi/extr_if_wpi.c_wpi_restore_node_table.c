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
struct wpi_vap {scalar_t__ wv_gtk; } ;
struct ieee80211com {int /*<<< orphan*/  ic_sta; } ;
struct wpi_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPI_NT_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_NT_UNLOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  ieee80211_crypto_reload_keys (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_iterate_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpi_softc*) ; 
 int /*<<< orphan*/  wpi_restore_node ; 

__attribute__((used)) static void
wpi_restore_node_table(struct wpi_softc *sc, struct wpi_vap *wvp)
{
	struct ieee80211com *ic = &sc->sc_ic;

	/* Set group keys once. */
	WPI_NT_LOCK(sc);
	wvp->wv_gtk = 0;
	WPI_NT_UNLOCK(sc);

	ieee80211_iterate_nodes(&ic->ic_sta, wpi_restore_node, sc);
	ieee80211_crypto_reload_keys(ic);
}