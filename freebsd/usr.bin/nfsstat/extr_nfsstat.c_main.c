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
typedef  scalar_t__ u_int ;
struct statfs {char* f_mntonname; char* f_mntfromname; int /*<<< orphan*/  f_fstypename; } ;
struct nfscl_dumpmntopts {char* ndmnt_fname; char* ndmnt_buf; int ndmnt_blen; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int /*<<< orphan*/  NFSSTAT_XO_VERSION ; 
 int /*<<< orphan*/  NFSSVC_DUMPMNTOPTS ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exp_intpr (int,int,scalar_t__) ; 
 int /*<<< orphan*/  exp_sidewaysintpr (scalar_t__,int,int,int) ; 
 scalar_t__ extra_output ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  intpr (int,int) ; 
 scalar_t__ modfind (char*) ; 
 int /*<<< orphan*/  nfssvc (int /*<<< orphan*/ ,struct nfscl_dumpmntopts*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  printtitle ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int widemode ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_set_version (int /*<<< orphan*/ ) ; 
 int zflag ; 

int
main(int argc, char **argv)
{
	u_int interval;
	int clientOnly = -1;
	int serverOnly = -1;
	int newStats = 0;
	int ch;
	char *memf, *nlistf;
	int mntlen, i;
	char buf[1024];
	struct statfs *mntbuf;
	struct nfscl_dumpmntopts dumpmntopts;

	interval = 0;
	memf = nlistf = NULL;

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(1);

	xo_set_version(NFSSTAT_XO_VERSION);

	while ((ch = getopt(argc, argv, "cdEesWM:mN:w:zq")) != -1)
		switch(ch) {
		case 'M':
			memf = optarg;
			break;
		case 'm':
			/* Display mount options for NFS mount points. */
			mntlen = getmntinfo(&mntbuf, MNT_NOWAIT);
			for (i = 0; i < mntlen; i++) {
				if (strcmp(mntbuf->f_fstypename, "nfs") == 0) {
					dumpmntopts.ndmnt_fname =
					    mntbuf->f_mntonname;
					dumpmntopts.ndmnt_buf = buf;
					dumpmntopts.ndmnt_blen = sizeof(buf);
					if (nfssvc(NFSSVC_DUMPMNTOPTS,
					    &dumpmntopts) >= 0)
						printf("%s on %s\n%s\n",
						    mntbuf->f_mntfromname,
						    mntbuf->f_mntonname, buf);
					else if (errno == EPERM)
						errx(1, "Only priviledged users"
						    " can use the -m option");
				}
				mntbuf++;
			}
			exit(0);
		case 'N':
			nlistf = optarg;
			break;
		case 'W':
			widemode = 1;
			break;
		case 'w':
			interval = atoi(optarg);
			break;
		case 'c':
			clientOnly = 1;
			if (serverOnly < 0)
				serverOnly = 0;
			break;
		case 'd':
			newStats = 1;
			if (interval == 0)
				interval = 1;
			break;
		case 's':
			serverOnly = 1;
			if (clientOnly < 0)
				clientOnly = 0;
			break;
		case 'z':
			zflag = 1;
			break;
		case 'E':
			if (extra_output != 0)
				xo_err(1, "-e and -E are mutually exclusive");
			extra_output = 2;
			break;
		case 'e':
			if (extra_output != 0)
				xo_err(1, "-e and -E are mutually exclusive");
			extra_output = 1;
			break;
		case 'q':
			printtitle = 0;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

#define	BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
	if (*argv) {
		interval = atoi(*argv);
		if (*++argv) {
			nlistf = *argv;
			if (*++argv)
				memf = *argv;
		}
	}
#endif
	if (modfind("nfscommon") < 0)
		xo_err(1, "NFS client/server not loaded");

	if (interval) {
		exp_sidewaysintpr(interval, clientOnly, serverOnly,
		    newStats);
	} else {
		xo_open_container("nfsstat");
		if (extra_output != 0)
			exp_intpr(clientOnly, serverOnly, extra_output - 1);
		else
			intpr(clientOnly, serverOnly);
		xo_close_container("nfsstat");
	}

	xo_finish();
	exit(0);
}