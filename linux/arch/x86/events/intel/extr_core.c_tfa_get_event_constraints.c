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
struct perf_event {int dummy; } ;
struct event_constraint {unsigned long long idxmsk64; int /*<<< orphan*/  weight; int /*<<< orphan*/  idxmsk; } ;
struct cpu_hw_events {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  allow_tsx_force_abort ; 
 struct event_constraint* dyn_constraint (struct cpu_hw_events*,struct event_constraint*,int) ; 
 struct event_constraint* hsw_get_event_constraints (struct cpu_hw_events*,int,struct perf_event*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct event_constraint *
tfa_get_event_constraints(struct cpu_hw_events *cpuc, int idx,
			  struct perf_event *event)
{
	struct event_constraint *c = hsw_get_event_constraints(cpuc, idx, event);

	/*
	 * Without TFA we must not use PMC3.
	 */
	if (!allow_tsx_force_abort && test_bit(3, c->idxmsk)) {
		c = dyn_constraint(cpuc, c, idx);
		c->idxmsk64 &= ~(1ULL << 3);
		c->weight--;
	}

	return c;
}