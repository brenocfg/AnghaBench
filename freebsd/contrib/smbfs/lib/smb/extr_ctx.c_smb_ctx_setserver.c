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
struct TYPE_2__ {int /*<<< orphan*/  ioc_srvname; } ;
struct smb_ctx {TYPE_1__ ct_ssn; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 scalar_t__ SMB_MAXSRVNAMELEN ; 
 int /*<<< orphan*/  nls_str_upper (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  smb_error (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
smb_ctx_setserver(struct smb_ctx *ctx, const char *name)
{
	if (strlen(name) > SMB_MAXSRVNAMELEN) {
		smb_error("server name '%s' too long", 0, name);
		return ENAMETOOLONG;
	}
	nls_str_upper(ctx->ct_ssn.ioc_srvname, name);
	return 0;
}