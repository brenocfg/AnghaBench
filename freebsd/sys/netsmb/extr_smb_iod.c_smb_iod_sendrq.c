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
struct thread {int dummy; } ;
struct smbiod {int iod_state; scalar_t__ iod_muxcnt; int /*<<< orphan*/  iod_lastrqsent; struct smb_vc* iod_vc; struct thread* iod_td; } ;
struct smb_vc {scalar_t__ vc_maxmux; int vc_hflags2; int /*<<< orphan*/  vc_smbuid; } ;
struct smb_share {int /*<<< orphan*/  ss_tid; } ;
struct TYPE_2__ {int /*<<< orphan*/  mb_top; } ;
struct smb_rq {scalar_t__ sr_sendcnt; int sr_lerror; int /*<<< orphan*/  sr_state; int /*<<< orphan*/  sr_flags; int /*<<< orphan*/  sr_timesent; TYPE_1__ sr_rq; int /*<<< orphan*/  sr_mid; int /*<<< orphan*/  sr_rquid; int /*<<< orphan*/  sr_rqtid; struct smb_share* sr_share; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  M_COPYALL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SMBIODEBUG (char*,int) ; 
#define  SMBIOD_ST_DEAD 130 
#define  SMBIOD_ST_NOTCONN 129 
#define  SMBIOD_ST_RECONNECT 128 
 int /*<<< orphan*/  SMBRQ_SENT ; 
 int /*<<< orphan*/  SMBR_RESTART ; 
 int /*<<< orphan*/  SMBR_SENT ; 
 int /*<<< orphan*/  SMBSDEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SMB_FLAGS2_SECURITY_SIGNATURE ; 
 int /*<<< orphan*/  SMB_TID_UNKNOWN ; 
 scalar_t__ SMB_TRAN_FATAL (struct smb_vc*,int) ; 
 int SMB_TRAN_SEND (struct smb_vc*,struct mbuf*,struct thread*) ; 
 int /*<<< orphan*/  getnanotime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16enc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* m_copym (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_dumpm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_fixhdr (TYPE_1__*) ; 
 int /*<<< orphan*/  smb_iod_rqprocessed (struct smb_rq*,int) ; 
 scalar_t__ smb_rq_intr (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_sign (struct smb_rq*) ; 

__attribute__((used)) static int
smb_iod_sendrq(struct smbiod *iod, struct smb_rq *rqp)
{
	struct thread *td = iod->iod_td;
	struct smb_vc *vcp = iod->iod_vc;
	struct smb_share *ssp = rqp->sr_share;
	struct mbuf *m;
	int error;

	SMBIODEBUG("iod_state = %d\n", iod->iod_state);
	switch (iod->iod_state) {
	    case SMBIOD_ST_NOTCONN:
		smb_iod_rqprocessed(rqp, ENOTCONN);
		return 0;
	    case SMBIOD_ST_DEAD:
		iod->iod_state = SMBIOD_ST_RECONNECT;
		return 0;
	    case SMBIOD_ST_RECONNECT:
		return 0;
	    default:
		break;
	}
	if (rqp->sr_sendcnt == 0) {
#ifdef movedtoanotherplace
		if (vcp->vc_maxmux != 0 && iod->iod_muxcnt >= vcp->vc_maxmux)
			return 0;
#endif
		le16enc(rqp->sr_rqtid, ssp ? ssp->ss_tid : SMB_TID_UNKNOWN);
		le16enc(rqp->sr_rquid, vcp ? vcp->vc_smbuid : 0);
		mb_fixhdr(&rqp->sr_rq);
		if (vcp->vc_hflags2 & SMB_FLAGS2_SECURITY_SIGNATURE)
			smb_rq_sign(rqp);
	}
	if (rqp->sr_sendcnt++ > 5) {
		rqp->sr_flags |= SMBR_RESTART;
		smb_iod_rqprocessed(rqp, rqp->sr_lerror);
		/*
		 * If all attempts to send a request failed, then
		 * something is seriously hosed.
		 */
		return ENOTCONN;
	}
	SMBSDEBUG("M:%04x, P:%04x, U:%04x, T:%04x\n", rqp->sr_mid, 0, 0, 0);
	m_dumpm(rqp->sr_rq.mb_top);
	m = m_copym(rqp->sr_rq.mb_top, 0, M_COPYALL, M_WAITOK);
	error = rqp->sr_lerror = SMB_TRAN_SEND(vcp, m, td);
	if (error == 0) {
		getnanotime(&rqp->sr_timesent);
		iod->iod_lastrqsent = rqp->sr_timesent;
		rqp->sr_flags |= SMBR_SENT;
		rqp->sr_state = SMBRQ_SENT;
		return 0;
	}
	/*
	 * Check for fatal errors
	 */
	if (SMB_TRAN_FATAL(vcp, error)) {
		/*
		 * No further attempts should be made
		 */
		return ENOTCONN;
	}
	if (smb_rq_intr(rqp))
		smb_iod_rqprocessed(rqp, EINTR);
	return 0;
}