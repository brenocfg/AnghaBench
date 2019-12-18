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
struct smb_vcspec {int flags; struct smb_share* ssp; } ;
struct smb_vc {int dummy; } ;
struct smb_sharespec {int dummy; } ;
struct smb_share {int dummy; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int SMBV_CREATE ; 
 int smb_share_create (struct smb_vc*,struct smb_sharespec*,struct smb_cred*,struct smb_share**) ; 
 int /*<<< orphan*/  smb_share_put (struct smb_share*,struct smb_cred*) ; 
 int smb_sm_lockvclist () ; 
 int smb_sm_lookupint (struct smb_vcspec*,struct smb_sharespec*,struct smb_cred*,struct smb_vc**) ; 
 int /*<<< orphan*/  smb_sm_unlockvclist () ; 
 int smb_smb_treeconnect (struct smb_share*,struct smb_cred*) ; 
 int smb_vc_connect (struct smb_vc*,struct smb_cred*) ; 
 int smb_vc_create (struct smb_vcspec*,struct smb_cred*,struct smb_vc**) ; 
 int /*<<< orphan*/  smb_vc_lock (struct smb_vc*) ; 
 int /*<<< orphan*/  smb_vc_put (struct smb_vc*,struct smb_cred*) ; 

int
smb_sm_lookup(struct smb_vcspec *vcspec, struct smb_sharespec *shspec,
	struct smb_cred *scred,	struct smb_vc **vcpp)
{
	struct smb_vc *vcp;
	struct smb_share *ssp = NULL;
	int error;

	*vcpp = vcp = NULL;

	error = smb_sm_lockvclist();
	if (error)
		return error;
	error = smb_sm_lookupint(vcspec, shspec, scred, vcpp);
	if (error == 0 || (vcspec->flags & SMBV_CREATE) == 0) {
		smb_sm_unlockvclist();
		return error;
	}
	error = smb_sm_lookupint(vcspec, NULL, scred, &vcp);
	if (error) {
		error = smb_vc_create(vcspec, scred, &vcp);
		if (error)
			goto out;
		error = smb_vc_connect(vcp, scred);
		if (error)
			goto out;
	}
	if (shspec == NULL)
		goto out;
	error = smb_share_create(vcp, shspec, scred, &ssp);
	if (error)
		goto out;
	error = smb_smb_treeconnect(ssp, scred);
	if (error == 0)
		vcspec->ssp = ssp;
	else
		smb_share_put(ssp, scred);
out:
	smb_sm_unlockvclist();
	if (error == 0)
		*vcpp = vcp;
	else if (vcp) {
		smb_vc_lock(vcp);
		smb_vc_put(vcp, scred);
	}
	return error;
}