#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ubt_softc_p ;
struct TYPE_3__ {int sc_task_flags; int /*<<< orphan*/  sc_task; int /*<<< orphan*/  sc_ng_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int UBT_FLAG_T_PENDING ; 
 int UBT_FLAG_T_START_ALL ; 
 int UBT_FLAG_T_STOP_ALL ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
ubt_task_schedule(ubt_softc_p sc, int action)
{
	mtx_assert(&sc->sc_ng_mtx, MA_OWNED);

	/*
	 * Try to handle corner case when "start all" and "stop all"
	 * actions can both be set before task is executed.
	 *
	 * The rules are
	 *
	 * sc_task_flags	action		new sc_task_flags
	 * ------------------------------------------------------
	 * 0			start		start
	 * 0			stop		stop
	 * start		start		start
	 * start		stop		stop
	 * stop			start		stop|start
	 * stop			stop		stop
	 * stop|start		start		stop|start
	 * stop|start		stop		stop
	 */

	if (action != 0) {
		if ((action & UBT_FLAG_T_STOP_ALL) != 0)
			sc->sc_task_flags &= ~UBT_FLAG_T_START_ALL;

		sc->sc_task_flags |= action;
	}

	if (sc->sc_task_flags & UBT_FLAG_T_PENDING)
		return;

	if (taskqueue_enqueue(taskqueue_swi, &sc->sc_task) == 0) {
		sc->sc_task_flags |= UBT_FLAG_T_PENDING;
		return;
	}

	/* XXX: i think this should never happen */
}