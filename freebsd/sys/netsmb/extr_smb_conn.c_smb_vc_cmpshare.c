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
struct smb_sharespec {scalar_t__ owner; scalar_t__ group; int mode; int /*<<< orphan*/  scred; int /*<<< orphan*/  name; } ;
struct smb_share {scalar_t__ ss_uid; scalar_t__ ss_grp; int ss_mode; int /*<<< orphan*/  ss_name; } ;

/* Variables and functions */
 scalar_t__ SMBM_ANY_GROUP ; 
 scalar_t__ SMBM_ANY_OWNER ; 
 int SMBM_EXACT ; 
 int SMBM_MASK ; 
 scalar_t__ smb_share_access (struct smb_share*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb_vc_cmpshare(struct smb_share *ssp, struct smb_sharespec *dp)
{
	int exact = 1;

	if (strcmp(ssp->ss_name, dp->name) != 0)
		return 1;
	if (dp->owner != SMBM_ANY_OWNER) {
		if (ssp->ss_uid != dp->owner)
			return 1;
	} else
		exact = 0;
	if (dp->group != SMBM_ANY_GROUP) {
		if (ssp->ss_grp != dp->group)
			return 1;
	} else
		exact = 0;

	if (dp->mode & SMBM_EXACT) {
		if (!exact)
			return 1;
		return (dp->mode & SMBM_MASK) == ssp->ss_mode ? 0 : 1;
	}
	if (smb_share_access(ssp, dp->scred, dp->mode) != 0)
		return 1;
	return 0;
}