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
struct rtwn_softc {int /*<<< orphan*/  (* sc_node_free ) (struct ieee80211_node*) ;int /*<<< orphan*/ ** node_list; } ;
struct rtwn_node {size_t id; } ;
struct ieee80211_node {TYPE_1__* ni_ic; } ;
struct TYPE_2__ {struct rtwn_softc* ic_softc; } ;

/* Variables and functions */
 size_t RTWN_MACID_UNDEFINED ; 
 struct rtwn_node* RTWN_NODE (struct ieee80211_node*) ; 
 int /*<<< orphan*/  RTWN_NT_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_NT_UNLOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_cmd_sleepable (struct rtwn_softc*,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_set_media_status ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*) ; 

__attribute__((used)) static void
rtwn_node_free(struct ieee80211_node *ni)
{
	struct rtwn_softc *sc = ni->ni_ic->ic_softc;
	struct rtwn_node *un = RTWN_NODE(ni);

	RTWN_NT_LOCK(sc);
	if (un->id != RTWN_MACID_UNDEFINED) {
		sc->node_list[un->id] = NULL;
		rtwn_cmd_sleepable(sc, &un->id, sizeof(un->id),
		    rtwn_set_media_status);
	}
	RTWN_NT_UNLOCK(sc);

	sc->sc_node_free(ni);
}