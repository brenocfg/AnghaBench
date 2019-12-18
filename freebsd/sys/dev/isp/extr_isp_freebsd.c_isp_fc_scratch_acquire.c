#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* fc; } ;
struct TYPE_8__ {TYPE_2__ pc; } ;
struct TYPE_9__ {TYPE_3__ isp_osinfo; } ;
typedef  TYPE_4__ ispsoftc_t ;
struct TYPE_6__ {int fcbsy; } ;

/* Variables and functions */

int
isp_fc_scratch_acquire(ispsoftc_t *isp, int chan)
{
	int ret = 0;
	if (isp->isp_osinfo.pc.fc[chan].fcbsy) {
		ret = -1;
	} else {
		isp->isp_osinfo.pc.fc[chan].fcbsy = 1;
	}
	return (ret);
}