#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smb_share {int ss_flags; int /*<<< orphan*/  ss_vcgenid; } ;
struct smb_rq {TYPE_2__* sr_vc; TYPE_1__* sr_cred; struct smb_share* sr_share; } ;
struct TYPE_4__ {int /*<<< orphan*/  scr_td; } ;
struct TYPE_6__ {TYPE_1__ iod_scred; } ;
struct TYPE_5__ {TYPE_3__* vc_iod; } ;

/* Variables and functions */
 int EINTR ; 
 int EXDEV ; 
 int PDROP ; 
 int PWAIT ; 
 int SMBIOD_EV_SYNC ; 
 int SMBIOD_EV_TREECONNECT ; 
 int SMBS_CONNECTED ; 
 int SMBS_RECONNECTING ; 
 int /*<<< orphan*/  SMBS_ST_LOCK (struct smb_share*) ; 
 int /*<<< orphan*/  SMBS_ST_LOCKPTR (struct smb_share*) ; 
 int /*<<< orphan*/  SMBS_ST_UNLOCK (struct smb_share*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int smb_iod_addrq (struct smb_rq*) ; 
 int smb_iod_request (TYPE_3__*,int,struct smb_share*) ; 
 scalar_t__ smb_share_valid (struct smb_share*) ; 
 scalar_t__ smb_td_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb_rq_enqueue(struct smb_rq *rqp)
{
	struct smb_share *ssp = rqp->sr_share;
	int error;

	if (ssp == NULL || rqp->sr_cred == &rqp->sr_vc->vc_iod->iod_scred) {
		return smb_iod_addrq(rqp);
	}
	for (;;) {
		SMBS_ST_LOCK(ssp);
		if (ssp->ss_flags & SMBS_RECONNECTING) {
			msleep(&ssp->ss_vcgenid, SMBS_ST_LOCKPTR(ssp),
			    PWAIT | PDROP, "90trcn", hz);
			if (smb_td_intr(rqp->sr_cred->scr_td))
				return EINTR;
			continue;
		}
		if (smb_share_valid(ssp) || (ssp->ss_flags & SMBS_CONNECTED) == 0) {
			SMBS_ST_UNLOCK(ssp);
		} else {
			SMBS_ST_UNLOCK(ssp);
			error = smb_iod_request(rqp->sr_vc->vc_iod,
			    SMBIOD_EV_TREECONNECT | SMBIOD_EV_SYNC, ssp);
			if (error)
				return error;
		}
		error = smb_iod_addrq(rqp);
		if (error != EXDEV)
			break;
	}
	return error;
}