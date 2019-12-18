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
struct TYPE_2__ {int ioc_stype; int /*<<< orphan*/  ioc_share; } ;
struct smb_ctx {TYPE_1__ ct_sh; int /*<<< orphan*/  ct_parsedlevel; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  SMBL_SHARE ; 
 scalar_t__ SMB_MAXSHARENAMELEN ; 
 int /*<<< orphan*/  nls_str_upper (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  smb_error (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
smb_ctx_setshare(struct smb_ctx *ctx, const char *share, int stype)
{
	if (strlen(share) > SMB_MAXSHARENAMELEN) {
		smb_error("share name '%s' too long", 0, share);
		return ENAMETOOLONG;
	}
	nls_str_upper(ctx->ct_sh.ioc_share, share);
	if (share[0] != 0)
		ctx->ct_parsedlevel = SMBL_SHARE;
	ctx->ct_sh.ioc_stype = stype;
	return 0;
}