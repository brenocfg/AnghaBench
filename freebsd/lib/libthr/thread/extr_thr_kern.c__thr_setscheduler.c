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
 int /*<<< orphan*/  RTP_SET ; 
 int /*<<< orphan*/  _schedparam_to_rtp (int,struct sched_param const*,struct rtprio*) ; 
 int rtprio_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtprio*) ; 

int
_thr_setscheduler(lwpid_t lwpid, int policy, const struct sched_param *param)
{
	struct rtprio rtp;

	_schedparam_to_rtp(policy, param, &rtp);
	return (rtprio_thread(RTP_SET, lwpid, &rtp));
}