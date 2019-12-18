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
struct rtprio {int type; } ;
struct ksched {int dummy; } ;

/* Variables and functions */
#define  RTP_PRIO_FIFO 129 
#define  RTP_PRIO_REALTIME 128 
 int SCHED_FIFO ; 
 int SCHED_OTHER ; 
 int SCHED_RR ; 
 int /*<<< orphan*/  pri_to_rtp (struct thread*,struct rtprio*) ; 

__attribute__((used)) static __inline int
getscheduler(struct ksched *ksched, struct thread *td, int *policy)
{
	struct rtprio rtp;
	int e;

	e = 0;
	pri_to_rtp(td, &rtp);
	switch (rtp.type) {
	case RTP_PRIO_FIFO:
		*policy = SCHED_FIFO;
		break;
	case RTP_PRIO_REALTIME:
		*policy = SCHED_RR;
		break;
	default:
		*policy = SCHED_OTHER;
		break;
	}
	return (e);
}