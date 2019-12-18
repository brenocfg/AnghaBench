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
struct callout_run {int index; int co_number_callouts; int co_return_npa; int co_completed; int drain_calls; int cnt_zero; int cnt_one; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
co_saydone(void *arg)
{
	struct callout_run *rn;

	rn = (struct callout_run *)arg;
	printf("The callout test is now complete for thread %d\n",
	    rn->index);
	printf("number_callouts:%d\n",
	    rn->co_number_callouts);
	printf("Callouts that bailed (Not PENDING or ACTIVE cleared):%d\n",
	    rn->co_return_npa);
	printf("Callouts that completed:%d\n", rn->co_completed);
	printf("Drain calls:%d\n", rn->drain_calls);
	printf("Zero returns:%d non-zero:%d\n",
	    rn->cnt_zero,
	    rn->cnt_one);

}