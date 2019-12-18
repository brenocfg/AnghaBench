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
struct statfs {int dummy; } ;
struct smb_share {int dummy; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 scalar_t__ SMB_DIALECT (int /*<<< orphan*/ ) ; 
 scalar_t__ SMB_DIALECT_LANMAN2_0 ; 
 int /*<<< orphan*/  SSTOVC (struct smb_share*) ; 
 scalar_t__ smbfs_query_info_alloc (struct smb_share*,struct statfs*,struct smb_cred*) ; 
 int smbfs_query_info_disk (struct smb_share*,struct statfs*,struct smb_cred*) ; 
 scalar_t__ smbfs_query_info_fs (struct smb_share*,struct statfs*,struct smb_cred*) ; 

int
smbfs_smb_statfs(struct smb_share *ssp, struct statfs *sbp,
	struct smb_cred *scred)
{

	if (SMB_DIALECT(SSTOVC(ssp)) >= SMB_DIALECT_LANMAN2_0) {
		if (smbfs_query_info_fs(ssp, sbp, scred) == 0)
			return (0);
		if (smbfs_query_info_alloc(ssp, sbp, scred) == 0)
			return (0);
	}
	return (smbfs_query_info_disk(ssp, sbp, scred));
}