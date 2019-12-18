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
struct ksched {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int P1B_PRIO_MAX ; 
 int PRI_MAX_TIMESHARE ; 
 int PRI_MIN_TIMESHARE ; 
#define  SCHED_FIFO 130 
#define  SCHED_OTHER 129 
#define  SCHED_RR 128 

int
ksched_get_priority_max(struct ksched *ksched, int policy, int *prio)
{
	int e;

	e = 0;
	switch (policy)	{
	case SCHED_FIFO:
	case SCHED_RR:
		*prio = P1B_PRIO_MAX;
		break;
	case SCHED_OTHER:
		*prio = PRI_MAX_TIMESHARE - PRI_MIN_TIMESHARE;
		break;
	default:
		e = EINVAL;
		break;
	}
	return (e);
}