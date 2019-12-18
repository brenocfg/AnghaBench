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

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int PDROP ; 
 int PRIBIO ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_doorstep ; 
 int /*<<< orphan*/  g_eventlock ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_wait_event ; 
 int /*<<< orphan*/  g_wither_washer () ; 
 scalar_t__ g_wither_work ; 
 int hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ one_event () ; 

void
g_run_events()
{

	for (;;) {
		g_topology_lock();
		while (one_event())
			;
		mtx_assert(&g_eventlock, MA_OWNED);
		if (g_wither_work) {
			g_wither_work = 0;
			mtx_unlock(&g_eventlock);
			g_wither_washer();
			g_topology_unlock();
		} else {
			g_topology_unlock();
			msleep(&g_wait_event, &g_eventlock, PRIBIO | PDROP,
			    "-", TAILQ_EMPTY(&g_doorstep) ? 0 : hz / 10);
		}
	}
	/* NOTREACHED */
}