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
struct smbfs_fctx {int f_flags; struct smbfs_fctx* f_rname; struct smb_cred* f_scred; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMBFSDATA ; 
 int SMBFS_RDD_USESEARCH ; 
 int /*<<< orphan*/  free (struct smbfs_fctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbfs_findcloseLM1 (struct smbfs_fctx*) ; 
 int /*<<< orphan*/  smbfs_findcloseLM2 (struct smbfs_fctx*) ; 

int
smbfs_findclose(struct smbfs_fctx *ctx, struct smb_cred *scred)
{
	ctx->f_scred = scred;
	if (ctx->f_flags & SMBFS_RDD_USESEARCH) {
		smbfs_findcloseLM1(ctx);
	} else
		smbfs_findcloseLM2(ctx);
	if (ctx->f_rname)
		free(ctx->f_rname, M_SMBFSDATA);
	free(ctx, M_SMBFSDATA);
	return 0;
}