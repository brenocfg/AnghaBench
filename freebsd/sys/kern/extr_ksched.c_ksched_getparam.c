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
struct thread {int dummy; } ;
struct sched_param {scalar_t__ sched_priority; } ;
struct rtprio {scalar_t__ prio; int /*<<< orphan*/  type; } ;
struct ksched {int dummy; } ;

/* Variables and functions */
 scalar_t__ PRI_MAX_TIMESHARE ; 
 scalar_t__ PRI_MIN_TIMESHARE ; 
 scalar_t__ RTP_PRIO_IS_REALTIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pri_to_rtp (struct thread*,struct rtprio*) ; 
 scalar_t__ rtpprio_to_p4prio (scalar_t__) ; 
 scalar_t__ tsprio_to_p4prio (scalar_t__) ; 

int
ksched_getparam(struct ksched *ksched, struct thread *td,
    struct sched_param *param)
{
	struct rtprio rtp;

	pri_to_rtp(td, &rtp);
	if (RTP_PRIO_IS_REALTIME(rtp.type))
		param->sched_priority = rtpprio_to_p4prio(rtp.prio);
	else {
		if (PRI_MIN_TIMESHARE < rtp.prio) 
			/*
		 	 * The interactive score has it to min realtime
			 * so we must show max (64 most likely).
			 */ 
			param->sched_priority = PRI_MAX_TIMESHARE -
			    PRI_MIN_TIMESHARE;
		else
			param->sched_priority = tsprio_to_p4prio(rtp.prio);
	}
	return (0);
}