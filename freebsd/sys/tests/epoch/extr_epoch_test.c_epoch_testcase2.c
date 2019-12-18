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
struct mtx {int dummy; } ;
struct epoch_tracker {int dummy; } ;
struct epoch_test_instance {int threadid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  epoch_enter_preempt (int /*<<< orphan*/ ,struct epoch_tracker*) ; 
 int /*<<< orphan*/  epoch_exit_preempt (int /*<<< orphan*/ ,struct epoch_tracker*) ; 
 int /*<<< orphan*/  epoch_wait_preempt (int /*<<< orphan*/ ) ; 
 int iterations ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 struct mtx mutexA ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  test_epoch ; 
 int ticks ; 

__attribute__((used)) static void
epoch_testcase2(struct epoch_test_instance *eti)
{
	int i, startticks;
	struct mtx *mtxp;
	struct epoch_tracker et;

	startticks = ticks;
	i = 0;
	mtxp = &mutexA;

	while (i < iterations) {
		epoch_enter_preempt(test_epoch, &et);
		mtx_lock(mtxp);
		DELAY(1);
		i++;
		mtx_unlock(mtxp);
		epoch_exit_preempt(test_epoch, &et);
		epoch_wait_preempt(test_epoch);
	}
	printf("test2: thread: %d took %d ticks to complete %d iterations\n",
		   eti->threadid, ticks - startticks, iterations);
}