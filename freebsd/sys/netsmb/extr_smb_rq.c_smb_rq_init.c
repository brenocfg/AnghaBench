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
typedef  int /*<<< orphan*/  u_char ;
struct smb_rq {int /*<<< orphan*/  sr_vc; int /*<<< orphan*/  sr_mid; struct smb_cred* sr_cred; scalar_t__ sr_share; int /*<<< orphan*/  sr_slock; } ;
struct smb_cred {int dummy; } ;
struct smb_connobj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBM_EXEC ; 
 int /*<<< orphan*/  bzero (struct smb_rq*,int) ; 
 int smb_rq_getenv (struct smb_connobj*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int smb_rq_new (struct smb_rq*,int /*<<< orphan*/ ) ; 
 int smb_share_access (scalar_t__,struct smb_cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_sl_init (int /*<<< orphan*/ *,char*) ; 
 int smb_vc_access (int /*<<< orphan*/ ,struct smb_cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_vc_nextmid (int /*<<< orphan*/ ) ; 

int
smb_rq_init(struct smb_rq *rqp, struct smb_connobj *layer, u_char cmd,
	struct smb_cred *scred)
{
	int error;

	bzero(rqp, sizeof(*rqp));
	smb_sl_init(&rqp->sr_slock, "srslock");
	error = smb_rq_getenv(layer, &rqp->sr_vc, &rqp->sr_share);
	if (error)
		return error;
	error = smb_vc_access(rqp->sr_vc, scred, SMBM_EXEC);
	if (error)
		return error;
	if (rqp->sr_share) {
		error = smb_share_access(rqp->sr_share, scred, SMBM_EXEC);
		if (error)
			return error;
	}
	rqp->sr_cred = scred;
	rqp->sr_mid = smb_vc_nextmid(rqp->sr_vc);
	return smb_rq_new(rqp, cmd);
}