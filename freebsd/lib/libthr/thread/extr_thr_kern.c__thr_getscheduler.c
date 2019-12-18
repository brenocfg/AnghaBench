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
struct sched_param {int dummy; } ;
struct rtprio {int dummy; } ;
typedef  int /*<<< orphan*/  lwpid_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTP_LOOKUP ; 
 int /*<<< orphan*/  _rtp_to_schedparam (struct rtprio*,int*,struct sched_param*) ; 
 int rtprio_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtprio*) ; 

int
_thr_getscheduler(lwpid_t lwpid, int *policy, struct sched_param *param)
{
	struct rtprio rtp;
	int ret;

	ret = rtprio_thread(RTP_LOOKUP, lwpid, &rtp);
	if (ret == -1)
		return (ret);
	_rtp_to_schedparam(&rtp, policy, param);
	return (0);
}