#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_7__ {int /*<<< orphan*/ * tc_poll_pps; } ;
struct TYPE_5__ {int mode; } ;
struct TYPE_6__ {TYPE_1__ ppsparam; } ;

/* Variables and functions */
 int ENOIOCTL ; 
 int PPS_CAPTUREASSERT ; 
 int /*<<< orphan*/ * elan_poll_pps ; 
 TYPE_2__ elan_pps ; 
 TYPE_3__ elan_timecounter ; 
 scalar_t__ pps_a ; 
 int pps_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
elan_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int flag, struct  thread *tdr)
{
	int error;

	error = ENOIOCTL;

#ifdef CPU_ELAN_PPS
	if (pps_a != 0)
		error = pps_ioctl(cmd, arg, &elan_pps);
	/*
	 * We only want to incur the overhead of the PPS polling if we
	 * are actually asked to timestamp.
	 */
	if (elan_pps.ppsparam.mode & PPS_CAPTUREASSERT) {
		elan_timecounter.tc_poll_pps = elan_poll_pps;
	} else {
		elan_timecounter.tc_poll_pps = NULL;
	}
	if (error != ENOIOCTL)
		return (error);
#endif

	return(error);
}