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
typedef  int u_int8_t ;
typedef  int u_int16_t ;
struct uio {int uio_resid; int /*<<< orphan*/  uio_offset; } ;
struct smb_share {int dummy; } ;
struct smb_rq {int dummy; } ;
struct smb_cred {int dummy; } ;
struct mdchain {int dummy; } ;
struct mbchain {int dummy; } ;
typedef  int /*<<< orphan*/  fid ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_3__ {int sv_caps; } ;
struct TYPE_4__ {int vc_txmax; TYPE_1__ vc_sopt; } ;

/* Variables and functions */
 int EBADRPC ; 
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int SMB_CAP_LARGE_WRITEX ; 
 int /*<<< orphan*/  SMB_COM_WRITE ; 
 int /*<<< orphan*/  SMB_DT_DATA ; 
 int SMB_HDRLEN ; 
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 TYPE_2__* SSTOVC (struct smb_share*) ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int) ; 
 int /*<<< orphan*/  mb_put_uint32le (struct mbchain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint8 (struct mbchain*,int /*<<< orphan*/ ) ; 
 int mb_put_uio (struct mbchain*,struct uio*,int) ; 
 int /*<<< orphan*/  md_get_uint16le (struct mdchain*,int*) ; 
 int /*<<< orphan*/  md_get_uint8 (struct mdchain*,int*) ; 
 int min (int,int) ; 
 int smb_rq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_cred*,struct smb_rq**) ; 
 int /*<<< orphan*/  smb_rq_bend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_bstart (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_getreply (struct smb_rq*,struct mdchain**) ; 
 int /*<<< orphan*/  smb_rq_getrequest (struct smb_rq*,struct mbchain**) ; 
 int smb_rq_simple (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wstart (struct smb_rq*) ; 
 int smb_smb_writex (struct smb_share*,int,int*,int*,struct uio*,struct smb_cred*) ; 

__attribute__((used)) static __inline int
smb_smb_write(struct smb_share *ssp, u_int16_t fid, int *len, int *rresid,
	struct uio *uio, struct smb_cred *scred)
{
	struct smb_rq *rqp;
	struct mbchain *mbp;
	struct mdchain *mdp;
	u_int16_t resid;
	u_int8_t wc;
	int error, blksz;

	if (*len && SSTOVC(ssp)->vc_sopt.sv_caps & SMB_CAP_LARGE_WRITEX)
		return (smb_smb_writex(ssp, fid, len, rresid, uio, scred));
 
	blksz = SSTOVC(ssp)->vc_txmax - SMB_HDRLEN - 16;
	if (blksz > 0xffff)
		blksz = 0xffff;

	resid = *len = min(blksz, *len);

	error = smb_rq_alloc(SSTOCP(ssp), SMB_COM_WRITE, scred, &rqp);
	if (error)
		return error;
	smb_rq_getrequest(rqp, &mbp);
	smb_rq_wstart(rqp);
	mb_put_mem(mbp, (caddr_t)&fid, sizeof(fid), MB_MSYSTEM);
	mb_put_uint16le(mbp, resid);
	mb_put_uint32le(mbp, uio->uio_offset);
	mb_put_uint16le(mbp, min(uio->uio_resid, 0xffff));
	smb_rq_wend(rqp);
	smb_rq_bstart(rqp);
	mb_put_uint8(mbp, SMB_DT_DATA);
	mb_put_uint16le(mbp, resid);
	do {
		error = mb_put_uio(mbp, uio, resid);
		if (error)
			break;
		smb_rq_bend(rqp);
		error = smb_rq_simple(rqp);
		if (error)
			break;
		smb_rq_getreply(rqp, &mdp);
		md_get_uint8(mdp, &wc);
		if (wc != 1) {
			error = EBADRPC;
			break;
		}
		md_get_uint16le(mdp, &resid);
		*rresid = resid;
	} while(0);
	smb_rq_done(rqp);
	return error;
}