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
struct TYPE_2__ {char* ioc_srvname; char* ioc_user; } ;
struct smb_ctx {TYPE_1__ ct_ssn; } ;
typedef  int /*<<< orphan*/  smbfh ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  fnamebuf ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EIO ; 
 int EOF ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SMBLK_CREATE ; 
 int /*<<< orphan*/  SMBL_SHARE ; 
 int /*<<< orphan*/  SMB_ST_PRINTER ; 
#define  STDPARAM_ARGS 128 
 int /*<<< orphan*/  STDPARAM_OPT ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  rc_close (scalar_t__) ; 
 int read (int,char*,int) ; 
 scalar_t__ smb_ctx_init (struct smb_ctx*,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smb_ctx_lookup (struct smb_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smb_ctx_opt (struct smb_ctx*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ smb_ctx_readrc (struct smb_ctx*) ; 
 scalar_t__ smb_ctx_resolve (struct smb_ctx*) ; 
 int /*<<< orphan*/  smb_error (char*,int,...) ; 
 scalar_t__ smb_rc ; 
 int smb_smb_close_print_file (struct smb_ctx*,int /*<<< orphan*/ ) ; 
 int smb_smb_open_print_file (struct smb_ctx*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int smb_write (struct smb_ctx*,int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  view_usage () ; 

int
cmd_print(int argc, char *argv[])
{
	struct smb_ctx sctx, *ctx = &sctx;
	smbfh fh;
	off_t offset;
	char buf[8192];
	char *filename;
	char fnamebuf[256];
	int error, opt, i, file, count;

	if (argc < 2)
		view_usage();
	if (smb_ctx_init(ctx, argc, argv, SMBL_SHARE, SMBL_SHARE, SMB_ST_PRINTER) != 0)
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
	if (optind + 1 >= argc)
		print_usage();
	filename = argv[optind + 1];

	if (strcmp(filename, "-") == 0) {
		file = 0;	/* stdin */
		filename = "stdin";
	} else {
		file = open(filename, O_RDONLY, 0);
		if (file < 0) {
			smb_error("could not open file %s\n", errno, filename);
			exit(1);
		}
	}

	if (smb_ctx_resolve(ctx) != 0)
		exit(1);
	error = smb_ctx_lookup(ctx, SMBL_SHARE, SMBLK_CREATE);
	if (error) {
		smb_error("could not login to server %s", error, ctx->ct_ssn.ioc_srvname);
		exit(1);
	}
	snprintf(fnamebuf, sizeof(fnamebuf), "%s_%s_%s", ctx->ct_ssn.ioc_user,
	    ctx->ct_ssn.ioc_srvname, filename);
	error = smb_smb_open_print_file(ctx, 0, 1, fnamebuf, &fh);
	if (error) {
		smb_error("could not open print job", error);
		exit(1);
	}
	offset = 0;
	error = 0;
	for(;;) {
		count = read(file, buf, sizeof(buf));
		if (count == 0)
			break;
		if (count < 0) {
			error = errno;
			smb_error("error reading input file\n", error);
			break;
		}
		i = smb_write(ctx, fh, offset, count, buf);
		if (i < 0) {
			error = errno;
			smb_error("error writing spool file\n", error);
			break;
		}
		if (i != count) {
			smb_error("incomplete write to spool file\n", 0);
			error = EIO;
			break;
		}
		offset += count;
	}
	close(file);
	error = smb_smb_close_print_file(ctx, fh);
	if (error)
		smb_error("an error while closing spool file\n", error);
	return error ? 1 : 0;
}