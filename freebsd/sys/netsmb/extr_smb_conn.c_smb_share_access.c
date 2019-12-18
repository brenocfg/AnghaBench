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
struct ucred {scalar_t__ cr_uid; } ;
struct smb_share {scalar_t__ ss_uid; int ss_mode; int /*<<< orphan*/  ss_grp; } ;
struct smb_cred {struct ucred* scr_cred; } ;
typedef  int mode_t ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  groupmember (int /*<<< orphan*/ ,struct ucred*) ; 
 scalar_t__ smb_suser (struct ucred*) ; 

int
smb_share_access(struct smb_share *ssp, struct smb_cred *scred, mode_t mode)
{
	struct ucred *cred = scred->scr_cred;

	if (smb_suser(cred) == 0 || cred->cr_uid == ssp->ss_uid)
		return 0;
	mode >>= 3;
	if (!groupmember(ssp->ss_grp, cred))
		mode >>= 3;
	return (ssp->ss_mode & mode) == mode ? 0 : EACCES;
}