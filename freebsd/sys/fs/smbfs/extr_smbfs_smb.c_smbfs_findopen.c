#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smbnode {TYPE_1__* n_mount; } ;
struct smbfs_fctx {int /*<<< orphan*/  f_flags; int /*<<< orphan*/  f_ssp; struct smb_cred* f_scred; struct smbnode* f_dnp; } ;
struct smb_cred {int dummy; } ;
struct TYPE_2__ {int sm_flags; int /*<<< orphan*/  sm_share; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMBFSDATA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SMBFS_MOUNT_NO_LONG ; 
 int /*<<< orphan*/  SMBFS_RDD_FINDFIRST ; 
 int /*<<< orphan*/  SMBFS_RDD_USESEARCH ; 
 scalar_t__ SMB_DIALECT (int /*<<< orphan*/ ) ; 
 scalar_t__ SMB_DIALECT_LANMAN2_0 ; 
 int /*<<< orphan*/  SSTOVC (int /*<<< orphan*/ ) ; 
 struct smbfs_fctx* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smbfs_findclose (struct smbfs_fctx*,struct smb_cred*) ; 
 int smbfs_findopenLM1 (struct smbfs_fctx*,struct smbnode*,char const*,int,int,struct smb_cred*) ; 
 int smbfs_findopenLM2 (struct smbfs_fctx*,struct smbnode*,char const*,int,int,struct smb_cred*) ; 

int
smbfs_findopen(struct smbnode *dnp, const char *wildcard, int wclen, int attr,
	struct smb_cred *scred, struct smbfs_fctx **ctxpp)
{
	struct smbfs_fctx *ctx;
	int error;

	ctx = malloc(sizeof(*ctx), M_SMBFSDATA, M_WAITOK | M_ZERO);
	ctx->f_ssp = dnp->n_mount->sm_share;
	ctx->f_dnp = dnp;
	ctx->f_flags = SMBFS_RDD_FINDFIRST;
	ctx->f_scred = scred;
	if (SMB_DIALECT(SSTOVC(ctx->f_ssp)) < SMB_DIALECT_LANMAN2_0 ||
	    (dnp->n_mount->sm_flags & SMBFS_MOUNT_NO_LONG)) {
		ctx->f_flags |= SMBFS_RDD_USESEARCH;
		error = smbfs_findopenLM1(ctx, dnp, wildcard, wclen, attr, scred);
	} else
		error = smbfs_findopenLM2(ctx, dnp, wildcard, wclen, attr, scred);
	if (error)
		smbfs_findclose(ctx, scred);
	else
		*ctxpp = ctx;
	return error;
}