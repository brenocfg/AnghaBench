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
struct TYPE_2__ {int /*<<< orphan*/  ioc_retrycount; int /*<<< orphan*/  ioc_timeout; } ;
struct smb_ctx {TYPE_1__ ct_ssn; } ;

/* Variables and functions */
 int /*<<< orphan*/  rc_getint (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_getstringptr (int /*<<< orphan*/ ,char const*,char*,char**) ; 
 int smb_ctx_setcharset (struct smb_ctx*,char*) ; 
 int /*<<< orphan*/  smb_ctx_setpassword (struct smb_ctx*,char*) ; 
 int smb_ctx_setsrvaddr (struct smb_ctx*,char*) ; 
 int /*<<< orphan*/  smb_ctx_setworkgroup (struct smb_ctx*,char*) ; 
 int /*<<< orphan*/  smb_error (char*,int,char const*) ; 
 int /*<<< orphan*/  smb_rc ; 

__attribute__((used)) static int
smb_ctx_readrcsection(struct smb_ctx *ctx, const char *sname, int level)
{
	char *p;
	int error;

	if (level >= 0) {
		rc_getstringptr(smb_rc, sname, "charsets", &p);
		if (p) {
			error = smb_ctx_setcharset(ctx, p);
			if (error)
				smb_error("charset specification in the section '%s' ignored", error, sname);
		}
	}
	if (level <= 1) {
		rc_getint(smb_rc, sname, "timeout", &ctx->ct_ssn.ioc_timeout);
		rc_getint(smb_rc, sname, "retry_count", &ctx->ct_ssn.ioc_retrycount);
	}
	if (level == 1) {
		rc_getstringptr(smb_rc, sname, "addr", &p);
		if (p) {
			error = smb_ctx_setsrvaddr(ctx, p);
			if (error) {
				smb_error("invalid address specified in the section %s", 0, sname);
				return error;
			}
		}
	}
	if (level >= 2) {
		rc_getstringptr(smb_rc, sname, "password", &p);
		if (p)
			smb_ctx_setpassword(ctx, p);
	}
	rc_getstringptr(smb_rc, sname, "workgroup", &p);
	if (p)
		smb_ctx_setworkgroup(ctx, p);
	return 0;
}