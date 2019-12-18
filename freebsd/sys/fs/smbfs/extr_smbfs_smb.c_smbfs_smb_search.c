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
typedef  int u_int8_t ;
typedef  scalar_t__ u_int16_t ;
struct smbfs_fctx {int f_attrmask; int f_flags; scalar_t__ f_ecnt; int /*<<< orphan*/  f_skey; int /*<<< orphan*/  f_wclen; int /*<<< orphan*/  f_wildcard; int /*<<< orphan*/  f_dnp; struct smb_rq* f_rq; int /*<<< orphan*/  f_scred; int /*<<< orphan*/  f_ssp; int /*<<< orphan*/  f_left; } ;
struct smb_vc {int vc_txmax; } ;
struct smb_rq {scalar_t__ sr_errclass; scalar_t__ sr_serror; } ;
struct mdchain {int dummy; } ;
struct mbchain {int dummy; } ;

/* Variables and functions */
 int EBADRPC ; 
 int ENOENT ; 
 scalar_t__ ERRDOS ; 
 scalar_t__ ERRnofiles ; 
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int SMBFS_RDD_EOF ; 
 int SMBFS_RDD_FINDFIRST ; 
 int /*<<< orphan*/  SMB_COM_SEARCH ; 
 int SMB_DENTRYLEN ; 
 int SMB_DT_ASCII ; 
 int SMB_DT_VARIABLE ; 
 int SMB_HDRLEN ; 
 int SMB_SKEYLEN ; 
 scalar_t__ SMB_UNICODE_STRINGS (struct smb_vc*) ; 
 int /*<<< orphan*/  SSTOCP (int /*<<< orphan*/ ) ; 
 struct smb_vc* SSTOVC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_padbyte (struct mbchain*) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int) ; 
 int /*<<< orphan*/  mb_put_uint8 (struct mbchain*,int) ; 
 int /*<<< orphan*/  md_get_uint16le (struct mdchain*,scalar_t__*) ; 
 int /*<<< orphan*/  md_get_uint8 (struct mdchain*,int*) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int smb_rq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_rq**) ; 
 int /*<<< orphan*/  smb_rq_bend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_bstart (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_getreply (struct smb_rq*,struct mdchain**) ; 
 int /*<<< orphan*/  smb_rq_getrequest (struct smb_rq*,struct mbchain**) ; 
 int smb_rq_simple (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wstart (struct smb_rq*) ; 
 int smbfs_fullpath (struct mbchain*,struct smb_vc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smbfs_smb_search(struct smbfs_fctx *ctx)
{
	struct smb_vc *vcp = SSTOVC(ctx->f_ssp);
	struct smb_rq *rqp;
	struct mbchain *mbp;
	struct mdchain *mdp;
	u_int8_t wc, bt;
	u_int16_t ec, dlen, bc;
	int maxent, error, iseof = 0;

	maxent = min(ctx->f_left, (vcp->vc_txmax - SMB_HDRLEN - 3) / SMB_DENTRYLEN);
	if (ctx->f_rq) {
		smb_rq_done(ctx->f_rq);
		ctx->f_rq = NULL;
	}
	error = smb_rq_alloc(SSTOCP(ctx->f_ssp), SMB_COM_SEARCH, ctx->f_scred, &rqp);
	if (error)
		return (error);
	ctx->f_rq = rqp;
	smb_rq_getrequest(rqp, &mbp);
	smb_rq_wstart(rqp);
	mb_put_uint16le(mbp, maxent);	/* max entries to return */
	mb_put_uint16le(mbp, ctx->f_attrmask);
	smb_rq_wend(rqp);
	smb_rq_bstart(rqp);
	mb_put_uint8(mbp, SMB_DT_ASCII);	/* buffer format */
	if (ctx->f_flags & SMBFS_RDD_FINDFIRST) {
		error = smbfs_fullpath(mbp, vcp, ctx->f_dnp, ctx->f_wildcard, ctx->f_wclen);
		if (error)
			return error;
		mb_put_uint8(mbp, SMB_DT_VARIABLE);
		mb_put_uint16le(mbp, 0);	/* context length */
		ctx->f_flags &= ~SMBFS_RDD_FINDFIRST;
	} else {
		if (SMB_UNICODE_STRINGS(vcp)) {
			mb_put_padbyte(mbp);
			mb_put_uint8(mbp, 0);
		}
		mb_put_uint8(mbp, 0);	/* file name length */
		mb_put_uint8(mbp, SMB_DT_VARIABLE);
		mb_put_uint16le(mbp, SMB_SKEYLEN);
		mb_put_mem(mbp, ctx->f_skey, SMB_SKEYLEN, MB_MSYSTEM);
	}
	smb_rq_bend(rqp);
	error = smb_rq_simple(rqp);
	if (error) {
		if (rqp->sr_errclass == ERRDOS && rqp->sr_serror == ERRnofiles) {
			error = 0;
			iseof = 1;
			ctx->f_flags |= SMBFS_RDD_EOF;
		} else
			return error;
	}
	smb_rq_getreply(rqp, &mdp);
	md_get_uint8(mdp, &wc);
	if (wc != 1) 
		return iseof ? ENOENT : EBADRPC;
	md_get_uint16le(mdp, &ec);
	if (ec == 0)
		return ENOENT;
	ctx->f_ecnt = ec;
	md_get_uint16le(mdp, &bc);
	if (bc < 3)
		return EBADRPC;
	bc -= 3;
	md_get_uint8(mdp, &bt);
	if (bt != SMB_DT_VARIABLE)
		return EBADRPC;
	md_get_uint16le(mdp, &dlen);
	if (dlen != bc || dlen % SMB_DENTRYLEN != 0)
		return EBADRPC;
	return 0;
}