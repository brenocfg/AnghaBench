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
struct sched_param {void* sched_priority; } ;
struct rtprio {void* prio; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTP_PRIO_FIFO ; 
 void* RTP_PRIO_MAX ; 
 int /*<<< orphan*/  RTP_PRIO_NORMAL ; 
 int /*<<< orphan*/  RTP_PRIO_REALTIME ; 
#define  SCHED_FIFO 130 
#define  SCHED_OTHER 129 
#define  SCHED_RR 128 

int
_schedparam_to_rtp(int policy, const struct sched_param *param,
	struct rtprio *rtp)
{
	switch(policy) {
	case SCHED_RR:
		rtp->type = RTP_PRIO_REALTIME;
		rtp->prio = RTP_PRIO_MAX - param->sched_priority;
		break;
	case SCHED_FIFO:
		rtp->type = RTP_PRIO_FIFO;
		rtp->prio = RTP_PRIO_MAX - param->sched_priority;
		break;
	case SCHED_OTHER:
	default:
		rtp->type = RTP_PRIO_NORMAL;
		rtp->prio = 0;
		break;
	}
	return (0);
}