#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpi_softc {int /*<<< orphan*/  (* sc_node_free ) (struct ieee80211_node*) ;} ;
struct wpi_node {scalar_t__ id; } ;
struct ieee80211_node {TYPE_1__* ni_ic; } ;
struct TYPE_2__ {struct wpi_softc* ic_softc; } ;

/* Variables and functions */
 scalar_t__ WPI_ID_UNDEFINED ; 
 struct wpi_node* WPI_NODE (struct ieee80211_node*) ; 
 int /*<<< orphan*/  WPI_NT_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_NT_UNLOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*) ; 
 scalar_t__ wpi_check_node_entry (struct wpi_softc*,scalar_t__) ; 
 int /*<<< orphan*/  wpi_del_node (struct wpi_softc*,struct ieee80211_node*) ; 
 int /*<<< orphan*/  wpi_del_node_entry (struct wpi_softc*,scalar_t__) ; 

__attribute__((used)) static void
wpi_node_free(struct ieee80211_node *ni)
{
	struct wpi_softc *sc = ni->ni_ic->ic_softc;
	struct wpi_node *wn = WPI_NODE(ni);

	if (wn->id != WPI_ID_UNDEFINED) {
		WPI_NT_LOCK(sc);
		if (wpi_check_node_entry(sc, wn->id)) {
			wpi_del_node_entry(sc, wn->id);
			wpi_del_node(sc, ni);
		}
		WPI_NT_UNLOCK(sc);
	}

	sc->sc_node_free(ni);
}