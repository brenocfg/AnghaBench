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
struct smbnode {int n_flag; int /*<<< orphan*/  n_fid; TYPE_1__* n_mount; } ;
struct smb_share {int dummy; } ;
struct smb_rq {int dummy; } ;
struct smb_cred {int dummy; } ;
struct mbchain {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {scalar_t__ v_type; } ;
struct TYPE_3__ {struct smb_share* sm_share; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int NFLUSHWIRE ; 
 int NOPEN ; 
 TYPE_2__* SMBTOV (struct smbnode*) ; 
 int /*<<< orphan*/  SMB_COM_FLUSH ; 
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int smb_rq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_cred*,struct smb_rq**) ; 
 int /*<<< orphan*/  smb_rq_bend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_bstart (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_getrequest (struct smb_rq*,struct mbchain**) ; 
 int smb_rq_simple (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wstart (struct smb_rq*) ; 

__attribute__((used)) static int
smb_smb_flush(struct smbnode *np, struct smb_cred *scred)
{
	struct smb_share *ssp = np->n_mount->sm_share;
	struct smb_rq *rqp;
	struct mbchain *mbp;
	int error;

	if ((np->n_flag & NOPEN) == 0 || !SMBTOV(np) ||
	    SMBTOV(np)->v_type != VREG)
		return 0; /* not a regular open file */
	error = smb_rq_alloc(SSTOCP(ssp), SMB_COM_FLUSH, scred, &rqp);
	if (error)
		return (error);
	smb_rq_getrequest(rqp, &mbp);
	smb_rq_wstart(rqp);
	mb_put_mem(mbp, (caddr_t)&np->n_fid, 2, MB_MSYSTEM);
	smb_rq_wend(rqp);
	smb_rq_bstart(rqp);
	smb_rq_bend(rqp);
	error = smb_rq_simple(rqp);
	smb_rq_done(rqp);
	if (!error)
		np->n_flag &= ~NFLUSHWIRE;
	return (error);
}