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
typedef  int /*<<< orphan*/  tmp ;
struct smb_ctx {scalar_t__ ct_maxlevel; scalar_t__ ct_minlevel; scalar_t__ ct_parsedlevel; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SMBL_NONE ; 
 scalar_t__ SMBL_SHARE ; 
 scalar_t__ SMBL_VC ; 
 int SMB_ST_NONE ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int getsubstring (char const*,char,char*,int,char const**) ; 
 int smb_ctx_setnbport (struct smb_ctx*,int /*<<< orphan*/ ) ; 
 int smb_ctx_setserver (struct smb_ctx*,char*) ; 
 int smb_ctx_setshare (struct smb_ctx*,char*,int) ; 
 int smb_ctx_setsmbport (struct smb_ctx*,int /*<<< orphan*/ ) ; 
 int smb_ctx_setuser (struct smb_ctx*,char*) ; 
 int /*<<< orphan*/  smb_error (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

int
smb_ctx_parseunc(struct smb_ctx *ctx, const char *unc, int sharetype,
	const char **next)
{
	const char *p = unc;
	char *p1, *psmb, *pnb;
	char tmp[1024];
	int error ;

	ctx->ct_parsedlevel = SMBL_NONE;
	if (*p++ != '/' || *p++ != '/') {
		smb_error("UNC should start with '//'", 0);
		return EINVAL;
	}
	p1 = tmp;
	error = getsubstring(p, '@', p1, sizeof(tmp), &p);
	if (!error) {
		if (ctx->ct_maxlevel < SMBL_VC) {
			smb_error("no user name required", 0);
			return EINVAL;
		}
		error = smb_ctx_setuser(ctx, tmp);
		if (error)
			return error;
		ctx->ct_parsedlevel = SMBL_VC;
	}
	error = getsubstring(p, '/', p1, sizeof(tmp), &p);
	if (error) {
		error = getsubstring(p, '\0', p1, sizeof(tmp), &p);
		if (error) {
			smb_error("no server name found", 0);
			return error;
		}
	}
	if (*p1 == 0) {
		smb_error("empty server name", 0);
		return EINVAL;
	}
	/*
	 * Check for port number specification.
	 */
	psmb = strchr(tmp, ':');
	if (psmb) {
		*psmb++ = '\0';
		pnb = strchr(psmb, ':');
		if (pnb) {
			*pnb++ = '\0';
			error = smb_ctx_setnbport(ctx, atoi(pnb));
			if (error) {
				smb_error("Invalid NetBIOS port number", 0);
				return error;
			}
		}
		error = smb_ctx_setsmbport(ctx, atoi(psmb));
		if (error) {
			smb_error("Invalid SMB port number", 0);
			return error;
		}
	}
	error = smb_ctx_setserver(ctx, tmp);
	if (error)
		return error;
	if (sharetype == SMB_ST_NONE) {
		*next = p;
		return 0;
	}
	if (*p != 0 && ctx->ct_maxlevel < SMBL_SHARE) {
		smb_error("no share name required", 0);
		return EINVAL;
	}
	error = getsubstring(p, '/', p1, sizeof(tmp), &p);
	if (error) {
		error = getsubstring(p, '\0', p1, sizeof(tmp), &p);
		if (error) {
			smb_error("unexpected end of line", 0);
			return error;
		}
	}
	if (*p1 == 0 && ctx->ct_minlevel >= SMBL_SHARE) {
		smb_error("empty share name", 0);
		return EINVAL;
	}
	*next = p;
	if (*p1 == 0)
		return 0;
	error = smb_ctx_setshare(ctx, p1, sharetype);
	return error;
}