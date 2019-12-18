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
struct TYPE_4__ {int /*<<< orphan*/  ioc_srvname; int /*<<< orphan*/  ioc_opt; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioc_opt; } ;
struct smb_ctx {int ct_parsedlevel; TYPE_2__ ct_ssn; TYPE_1__ ct_sh; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int EOF ; 
 int /*<<< orphan*/  EX_OSERR ; 
#define  SMBL_SHARE 130 
#define  SMBL_VC 129 
 int /*<<< orphan*/  SMBSOPT_CREATE ; 
 int SMBS_PERMANENT ; 
 int /*<<< orphan*/  SMBVOPT_CREATE ; 
 int SMBV_PERMANENT ; 
 int /*<<< orphan*/  SMB_ST_ANY ; 
#define  STDPARAM_ARGS 128 
 int /*<<< orphan*/  STDPARAM_OPT ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,int /*<<< orphan*/ ) ; 
 int loadsmbvfs () ; 
 int /*<<< orphan*/  logout_usage () ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rc_close (scalar_t__) ; 
 scalar_t__ smb_ctx_init (struct smb_ctx*,int,char**,int,int,int /*<<< orphan*/ ) ; 
 int smb_ctx_lookup (struct smb_ctx*,int,int /*<<< orphan*/ ) ; 
 int smb_ctx_opt (struct smb_ctx*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ smb_ctx_readrc (struct smb_ctx*) ; 
 scalar_t__ smb_ctx_resolve (struct smb_ctx*) ; 
 int smb_ctx_setflags (struct smb_ctx*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_error (char*,int,...) ; 
 scalar_t__ smb_rc ; 

int
cmd_logout(int argc, char *argv[])
{
	struct smb_ctx sctx, *ctx = &sctx;
	int error, opt, level;

	if (argc < 2)
		logout_usage();
	if (smb_ctx_init(ctx, argc, argv, SMBL_VC, SMBL_SHARE, SMB_ST_ANY) != 0)
		exit(1);
	if (smb_ctx_readrc(ctx) != 0)
		exit(1);
	if (smb_rc)
		rc_close(smb_rc);
	while ((opt = getopt(argc, argv, STDPARAM_OPT)) != EOF){
		switch (opt) {
		    case STDPARAM_ARGS:
			error = smb_ctx_opt(ctx, opt, optarg);
			if (error)
				exit(1);
			break;
		    default:
			logout_usage();
			/*NOTREACHED*/
		}
	}
#ifdef APPLE
	error = loadsmbvfs();
	if (error)
		errx(EX_OSERR, "SMB filesystem is not available");
#endif
	ctx->ct_ssn.ioc_opt &= ~SMBVOPT_CREATE;
	ctx->ct_sh.ioc_opt &= ~SMBSOPT_CREATE;
	if (smb_ctx_resolve(ctx) != 0)
		exit(1);
	level = ctx->ct_parsedlevel;
	error = smb_ctx_lookup(ctx, level, 0);
	if (error == ENOENT) {
/*		ctx->ct_ssn.ioc_opt |= SMBCOPT_SINGLE;
		error = smb_ctx_login(ctx);
		if (error == ENOENT) {
			ctx->ct_ssn.ioc_opt |= SMBCOPT_PRIVATE;
			error = smb_ctx_login(ctx);
			if (error == ENOENT) {
				ctx->ct_ssn.ioc_opt &= ~SMBCOPT_SINGLE;
				error = smb_ctx_login(ctx);
			}
		}*/
		if (error) {
			smb_error("There is no connection to %s", error, ctx->ct_ssn.ioc_srvname);
			exit(1);
		}
	}
	if (error)
		exit(1);
	switch (level) {
	    case SMBL_VC:
		opt = SMBV_PERMANENT;
		break;
	    case SMBL_SHARE:
		opt = SMBS_PERMANENT;
		break;
	    default:
		smb_error("unknown connection level %d", 0, level);
		exit(1);
	}
	error = smb_ctx_setflags(ctx, level, opt, 0);
	if (error && error != EACCES) {
		smb_error("Can't release connection", error);
		exit(1);
	}
	printf("Connection unmarked as permanent and will be closed when possible\n");
	exit(0);
}