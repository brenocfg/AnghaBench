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
struct gv_softc {int /*<<< orphan*/  equeue_mtx; int /*<<< orphan*/  worker; int /*<<< orphan*/  equeue; } ;
struct gv_event {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GV_EVENT_THREAD_EXIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PDROP ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gv_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  events ; 
 struct gv_event* g_malloc (int,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct gv_softc*) ; 

void
gv_worker_exit(struct gv_softc *sc)
{
	struct gv_event *ev;

	ev = g_malloc(sizeof(*ev), M_WAITOK | M_ZERO);
	ev->type = GV_EVENT_THREAD_EXIT;

	mtx_lock(&sc->equeue_mtx);
	TAILQ_INSERT_TAIL(&sc->equeue, ev, events);
	wakeup(sc);
	msleep(sc->worker, &sc->equeue_mtx, PDROP, "gv_wor", 0);
}