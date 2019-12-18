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
struct rtprio {int type; void* prio; } ;

/* Variables and functions */
#define  RTP_PRIO_FIFO 129 
 void* RTP_PRIO_MAX ; 
#define  RTP_PRIO_REALTIME 128 
 int SCHED_FIFO ; 
 int SCHED_OTHER ; 
 int SCHED_RR ; 

int
_rtp_to_schedparam(const struct rtprio *rtp, int *policy,
	struct sched_param *param)
{
	switch(rtp->type) {
	case RTP_PRIO_REALTIME:
		*policy = SCHED_RR;
		param->sched_priority = RTP_PRIO_MAX - rtp->prio;
		break;
	case RTP_PRIO_FIFO:
		*policy = SCHED_FIFO;
		param->sched_priority = RTP_PRIO_MAX - rtp->prio;
		break;
	default:
		*policy = SCHED_OTHER;
		param->sched_priority = 0;
		break;
	}
	return (0);
}