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
struct gv_softc {int /*<<< orphan*/  equeue_mtx; int /*<<< orphan*/  equeue; } ;
struct gv_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct gv_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  events ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
gv_remove_event(struct gv_softc *sc, struct gv_event *ev)
{

	KASSERT(sc != NULL, ("NULL sc"));
	KASSERT(ev != NULL, ("NULL ev"));
	mtx_lock(&sc->equeue_mtx);
	TAILQ_REMOVE(&sc->equeue, ev, events);
	mtx_unlock(&sc->equeue_mtx);
}