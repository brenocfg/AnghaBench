#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tmo; } ;
struct TYPE_6__ {TYPE_1__ isp_osinfo; } ;
typedef  TYPE_2__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_2__*) ; 
 int /*<<< orphan*/  isp_timer_count ; 
 int /*<<< orphan*/  isp_tmcmd_restart (TYPE_2__*) ; 

void
isp_timer(void *arg)
{
	ispsoftc_t *isp = arg;
#ifdef	ISP_TARGET_MODE
	isp_tmcmd_restart(isp);
#endif
	callout_reset(&isp->isp_osinfo.tmo, isp_timer_count, isp_timer, isp);
}