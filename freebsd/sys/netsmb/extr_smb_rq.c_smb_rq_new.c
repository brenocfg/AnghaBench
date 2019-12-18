#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct smb_vc {int vc_hflags2; int /*<<< orphan*/  vc_hflags; } ;
struct mbchain {int dummy; } ;
struct smb_rq {int sr_mid; void* sr_rquid; void* sr_rqtid; int /*<<< orphan*/ * sr_rqsig; int /*<<< orphan*/  sr_rp; scalar_t__ sr_sendcnt; struct mbchain sr_rq; struct smb_vc* sr_vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int /*<<< orphan*/  SMB_COM_NEGOTIATE ; 
 int /*<<< orphan*/  SMB_COM_TRANSACTION ; 
 int /*<<< orphan*/  SMB_COM_TRANSACTION_SECONDARY ; 
 int SMB_FLAGS2_SECURITY_SIGNATURE ; 
 int SMB_FLAGS2_UNICODE ; 
 int SMB_SIGLEN ; 
 int /*<<< orphan*/  SMB_SIGNATURE ; 
 int /*<<< orphan*/  mb_done (struct mbchain*) ; 
 int mb_init (struct mbchain*) ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int) ; 
 int /*<<< orphan*/  mb_put_uint32le (struct mbchain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint8 (struct mbchain*,int /*<<< orphan*/ ) ; 
 void* mb_reserve (struct mbchain*,int) ; 
 int /*<<< orphan*/  md_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tzero ; 

__attribute__((used)) static int
smb_rq_new(struct smb_rq *rqp, u_char cmd)
{
	struct smb_vc *vcp = rqp->sr_vc;
	struct mbchain *mbp = &rqp->sr_rq;
	int error;
	u_int16_t flags2;

	rqp->sr_sendcnt = 0;
	mb_done(mbp);
	md_done(&rqp->sr_rp);
	error = mb_init(mbp);
	if (error)
		return error;
	mb_put_mem(mbp, SMB_SIGNATURE, SMB_SIGLEN, MB_MSYSTEM);
	mb_put_uint8(mbp, cmd);
	mb_put_uint32le(mbp, 0);		/* DosError */
	mb_put_uint8(mbp, vcp->vc_hflags);
	flags2 = vcp->vc_hflags2;
	if (cmd == SMB_COM_TRANSACTION || cmd == SMB_COM_TRANSACTION_SECONDARY)
		flags2 &= ~SMB_FLAGS2_UNICODE;
	if (cmd == SMB_COM_NEGOTIATE)
		flags2 &= ~SMB_FLAGS2_SECURITY_SIGNATURE;
	mb_put_uint16le(mbp, flags2);
	if ((flags2 & SMB_FLAGS2_SECURITY_SIGNATURE) == 0) {
		mb_put_mem(mbp, tzero, 12, MB_MSYSTEM);
		rqp->sr_rqsig = NULL;
	} else {
		mb_put_uint16le(mbp, 0 /*scred->sc_p->p_pid >> 16*/);
		rqp->sr_rqsig = (u_int8_t *)mb_reserve(mbp, 8);
		mb_put_uint16le(mbp, 0);
	}
	rqp->sr_rqtid = mb_reserve(mbp, sizeof(u_int16_t));
	mb_put_uint16le(mbp, 1 /*scred->sc_p->p_pid & 0xffff*/);
	rqp->sr_rquid = mb_reserve(mbp, sizeof(u_int16_t));
	mb_put_uint16le(mbp, rqp->sr_mid);
	return 0;
}