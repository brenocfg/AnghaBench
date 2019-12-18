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
struct user_evtchn {int /*<<< orphan*/  port; struct per_user_data* user; } ;
struct per_user_data {scalar_t__ ring_prod; scalar_t__ ring_cons; int ring_overflow; int /*<<< orphan*/  ring_prod_mutex; int /*<<< orphan*/  ev_rsel; int /*<<< orphan*/ * ring; } ;

/* Variables and functions */
 size_t EVTCHN_RING_MASK (scalar_t__) ; 
 scalar_t__ EVTCHN_RING_SIZE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct per_user_data*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
evtchn_interrupt(void *arg)
{
	struct user_evtchn *evtchn;
	struct per_user_data *u;

	evtchn = arg;
	u = evtchn->user;

	/*
	 * Protect against concurrent events using this handler
	 * on different CPUs.
	 */
	mtx_lock(&u->ring_prod_mutex);
	if ((u->ring_prod - u->ring_cons) < EVTCHN_RING_SIZE) {
		u->ring[EVTCHN_RING_MASK(u->ring_prod)] = evtchn->port;
		wmb(); /* Ensure ring contents visible */
		if (u->ring_cons == u->ring_prod++) {
			wakeup(u);
			selwakeup(&u->ev_rsel);
		}
	} else
		u->ring_overflow = 1;
	mtx_unlock(&u->ring_prod_mutex);
}