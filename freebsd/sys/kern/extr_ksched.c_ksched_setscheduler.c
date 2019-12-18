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
struct rtprio {int /*<<< orphan*/  prio; int /*<<< orphan*/  type; } ;
struct ksched {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ P1B_PRIO_MAX ; 
 scalar_t__ P1B_PRIO_MIN ; 
 scalar_t__ PRI_MAX_TIMESHARE ; 
 scalar_t__ PRI_MIN_TIMESHARE ; 
 int /*<<< orphan*/  RTP_PRIO_FIFO ; 
 int /*<<< orphan*/  RTP_PRIO_NORMAL ; 
 int /*<<< orphan*/  RTP_PRIO_REALTIME ; 
#define  SCHED_FIFO 130 
#define  SCHED_OTHER 129 
#define  SCHED_RR 128 
 int /*<<< orphan*/  p4prio_to_rtpprio (scalar_t__) ; 
 int /*<<< orphan*/  p4prio_to_tsprio (scalar_t__) ; 
 int /*<<< orphan*/  rtp_to_pri (struct rtprio*,struct thread*) ; 

int
ksched_setscheduler(struct ksched *ksched, struct thread *td, int policy,
    const struct sched_param *param)
{
	struct rtprio rtp;
	int e;

	e = 0;
	switch(policy) {
	case SCHED_RR:
	case SCHED_FIFO:
		if (param->sched_priority >= P1B_PRIO_MIN &&
		    param->sched_priority <= P1B_PRIO_MAX) {
			rtp.prio = p4prio_to_rtpprio(param->sched_priority);
			rtp.type = (policy == SCHED_FIFO) ? RTP_PRIO_FIFO :
			    RTP_PRIO_REALTIME;
			rtp_to_pri(&rtp, td);
		} else {
			e = EPERM;
		}
		break;
	case SCHED_OTHER:
		if (param->sched_priority >= 0 && param->sched_priority <=
		    (PRI_MAX_TIMESHARE - PRI_MIN_TIMESHARE)) {
			rtp.type = RTP_PRIO_NORMAL;
			rtp.prio = p4prio_to_tsprio(param->sched_priority);
			rtp_to_pri(&rtp, td);
		} else {
			e = EINVAL;
		}
		break;
	default:
		e = EINVAL;
		break;
	}
	return (e);
}