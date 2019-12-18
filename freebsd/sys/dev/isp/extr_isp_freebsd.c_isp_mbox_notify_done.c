#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mboxcmd_done; scalar_t__ mbox_sleeping; } ;
struct TYPE_5__ {TYPE_1__ isp_osinfo; } ;
typedef  TYPE_2__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  wakeup (int*) ; 

void
isp_mbox_notify_done(ispsoftc_t *isp)
{
	isp->isp_osinfo.mboxcmd_done = 1;
	if (isp->isp_osinfo.mbox_sleeping)
		wakeup(&isp->isp_osinfo.mboxcmd_done);
}