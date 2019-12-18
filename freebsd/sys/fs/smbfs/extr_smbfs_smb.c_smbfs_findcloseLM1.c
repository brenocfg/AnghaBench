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
struct smbfs_fctx {scalar_t__ f_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  smb_rq_done (scalar_t__) ; 

__attribute__((used)) static int
smbfs_findcloseLM1(struct smbfs_fctx *ctx)
{
	if (ctx->f_rq)
		smb_rq_done(ctx->f_rq);
	return 0;
}