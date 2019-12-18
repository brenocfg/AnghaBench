#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* ioc_password; } ;
struct TYPE_3__ {char const* ioc_password; } ;
struct smb_ctx {TYPE_2__ ct_ssn; TYPE_1__ ct_sh; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 scalar_t__ SMB_MAXPASSWORDLEN ; 
 int /*<<< orphan*/  smb_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_simpledecrypt (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int
smb_ctx_setpassword(struct smb_ctx *ctx, const char *passwd)
{
	if (passwd == NULL)
		return EINVAL;
	if (strlen(passwd) > SMB_MAXPASSWORDLEN) {
		smb_error("password too long", 0);
		return ENAMETOOLONG;
	}
	if (strncmp(passwd, "$$1", 3) == 0)
		smb_simpledecrypt(ctx->ct_ssn.ioc_password, passwd);
	else
		strcpy(ctx->ct_ssn.ioc_password, passwd);
	strcpy(ctx->ct_sh.ioc_password, ctx->ct_ssn.ioc_password);
	return 0;
}