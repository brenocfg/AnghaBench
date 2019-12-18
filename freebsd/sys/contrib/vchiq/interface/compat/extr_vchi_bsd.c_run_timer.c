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
struct timer_list {void (* function ) (unsigned long) ;unsigned long data; int /*<<< orphan*/  mtx; int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
run_timer(void *arg)
{
	struct timer_list *t = (struct timer_list *) arg;
	void (*function)(unsigned long);

	mtx_lock_spin(&t->mtx);
	if (callout_pending(&t->callout)) {
		/* callout was reset */
		mtx_unlock_spin(&t->mtx);
		return;
	}
	if (!callout_active(&t->callout)) {
		/* callout was stopped */
		mtx_unlock_spin(&t->mtx);
		return;
	}
	callout_deactivate(&t->callout);

	function = t->function;
	mtx_unlock_spin(&t->mtx);

	function(t->data);
}