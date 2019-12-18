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
struct smbioc_ossn {int ioc_opt; } ;
struct smb_vcspec {int /*<<< orphan*/  flags; } ;
struct smb_vc {int dummy; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int SMBVOPT_CREATE ; 
 int /*<<< orphan*/  SMBV_CREATE ; 
 int smb_sm_lookup (struct smb_vcspec*,int /*<<< orphan*/ *,struct smb_cred*,struct smb_vc**) ; 
 int smb_usr_vc2spec (struct smbioc_ossn*,struct smb_vcspec*) ; 
 int /*<<< orphan*/  smb_usr_vcspec_free (struct smb_vcspec*) ; 

int
smb_usr_opensession(struct smbioc_ossn *dp, struct smb_cred *scred,
	struct smb_vc **vcpp)
{
	struct smb_vc *vcp = NULL;
	struct smb_vcspec vspec;
	int error;

	error = smb_usr_vc2spec(dp, &vspec);
	if (error)
		return error;
	if (dp->ioc_opt & SMBVOPT_CREATE)
		vspec.flags |= SMBV_CREATE;

	error = smb_sm_lookup(&vspec, NULL, scred, &vcp);
	smb_usr_vcspec_free(&vspec);
	return error;
}