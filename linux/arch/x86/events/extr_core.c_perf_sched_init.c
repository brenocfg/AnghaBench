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
struct TYPE_2__ {int event; int weight; int unassigned; } ;
struct perf_sched {int max_events; int max_weight; int max_gp; TYPE_1__ state; struct event_constraint** constraints; } ;
struct event_constraint {int weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct perf_sched*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void perf_sched_init(struct perf_sched *sched, struct event_constraint **constraints,
			    int num, int wmin, int wmax, int gpmax)
{
	int idx;

	memset(sched, 0, sizeof(*sched));
	sched->max_events	= num;
	sched->max_weight	= wmax;
	sched->max_gp		= gpmax;
	sched->constraints	= constraints;

	for (idx = 0; idx < num; idx++) {
		if (constraints[idx]->weight == wmin)
			break;
	}

	sched->state.event	= idx;		/* start with min weight */
	sched->state.weight	= wmin;
	sched->state.unassigned	= num;
}