#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smbiod {int /*<<< orphan*/  iod_rqlist; int /*<<< orphan*/  iod_flags; } ;
struct smb_rq {int sr_flags; scalar_t__ sr_rpgen; scalar_t__ sr_rplast; int sr_lerror; int /*<<< orphan*/  sr_state; TYPE_1__* sr_vc; } ;
struct TYPE_2__ {struct smbiod* vc_iod; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  SMBIODEBUG (char*) ; 
 int /*<<< orphan*/  SMBRQ_SLOCK (struct smb_rq*) ; 
 int /*<<< orphan*/  SMBRQ_SLOCKPTR (struct smb_rq*) ; 
 int /*<<< orphan*/  SMBRQ_SUNLOCK (struct smb_rq*) ; 
 int SMBR_INTERNAL ; 
 int SMBR_MULTIPACKET ; 
 int /*<<< orphan*/  SMB_IOD_RQLOCK (struct smbiod*) ; 
 int /*<<< orphan*/  SMB_IOD_RQUNLOCK (struct smbiod*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct smb_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct smb_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_iod_recvall (struct smbiod*) ; 
 int /*<<< orphan*/  smb_iod_removerq (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_iod_sendall (struct smbiod*) ; 
 int /*<<< orphan*/  sr_link ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
smb_iod_waitrq(struct smb_rq *rqp)
{
	struct smbiod *iod = rqp->sr_vc->vc_iod;
	int error;

	SMBIODEBUG("\n");
	if (rqp->sr_flags & SMBR_INTERNAL) {
		for (;;) {
			smb_iod_sendall(iod);
			smb_iod_recvall(iod);
			if (rqp->sr_rpgen != rqp->sr_rplast)
				break;
			tsleep(&iod->iod_flags, PWAIT, "90irq", hz);
		}
		smb_iod_removerq(rqp);
		return rqp->sr_lerror;

	}
	SMBRQ_SLOCK(rqp);
	if (rqp->sr_rpgen == rqp->sr_rplast)
		msleep(&rqp->sr_state, SMBRQ_SLOCKPTR(rqp), PWAIT, "90wrq", 0);
	rqp->sr_rplast++;
	SMBRQ_SUNLOCK(rqp);
	error = rqp->sr_lerror;
	if (rqp->sr_flags & SMBR_MULTIPACKET) {
		/*
		 * If request should stay in the list, then reinsert it
		 * at the end of queue so other waiters have chance to concur
		 */
		SMB_IOD_RQLOCK(iod);
		TAILQ_REMOVE(&iod->iod_rqlist, rqp, sr_link);
		TAILQ_INSERT_TAIL(&iod->iod_rqlist, rqp, sr_link);
		SMB_IOD_RQUNLOCK(iod);
	} else
		smb_iod_removerq(rqp);
	return error;
}