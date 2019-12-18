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
typedef  int u_int8_t ;
typedef  int u_int16_t ;
struct uio {int uio_offset; } ;
struct smb_share {int dummy; } ;
struct smb_rq {int dummy; } ;
struct smb_cred {int dummy; } ;
struct mdchain {int dummy; } ;
struct mbchain {int dummy; } ;
typedef  int /*<<< orphan*/  fid ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  vc_wxmax; } ;

/* Variables and functions */
 int EBADRPC ; 
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int /*<<< orphan*/  SMB_COM_WRITE_ANDX ; 
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 TYPE_1__* SSTOVC (struct smb_share*) ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int) ; 
 int /*<<< orphan*/  mb_put_uint32le (struct mbchain*,int) ; 
 int /*<<< orphan*/  mb_put_uint8 (struct mbchain*,int) ; 
 int mb_put_uio (struct mbchain*,struct uio*,int) ; 
 int /*<<< orphan*/  md_get_uint16le (struct mdchain*,int*) ; 
 int /*<<< orphan*/  md_get_uint8 (struct mdchain*,int*) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int smb_rq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_cred*,struct smb_rq**) ; 
 int /*<<< orphan*/  smb_rq_bend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_bstart (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_getreply (struct smb_rq*,struct mdchain**) ; 
 int /*<<< orphan*/  smb_rq_getrequest (struct smb_rq*,struct mbchain**) ; 
 int smb_rq_simple (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wstart (struct smb_rq*) ; 

__attribute__((used)) static __inline int
smb_smb_writex(struct smb_share *ssp, u_int16_t fid, int *len, int *rresid,
	struct uio *uio, struct smb_cred *scred)
{
	struct smb_rq *rqp;
	struct mbchain *mbp;
	struct mdchain *mdp;
	int error;
	u_int8_t wc;
	u_int16_t resid;

	error = smb_rq_alloc(SSTOCP(ssp), SMB_COM_WRITE_ANDX, scred, &rqp);
	if (error)
		return (error);
	smb_rq_getrequest(rqp, &mbp);
	smb_rq_wstart(rqp);
	mb_put_uint8(mbp, 0xff);	/* no secondary command */
	mb_put_uint8(mbp, 0);		/* MBZ */
	mb_put_uint16le(mbp, 0);	/* offset to secondary */
	mb_put_mem(mbp, (caddr_t)&fid, sizeof(fid), MB_MSYSTEM);
	mb_put_uint32le(mbp, uio->uio_offset);
	mb_put_uint32le(mbp, 0);	/* MBZ (timeout) */
	mb_put_uint16le(mbp, 0);	/* !write-thru */
	mb_put_uint16le(mbp, 0);
	*len = min(SSTOVC(ssp)->vc_wxmax, *len);
	mb_put_uint16le(mbp, (unsigned)*len >> 16);
	mb_put_uint16le(mbp, *len);
	mb_put_uint16le(mbp, 64);	/* data offset from header start */
	mb_put_uint32le(mbp, uio->uio_offset >> 32);	/* OffsetHigh */
	smb_rq_wend(rqp);
	smb_rq_bstart(rqp);
	do {
		mb_put_uint8(mbp, 0xee);	/* mimic xp pad byte! */
		error = mb_put_uio(mbp, uio, *len);
		if (error)
			break;
		smb_rq_bend(rqp);
		error = smb_rq_simple(rqp);
		if (error)
			break;
		smb_rq_getreply(rqp, &mdp);
		md_get_uint8(mdp, &wc);
		if (wc != 6) {
			error = EBADRPC;
			break;
		}
		md_get_uint8(mdp, NULL);
		md_get_uint8(mdp, NULL);
		md_get_uint16le(mdp, NULL);
		md_get_uint16le(mdp, &resid);
		*rresid = resid;
	} while(0);

	smb_rq_done(rqp);
	return (error);
}