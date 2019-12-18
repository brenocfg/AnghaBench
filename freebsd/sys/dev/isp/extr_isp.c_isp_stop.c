#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* param; } ;
typedef  TYPE_1__ mbreg_t ;
struct TYPE_8__ {int /*<<< orphan*/  isp_state; } ;
typedef  TYPE_2__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_NILSTATE ; 
 int /*<<< orphan*/  MBLOGALL ; 
 scalar_t__ MBOX_COMMAND_COMPLETE ; 
 int /*<<< orphan*/  MBOX_STOP_FIRMWARE ; 
 int /*<<< orphan*/  MBSINIT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isp_mboxcmd (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int
isp_stop(ispsoftc_t *isp)
{
	mbreg_t mbs;

	isp->isp_state = ISP_NILSTATE;
	MBSINIT(&mbs, MBOX_STOP_FIRMWARE, MBLOGALL, 500000);
	mbs.param[1] = 0;
	mbs.param[2] = 0;
	mbs.param[3] = 0;
	mbs.param[4] = 0;
	mbs.param[5] = 0;
	mbs.param[6] = 0;
	mbs.param[7] = 0;
	mbs.param[8] = 0;
	isp_mboxcmd(isp, &mbs);
	return (mbs.param[0] == MBOX_COMMAND_COMPLETE ? 0 : mbs.param[0]);
}