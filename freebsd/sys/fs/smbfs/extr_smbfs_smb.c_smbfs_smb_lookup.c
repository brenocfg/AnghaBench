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
struct smbnode {int n_ino; int /*<<< orphan*/  n_vnode; } ;
struct smbfattr {int fa_attr; int fa_ino; } ;
struct smbfs_fctx {struct smbfattr f_attr; int /*<<< orphan*/  f_flags; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  SMBFS_RDD_FINDSINGLE ; 
 int SMB_FA_DIR ; 
 int SMB_FA_HIDDEN ; 
 int SMB_FA_SYSTEM ; 
 int /*<<< orphan*/  bzero (struct smbfattr*,int) ; 
 int /*<<< orphan*/  smbfs_findclose (struct smbfs_fctx*,struct smb_cred*) ; 
 int smbfs_findnext (struct smbfs_fctx*,int,struct smb_cred*) ; 
 int smbfs_findopen (struct smbnode*,char const*,int,int,struct smb_cred*,struct smbfs_fctx**) ; 

int
smbfs_smb_lookup(struct smbnode *dnp, const char *name, int nmlen,
	struct smbfattr *fap, struct smb_cred *scred)
{
	struct smbfs_fctx *ctx;
	int error;

	if (dnp == NULL || (dnp->n_ino == 2 && name == NULL)) {
		bzero(fap, sizeof(*fap));
		fap->fa_attr = SMB_FA_DIR;
		fap->fa_ino = 2;
		return 0;
	}
	MPASS(!(nmlen == 2 && name[0] == '.' && name[1] == '.'));
	MPASS(!(nmlen == 1 && name[0] == '.'));
	ASSERT_VOP_ELOCKED(dnp->n_vnode, "smbfs_smb_lookup");
	error = smbfs_findopen(dnp, name, nmlen,
	    SMB_FA_SYSTEM | SMB_FA_HIDDEN | SMB_FA_DIR, scred, &ctx);
	if (error)
		return error;
	ctx->f_flags |= SMBFS_RDD_FINDSINGLE;
	error = smbfs_findnext(ctx, 1, scred);
	if (error == 0) {
		*fap = ctx->f_attr;
		if (name == NULL)
			fap->fa_ino = dnp->n_ino;
	}
	smbfs_findclose(ctx, scred);
	return error;
}