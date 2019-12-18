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
struct kern_test {int tot_threads_running; scalar_t__ test_options; } ;
struct callout_test {int number_of_callouts; int /*<<< orphan*/  test_number; } ;
struct callout_run {int index; int co_number_callouts; int co_return_npa; int /*<<< orphan*/ * co_array; int /*<<< orphan*/  co_test; scalar_t__ cnt_one; scalar_t__ cnt_zero; scalar_t__ drain_calls; scalar_t__ callout_waiting; scalar_t__ co_completed; int /*<<< orphan*/  lock; } ;
struct callout {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_MPSAFE ; 
 int /*<<< orphan*/  MTX_DUPOK ; 
 int /*<<< orphan*/  M_CALLTMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct callout_run** comaster ; 
 int /*<<< orphan*/  execute_the_co_test (struct callout_run*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct callout_run*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_callout_test(struct kern_test *test)
{
	struct callout_test *u;
	size_t sz;
	int i;
	struct callout_run *rn;
	int index = test->tot_threads_running;

	u = (struct callout_test *)test->test_options;
	if (comaster[index] == NULL) {
		rn = comaster[index] = malloc(sizeof(struct callout_run), M_CALLTMP, M_WAITOK);
		memset(comaster[index], 0, sizeof(struct callout_run));
		mtx_init(&rn->lock, "callouttest", NULL, MTX_DUPOK);
		rn->index = index;
	} else {
		rn = comaster[index];
		rn->co_number_callouts = rn->co_return_npa = 0;
		rn->co_completed = rn->callout_waiting = 0;
		rn->drain_calls = rn->cnt_zero = rn->cnt_one = 0;
		if (rn->co_array) {
			free(rn->co_array, M_CALLTMP);
			rn->co_array = NULL;
		}
	}
	rn->co_number_callouts = u->number_of_callouts;
	rn->co_test = u->test_number;
	sz = sizeof(struct callout) * rn->co_number_callouts;
	rn->co_array = malloc(sz, M_CALLTMP, M_WAITOK);
	for (i = 0; i < rn->co_number_callouts; i++) {
		callout_init(&rn->co_array[i], CALLOUT_MPSAFE);
	}
	execute_the_co_test(rn);
}