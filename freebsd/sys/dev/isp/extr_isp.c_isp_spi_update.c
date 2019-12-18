#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_8__ {int update; int sendmarker; TYPE_1__* isp_devparam; } ;
typedef  TYPE_2__ sdparam ;
struct TYPE_9__ {int* param; } ;
typedef  TYPE_3__ mbreg_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_7__ {scalar_t__ dev_enable; int dev_refresh; int goal_flags; int goal_offset; int goal_period; int actv_flags; scalar_t__ dev_update; void* actv_offset; void* actv_period; } ;

/* Variables and functions */
 int DPARM_PARITY ; 
 int DPARM_QFRZ ; 
 int DPARM_RENEG ; 
 int DPARM_SYNC ; 
 int DPARM_TQING ; 
 int DPARM_WIDE ; 
 int /*<<< orphan*/  ISPASYNC_NEW_TGT_PARAMS ; 
 int /*<<< orphan*/  ISP_LOGDEBUG0 ; 
 scalar_t__ IS_FC (int /*<<< orphan*/ *) ; 
 int MAX_TARGETS ; 
 int /*<<< orphan*/  MBLOGALL ; 
 int MBOX_COMMAND_COMPLETE ; 
 int MBOX_GET_TARGET_PARAMS ; 
 int MBOX_SET_TARGET_PARAMS ; 
 int /*<<< orphan*/  MBSINIT (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* SDPARAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isp_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  isp_mboxcmd (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,...) ; 

__attribute__((used)) static void
isp_spi_update(ispsoftc_t *isp, int chan)
{
	int tgt;
	mbreg_t mbs;
	sdparam *sdp;

	if (IS_FC(isp)) {
		/*
		 * There are no 'per-bus' settings for Fibre Channel.
		 */
		return;
	}
	sdp = SDPARAM(isp, chan);
	sdp->update = 0;

	for (tgt = 0; tgt < MAX_TARGETS; tgt++) {
		uint16_t flags, period, offset;
		int get;

		if (sdp->isp_devparam[tgt].dev_enable == 0) {
			sdp->isp_devparam[tgt].dev_update = 0;
			sdp->isp_devparam[tgt].dev_refresh = 0;
			isp_prt(isp, ISP_LOGDEBUG0, "skipping target %d bus %d update", tgt, chan);
			continue;
		}
		/*
		 * If the goal is to update the status of the device,
		 * take what's in goal_flags and try and set the device
		 * toward that. Otherwise, if we're just refreshing the
		 * current device state, get the current parameters.
		 */

		MBSINIT(&mbs, 0, MBLOGALL, 0);

		/*
		 * Refresh overrides set
		 */
		if (sdp->isp_devparam[tgt].dev_refresh) {
			mbs.param[0] = MBOX_GET_TARGET_PARAMS;
			get = 1;
		} else if (sdp->isp_devparam[tgt].dev_update) {
			mbs.param[0] = MBOX_SET_TARGET_PARAMS;

			/*
			 * Make sure goal_flags has "Renegotiate on Error"
			 * on and "Freeze Queue on Error" off.
			 */
			sdp->isp_devparam[tgt].goal_flags |= DPARM_RENEG;
			sdp->isp_devparam[tgt].goal_flags &= ~DPARM_QFRZ;
			mbs.param[2] = sdp->isp_devparam[tgt].goal_flags;

			/*
			 * Insist that PARITY must be enabled
			 * if SYNC or WIDE is enabled.
			 */
			if ((mbs.param[2] & (DPARM_SYNC|DPARM_WIDE)) != 0) {
				mbs.param[2] |= DPARM_PARITY;
			}

			if (mbs.param[2] & DPARM_SYNC) {
				mbs.param[3] =
				    (sdp->isp_devparam[tgt].goal_offset << 8) |
				    (sdp->isp_devparam[tgt].goal_period);
			}
			/*
			 * A command completion later that has
			 * RQSTF_NEGOTIATION set can cause
			 * the dev_refresh/announce cycle also.
			 *
			 * Note: It is really important to update our current
			 * flags with at least the state of TAG capabilities-
			 * otherwise we might try and send a tagged command
			 * when we have it all turned off. So change it here
			 * to say that current already matches goal.
			 */
			sdp->isp_devparam[tgt].actv_flags &= ~DPARM_TQING;
			sdp->isp_devparam[tgt].actv_flags |=
			    (sdp->isp_devparam[tgt].goal_flags & DPARM_TQING);
			isp_prt(isp, ISP_LOGDEBUG0, "bus %d set tgt %d flags 0x%x off 0x%x period 0x%x",
			    chan, tgt, mbs.param[2], mbs.param[3] >> 8, mbs.param[3] & 0xff);
			get = 0;
		} else {
			continue;
		}
		mbs.param[1] = (chan << 15) | (tgt << 8);
		isp_mboxcmd(isp, &mbs);
		if (mbs.param[0] != MBOX_COMMAND_COMPLETE) {
			continue;
		}
		if (get == 0) {
			sdp->sendmarker = 1;
			sdp->isp_devparam[tgt].dev_update = 0;
			sdp->isp_devparam[tgt].dev_refresh = 1;
		} else {
			sdp->isp_devparam[tgt].dev_refresh = 0;
			flags = mbs.param[2];
			period = mbs.param[3] & 0xff;
			offset = mbs.param[3] >> 8;
			sdp->isp_devparam[tgt].actv_flags = flags;
			sdp->isp_devparam[tgt].actv_period = period;
			sdp->isp_devparam[tgt].actv_offset = offset;
			isp_async(isp, ISPASYNC_NEW_TGT_PARAMS, chan, tgt);
		}
	}

	for (tgt = 0; tgt < MAX_TARGETS; tgt++) {
		if (sdp->isp_devparam[tgt].dev_update ||
		    sdp->isp_devparam[tgt].dev_refresh) {
			sdp->update = 1;
			break;
		}
	}
}