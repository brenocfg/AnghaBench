#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smbiod {scalar_t__ iod_p; int iod_state; scalar_t__ iod_muxcnt; int /*<<< orphan*/  iod_rqlist; int /*<<< orphan*/  iod_muxwant; int /*<<< orphan*/  iod_flags; } ;
struct smb_vc {scalar_t__ vc_maxmux; struct smbiod* vc_iod; } ;
struct smb_rq {scalar_t__ sr_state; int sr_lerror; int /*<<< orphan*/  sr_flags; TYPE_2__* sr_cred; struct smb_vc* sr_vc; } ;
struct TYPE_4__ {TYPE_1__* scr_td; } ;
struct TYPE_3__ {scalar_t__ td_proc; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int EXDEV ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  SMBERROR (char*) ; 
 int /*<<< orphan*/  SMBIODEBUG (char*) ; 
 int SMBIOD_EV_CONNECT ; 
 int SMBIOD_EV_SYNC ; 
#define  SMBIOD_ST_DEAD 129 
#define  SMBIOD_ST_NOTCONN 128 
 scalar_t__ SMBRQ_NOTSENT ; 
 int /*<<< orphan*/  SMBR_INTERNAL ; 
 int /*<<< orphan*/  SMB_IOD_RQLOCK (struct smbiod*) ; 
 int /*<<< orphan*/  SMB_IOD_RQLOCKPTR (struct smbiod*) ; 
 int /*<<< orphan*/  SMB_IOD_RQUNLOCK (struct smbiod*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct smb_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct smb_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_iod_dead (struct smbiod*) ; 
 int /*<<< orphan*/  smb_iod_removerq (struct smb_rq*) ; 
 int smb_iod_request (struct smbiod*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ smb_iod_sendrq (struct smbiod*,struct smb_rq*) ; 
 int /*<<< orphan*/  smb_iod_wakeup (struct smbiod*) ; 
 int /*<<< orphan*/  sr_link ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
smb_iod_addrq(struct smb_rq *rqp)
{
	struct smb_vc *vcp = rqp->sr_vc;
	struct smbiod *iod = vcp->vc_iod;
	int error;

	SMBIODEBUG("\n");
	if (rqp->sr_cred->scr_td != NULL &&
	    rqp->sr_cred->scr_td->td_proc == iod->iod_p) {
		rqp->sr_flags |= SMBR_INTERNAL;
		SMB_IOD_RQLOCK(iod);
		TAILQ_INSERT_HEAD(&iod->iod_rqlist, rqp, sr_link);
		SMB_IOD_RQUNLOCK(iod);
		for (;;) {
			if (smb_iod_sendrq(iod, rqp) != 0) {
				smb_iod_dead(iod);
				break;
			}
			/*
			 * we don't need to lock state field here
			 */
			if (rqp->sr_state != SMBRQ_NOTSENT)
				break;
			tsleep(&iod->iod_flags, PWAIT, "90sndw", hz);
		}
		if (rqp->sr_lerror)
			smb_iod_removerq(rqp);
		return rqp->sr_lerror;
	}

	switch (iod->iod_state) {
	    case SMBIOD_ST_NOTCONN:
		return ENOTCONN;
	    case SMBIOD_ST_DEAD:
		error = smb_iod_request(vcp->vc_iod, SMBIOD_EV_CONNECT | SMBIOD_EV_SYNC, NULL);
		if (error)
			return error;
		return EXDEV;
	    default:
		break;
	}

	SMB_IOD_RQLOCK(iod);
	for (;;) {
		if (vcp->vc_maxmux == 0) {
			SMBERROR("maxmux == 0\n");
			break;
		}
		if (iod->iod_muxcnt < vcp->vc_maxmux)
			break;
		iod->iod_muxwant++;
		msleep(&iod->iod_muxwant, SMB_IOD_RQLOCKPTR(iod),
		    PWAIT, "90mux", 0);
	}
	iod->iod_muxcnt++;
	TAILQ_INSERT_TAIL(&iod->iod_rqlist, rqp, sr_link);
	SMB_IOD_RQUNLOCK(iod);
	smb_iod_wakeup(iod);
	return 0;
}