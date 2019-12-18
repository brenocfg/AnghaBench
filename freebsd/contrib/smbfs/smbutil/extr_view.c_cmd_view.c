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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct smb_share_info_1 {char* shi1_netname; int /*<<< orphan*/  shi1_remark; int /*<<< orphan*/  shi1_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_srvname; } ;
struct smb_ctx {TYPE_1__ ct_ssn; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  SMBLK_CREATE ; 
 int /*<<< orphan*/  SMBL_SHARE ; 
 int /*<<< orphan*/  SMBL_VC ; 
 int SMB_ERROR_MORE_DATA ; 
 int SMB_RAP_ERROR ; 
 int /*<<< orphan*/  SMB_ST_ANY ; 
#define  STDPARAM_ARGS 128 
 int /*<<< orphan*/  STDPARAM_OPT ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (struct smb_share_info_1*) ; 
 int getopt (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ loadsmbvfs () ; 
 struct smb_share_info_1* malloc (int) ; 
 size_t min (int /*<<< orphan*/ ,int) ; 
 char* nls_str_toloc (char*,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rc_close (scalar_t__) ; 
 char** shtype ; 
 scalar_t__ smb_ctx_init (struct smb_ctx*,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smb_ctx_lookup (struct smb_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smb_ctx_opt (struct smb_ctx*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ smb_ctx_readrc (struct smb_ctx*) ; 
 scalar_t__ smb_ctx_resolve (struct smb_ctx*) ; 
 int /*<<< orphan*/  smb_ctx_setshare (struct smb_ctx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_error (char*,int,...) ; 
 int smb_rap_NetShareEnum (struct smb_ctx*,int,struct smb_share_info_1*,int,int*,int*) ; 
 scalar_t__ smb_rc ; 
 int /*<<< orphan*/  view_usage () ; 

int
cmd_view(int argc, char *argv[])
{
	struct smb_ctx sctx, *ctx = &sctx;
	struct smb_share_info_1 *rpbuf, *ep;
	char *cp;
	u_int32_t remark;
	u_int16_t type;
	int error, opt, bufsize, i, entries, total;
	

	if (argc < 2)
		view_usage();
	if (smb_ctx_init(ctx, argc, argv, SMBL_VC, SMBL_VC, SMB_ST_ANY) != 0)
		exit(1);
	if (smb_ctx_readrc(ctx) != 0)
		exit(1);
	if (smb_rc)
		rc_close(smb_rc);
	while ((opt = getopt(argc, argv, STDPARAM_OPT)) != EOF) {
		switch(opt){
		    case STDPARAM_ARGS:
			error = smb_ctx_opt(ctx, opt, optarg);
			if (error)
				exit(1);
			break;
		    default:
			view_usage();
			/*NOTREACHED*/
		}
	}
#ifdef APPLE
	if (loadsmbvfs())
		errx(EX_OSERR, "SMB filesystem is not available");
#endif
	smb_ctx_setshare(ctx, "IPC$", SMB_ST_ANY);
	if (smb_ctx_resolve(ctx) != 0)
		exit(1);
	error = smb_ctx_lookup(ctx, SMBL_SHARE, SMBLK_CREATE);
	if (error) {
		smb_error("could not login to server %s", error, ctx->ct_ssn.ioc_srvname);
		exit(1);
	}
	printf("Share        Type       Comment\n");
	printf("-------------------------------\n");
	bufsize = 0xffe0; /* samba notes win2k bug with 65535 */
	rpbuf = malloc(bufsize);
	error = smb_rap_NetShareEnum(ctx, 1, rpbuf, bufsize, &entries, &total);
	if (error &&
	    error != (SMB_ERROR_MORE_DATA | SMB_RAP_ERROR)) {
		smb_error("unable to list resources", error);
		exit(1);
	}
	for (ep = rpbuf, i = 0; i < entries; i++, ep++) {
		type = le16toh(ep->shi1_type);
		remark = le32toh(ep->shi1_remark);
		remark &= 0xFFFF;

		cp = (char*)rpbuf + remark;
		printf("%-12s %-10s %s\n", ep->shi1_netname,
		    shtype[min(type, sizeof shtype / sizeof(char *) - 1)],
		    remark ? nls_str_toloc(cp, cp) : "");
	}
	printf("\n%d shares listed from %d available\n", entries, total);
	free(rpbuf);
	return 0;
}