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
struct thread {int dummy; } ;
struct swdevt {struct g_consumer* sw_id; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  g_waitfor_event (int /*<<< orphan*/ ,struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sw_dev_mtx ; 
 int /*<<< orphan*/  swapgeom_close_ev ; 

__attribute__((used)) static void
swapgeom_close(struct thread *td, struct swdevt *sw)
{
	struct g_consumer *cp;

	mtx_lock(&sw_dev_mtx);
	cp = sw->sw_id;
	sw->sw_id = NULL;
	mtx_unlock(&sw_dev_mtx);

	/*
	 * swapgeom_close() may be called from the biodone context,
	 * where we cannot perform topology changes.  Delegate the
	 * work to the events thread.
	 */
	if (cp != NULL)
		g_waitfor_event(swapgeom_close_ev, cp, M_WAITOK, NULL);
}