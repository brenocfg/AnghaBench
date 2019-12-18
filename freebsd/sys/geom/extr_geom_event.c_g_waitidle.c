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
struct TYPE_2__ {int /*<<< orphan*/  td_pflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPAUSE ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TDP_GEOM ; 
 int /*<<< orphan*/  TSUNWAIT (char*) ; 
 int /*<<< orphan*/  TSWAIT (char*) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  g_eventlock ; 
 int /*<<< orphan*/  g_events ; 
 int /*<<< orphan*/  g_pending_events ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
g_waitidle(void)
{

	g_topology_assert_not();

	mtx_lock(&g_eventlock);
	TSWAIT("GEOM events");
	while (!TAILQ_EMPTY(&g_events))
		msleep(&g_pending_events, &g_eventlock, PPAUSE,
		    "g_waitidle", hz/5);
	TSUNWAIT("GEOM events");
	mtx_unlock(&g_eventlock);
	curthread->td_pflags &= ~TDP_GEOM;
}