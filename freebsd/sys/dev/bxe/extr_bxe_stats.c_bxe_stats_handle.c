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
struct bxe_softc {int stats_state; int /*<<< orphan*/  panic; } ;
typedef  enum bxe_stats_state { ____Placeholder_bxe_stats_state } bxe_stats_state ;
typedef  enum bxe_stats_event { ____Placeholder_bxe_stats_event } bxe_stats_event ;
struct TYPE_2__ {int next_state; int /*<<< orphan*/  (* action ) (struct bxe_softc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  BXE_STATS_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_STATS_UNLOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_STATS ; 
 int STATS_EVENT_UPDATE ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 TYPE_1__** bxe_stats_stm ; 
 int /*<<< orphan*/  stub1 (struct bxe_softc*) ; 

void bxe_stats_handle(struct bxe_softc     *sc,
                      enum bxe_stats_event event)
{
    enum bxe_stats_state state;

    if (__predict_false(sc->panic)) {
        return;
    }

    BXE_STATS_LOCK(sc);
    state = sc->stats_state;
    sc->stats_state = bxe_stats_stm[state][event].next_state;
    BXE_STATS_UNLOCK(sc);

    bxe_stats_stm[state][event].action(sc);

    if (event != STATS_EVENT_UPDATE) {
        BLOGD(sc, DBG_STATS,
              "state %d -> event %d -> state %d\n",
              state, event, sc->stats_state);
    }
}