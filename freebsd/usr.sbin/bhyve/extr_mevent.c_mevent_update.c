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
struct mevent {int me_state; int me_cq; } ;

/* Variables and functions */
 int EV_DELETE ; 
 int EV_DISABLE ; 
 int EV_ENABLE ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct mevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct mevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  change_head ; 
 int /*<<< orphan*/  me_list ; 
 int /*<<< orphan*/  mevent_notify () ; 
 int /*<<< orphan*/  mevent_qlock () ; 
 int /*<<< orphan*/  mevent_qunlock () ; 

__attribute__((used)) static int
mevent_update(struct mevent *evp, bool enable)
{
	int newstate;

	mevent_qlock();

	/*
	 * It's not possible to enable/disable a deleted event
	 */
	assert((evp->me_state & EV_DELETE) == 0);

	newstate = evp->me_state;
	if (enable) {
		newstate |= EV_ENABLE;
		newstate &= ~EV_DISABLE;
	} else {
		newstate |= EV_DISABLE;
		newstate &= ~EV_ENABLE;
	}

	/*
	 * No update needed if state isn't changing
	 */
	if (evp->me_state != newstate) {
		evp->me_state = newstate;

		/*
		 * Place the entry onto the changed list if not
		 * already there.
		 */
		if (evp->me_cq == 0) {
			evp->me_cq = 1;
			LIST_REMOVE(evp, me_list);
			LIST_INSERT_HEAD(&change_head, evp, me_list);
			mevent_notify();
		}
	}

	mevent_qunlock();

	return (0);
}