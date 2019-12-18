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
struct TYPE_2__ {int /*<<< orphan*/  used; int /*<<< orphan*/  counter; } ;
struct perf_sched {size_t saved_states; TYPE_1__ state; TYPE_1__* saved; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool perf_sched_restore_state(struct perf_sched *sched)
{
	if (!sched->saved_states)
		return false;

	sched->saved_states--;
	sched->state = sched->saved[sched->saved_states];

	/* continue with next counter: */
	clear_bit(sched->state.counter++, sched->state.used);

	return true;
}