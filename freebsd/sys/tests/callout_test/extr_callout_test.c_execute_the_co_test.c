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
typedef  int uint32_t ;
struct callout_run {scalar_t__ callout_waiting; int co_number_callouts; int co_test; int index; scalar_t__ cnt_one; int /*<<< orphan*/  lock; int /*<<< orphan*/  cnt_zero; int /*<<< orphan*/ * co_array; } ;

/* Variables and functions */
 int callout_async_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_sbt_on (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct callout_run*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  co_saydone (void*) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  drainit ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_callout ; 
 int ticks ; 

void
execute_the_co_test(struct callout_run *rn)
{
	int i, ret, cpu;
	uint32_t tk_s, tk_e, tk_d;

	mtx_lock(&rn->lock);
	rn->callout_waiting = 0;
	for (i = 0; i < rn->co_number_callouts; i++) {
		if (rn->co_test == 1) {
			/* start all on spread out cpu's */
			cpu = i % mp_ncpus;
			callout_reset_sbt_on(&rn->co_array[i], 3, 0, test_callout, rn,
			    cpu, 0);
		} else {
			/* Start all on the same CPU */
			callout_reset_sbt_on(&rn->co_array[i], 3, 0, test_callout, rn,
			    rn->index, 0);
		}
	}
	tk_s = ticks;
	while (rn->callout_waiting != rn->co_number_callouts) {
		cpu_spinwait();
		tk_e = ticks;
		tk_d = tk_e - tk_s;
		if (tk_d > 100) {
			break;
		}
	}
	/* OK everyone is waiting and we have the lock */
	for (i = 0; i < rn->co_number_callouts; i++) {
		ret = callout_async_drain(&rn->co_array[i], drainit);
		if (ret) {
			rn->cnt_one++;
		} else {
			rn->cnt_zero++;
		}
	}
	rn->callout_waiting -= rn->cnt_one;
	mtx_unlock(&rn->lock);
	/* Now wait until all are done */
	tk_s = ticks;
	while (rn->callout_waiting > 0) {
		cpu_spinwait();
		tk_e = ticks;
		tk_d = tk_e - tk_s;
		if (tk_d > 100) {
			break;
		}
	}
	co_saydone((void *)rn);
}