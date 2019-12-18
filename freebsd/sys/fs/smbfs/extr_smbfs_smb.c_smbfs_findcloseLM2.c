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
struct smbfs_fctx {int f_flags; scalar_t__ f_t2; scalar_t__ f_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMBFSDATA ; 
 int SMBFS_RDD_NOCLOSE ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_t2_done (scalar_t__) ; 
 int /*<<< orphan*/  smbfs_smb_findclose2 (struct smbfs_fctx*) ; 

__attribute__((used)) static int
smbfs_findcloseLM2(struct smbfs_fctx *ctx)
{
	if (ctx->f_name)
		free(ctx->f_name, M_SMBFSDATA);
	if (ctx->f_t2)
		smb_t2_done(ctx->f_t2);
	if ((ctx->f_flags & SMBFS_RDD_NOCLOSE) == 0)
		smbfs_smb_findclose2(ctx);
	return 0;
}