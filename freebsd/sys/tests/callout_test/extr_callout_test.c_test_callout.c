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
struct callout_run {int /*<<< orphan*/  callout_waiting; int /*<<< orphan*/  lock; int /*<<< orphan*/  co_completed; int /*<<< orphan*/ * co_array; int /*<<< orphan*/  co_return_npa; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int curcpu ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_callout(void *arg)
{
	struct callout_run *rn;
	int cpu;

	critical_enter();
	cpu = curcpu;
	critical_exit();
	rn = (struct callout_run *)arg;
	atomic_add_int(&rn->callout_waiting, 1);
	mtx_lock(&rn->lock);
	if (callout_pending(&rn->co_array[cpu]) ||
	    !callout_active(&rn->co_array[cpu])) {
		rn->co_return_npa++;
		atomic_subtract_int(&rn->callout_waiting, 1);
		mtx_unlock(&rn->lock);
		return;
	}
	callout_deactivate(&rn->co_array[cpu]);
	rn->co_completed++;
	mtx_unlock(&rn->lock);
	atomic_subtract_int(&rn->callout_waiting, 1);
}