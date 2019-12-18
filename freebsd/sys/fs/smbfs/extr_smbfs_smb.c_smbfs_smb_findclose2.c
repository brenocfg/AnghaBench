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
struct smbfs_fctx {int /*<<< orphan*/  f_Sid; int /*<<< orphan*/  f_scred; int /*<<< orphan*/  f_ssp; } ;
struct smb_rq {int dummy; } ;
struct mbchain {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int /*<<< orphan*/  SMB_COM_FIND_CLOSE2 ; 
 int /*<<< orphan*/  SSTOCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int smb_rq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_rq**) ; 
 int /*<<< orphan*/  smb_rq_bend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_bstart (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_getrequest (struct smb_rq*,struct mbchain**) ; 
 int smb_rq_simple (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wstart (struct smb_rq*) ; 

__attribute__((used)) static int
smbfs_smb_findclose2(struct smbfs_fctx *ctx)
{
	struct smb_rq *rqp;
	struct mbchain *mbp;
	int error;

	error = smb_rq_alloc(SSTOCP(ctx->f_ssp), SMB_COM_FIND_CLOSE2,
	    ctx->f_scred, &rqp);
	if (error)
		return (error);
	smb_rq_getrequest(rqp, &mbp);
	smb_rq_wstart(rqp);
	mb_put_mem(mbp, (caddr_t)&ctx->f_Sid, 2, MB_MSYSTEM);
	smb_rq_wend(rqp);
	smb_rq_bstart(rqp);
	smb_rq_bend(rqp);
	error = smb_rq_simple(rqp);
	smb_rq_done(rqp);
	return error;
}