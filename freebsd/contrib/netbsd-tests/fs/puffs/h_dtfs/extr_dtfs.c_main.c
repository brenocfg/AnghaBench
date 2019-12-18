#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct puffs_usermount {int dummy; } ;
struct puffs_pathobj {char* po_path; int /*<<< orphan*/  po_len; } ;
struct puffs_ops {int dummy; } ;
struct dtfs_fid {int dummy; } ;
typedef  int /*<<< orphan*/ * mntoptparse_t ;
struct TYPE_3__ {int dtm_allowprot; } ;

/* Variables and functions */
 char* FSNAME ; 
 int MAXREQMAGIC ; 
 int /*<<< orphan*/  PUFFSOP_INIT (struct puffs_ops*) ; 
 int /*<<< orphan*/  PUFFSOP_SET (struct puffs_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUFFSOP_SETFSNOP (struct puffs_ops*,int /*<<< orphan*/ ) ; 
 int PUFFS_FHFLAG_DYNAMIC ; 
 int PUFFS_FHFLAG_NFSV2 ; 
 int PUFFS_FHFLAG_NFSV3 ; 
 int PUFFS_FLAG_BUILDPATH ; 
 int PUFFS_FLAG_OPDUMP ; 
 int PUFFS_KFLAG_IAONDEMAND ; 
 int PUFFS_KFLAG_LOOKUP_FULLPNBUF ; 
 int PUFFS_KFLAG_WTCACHE ; 
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ SIG_ERR ; 
 int VM_PROT_ALL ; 
 int /*<<< orphan*/  _PATH_PUFFS ; 
 int /*<<< orphan*/  access ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  create ; 
 int /*<<< orphan*/  dtfs ; 
 scalar_t__ dtfs_domount (struct puffs_usermount*,char*) ; 
 int dynamicfh ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fhtonode ; 
 int /*<<< orphan*/  freemntopts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs ; 
 TYPE_1__ gdtm ; 
 int /*<<< orphan*/  getattr ; 
 int /*<<< orphan*/ * getmntopts (char*,int /*<<< orphan*/ ,int*,int*) ; 
 int getopt (int,char**,char*) ; 
 struct puffs_usermount* gpu ; 
 int /*<<< orphan*/  inactive ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  lookup ; 
 int /*<<< orphan*/  loopfun ; 
 int /*<<< orphan*/  mkdir ; 
 int /*<<< orphan*/  mknod ; 
 int /*<<< orphan*/  mmap ; 
 int /*<<< orphan*/  node ; 
 int /*<<< orphan*/  nodetofh ; 
 int /*<<< orphan*/  pathconf ; 
 int /*<<< orphan*/  poll ; 
 int puffs_daemon (struct puffs_usermount*,int,int) ; 
 int /*<<< orphan*/  puffs_genfs ; 
 int /*<<< orphan*/  puffs_getroot (struct puffs_usermount*) ; 
 struct puffs_pathobj* puffs_getrootpathobj (struct puffs_usermount*) ; 
 struct puffs_usermount* puffs_init (struct puffs_ops*,int /*<<< orphan*/ ,char const*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  puffs_kernerr_abort ; 
 int puffs_mainloop (struct puffs_usermount*) ; 
 int /*<<< orphan*/  puffs_ml_setloopfn (struct puffs_usermount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puffs_ml_settimeout (struct puffs_usermount*,struct timespec*) ; 
 int puffs_mount (struct puffs_usermount*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puffs_set_errnotify (struct puffs_usermount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puffs_setfhsize (struct puffs_usermount*,int,int) ; 
 int /*<<< orphan*/  puffs_setmaxreqlen (struct puffs_usermount*,int) ; 
 int /*<<< orphan*/  puffs_setncookiehash (struct puffs_usermount*,int) ; 
 int /*<<< orphan*/  puffsmopts ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  readdir ; 
 int /*<<< orphan*/  readlink ; 
 int /*<<< orphan*/  reclaim ; 
 int /*<<< orphan*/  remove ; 
 int /*<<< orphan*/  rename ; 
 int /*<<< orphan*/  rmdir ; 
 int /*<<< orphan*/  setattr ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srandom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statvfs ; 
 int straightflush ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  symlink ; 
 int /*<<< orphan*/  sync ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmount ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  wipe_the_sleep_out_of_my_eyes ; 
 int /*<<< orphan*/  write ; 

int
main(int argc, char *argv[])
{
	extern char *optarg;
	extern int optind;
	struct puffs_usermount *pu;
	struct puffs_pathobj *po_root;
	struct puffs_ops *pops;
	struct timespec ts;
	const char *typename;
	char *rtstr;
	mntoptparse_t mp;
	int pflags, detach, mntflags;
	int ch;
	int khashbuckets;
	int maxreqsize;

	setprogname(argv[0]);

	rtstr = NULL;
	detach = 1;
	mntflags = 0;
	khashbuckets = 256;
	pflags = PUFFS_KFLAG_IAONDEMAND;
	typename = FSNAME;
	maxreqsize = MAXREQMAGIC;
	gdtm.dtm_allowprot = VM_PROT_ALL;
	while ((ch = getopt(argc, argv, "bc:dfilm:n:o:p:r:st")) != -1) {
		switch (ch) {
		case 'b': /* build paths, for debugging the feature */
			pflags |= PUFFS_FLAG_BUILDPATH;
			break;
		case 'c':
			khashbuckets = atoi(optarg);
			break;
		case 'd':
			dynamicfh = 1;
			break;
		case 'f':
			pflags |= PUFFS_KFLAG_LOOKUP_FULLPNBUF;
			break;
		case 'i':
			pflags &= ~PUFFS_KFLAG_IAONDEMAND;
			break;
		case 'l':
			straightflush = 1;
			break;
		case 'm':
			maxreqsize = atoi(optarg);
			break;
		case 'n':
			typename = optarg;
			break;
		case 'o':
			mp = getmntopts(optarg, puffsmopts, &mntflags, &pflags);
			if (mp == NULL)
				err(1, "getmntopts");
			freemntopts(mp);
			break;
		case 'p':
			gdtm.dtm_allowprot = atoi(optarg);
			if ((gdtm.dtm_allowprot | VM_PROT_ALL) != VM_PROT_ALL)
				usage();
			break;
		case 'r':
			rtstr = optarg;
			break;
		case 's': /* stay on top */
			detach = 0;
			break;
		case 't':
			pflags |= PUFFS_KFLAG_WTCACHE;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}
	}
	if (pflags & PUFFS_FLAG_OPDUMP)
		detach = 0;
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	PUFFSOP_INIT(pops);

	PUFFSOP_SET(pops, dtfs, fs, statvfs);
	PUFFSOP_SET(pops, dtfs, fs, unmount);
	PUFFSOP_SETFSNOP(pops, sync);
	PUFFSOP_SET(pops, dtfs, fs, fhtonode);
	PUFFSOP_SET(pops, dtfs, fs, nodetofh);

	PUFFSOP_SET(pops, dtfs, node, lookup);
	PUFFSOP_SET(pops, dtfs, node, access);
	PUFFSOP_SET(pops, puffs_genfs, node, getattr);
	PUFFSOP_SET(pops, dtfs, node, setattr);
	PUFFSOP_SET(pops, dtfs, node, create);
	PUFFSOP_SET(pops, dtfs, node, remove);
	PUFFSOP_SET(pops, dtfs, node, readdir);
	PUFFSOP_SET(pops, dtfs, node, poll);
	PUFFSOP_SET(pops, dtfs, node, mmap);
	PUFFSOP_SET(pops, dtfs, node, mkdir);
	PUFFSOP_SET(pops, dtfs, node, rmdir);
	PUFFSOP_SET(pops, dtfs, node, rename);
	PUFFSOP_SET(pops, dtfs, node, read);
	PUFFSOP_SET(pops, dtfs, node, write);
	PUFFSOP_SET(pops, dtfs, node, link);
	PUFFSOP_SET(pops, dtfs, node, symlink);
	PUFFSOP_SET(pops, dtfs, node, readlink);
	PUFFSOP_SET(pops, dtfs, node, mknod);
	PUFFSOP_SET(pops, dtfs, node, inactive);
	PUFFSOP_SET(pops, dtfs, node, pathconf);
	PUFFSOP_SET(pops, dtfs, node, reclaim);

	srandom(time(NULL)); /* for random generation numbers */

	pu = puffs_init(pops, _PATH_PUFFS, typename, &gdtm, pflags);
	if (pu == NULL)
		err(1, "init");
	gpu = pu;

	puffs_setfhsize(pu, sizeof(struct dtfs_fid),
	    PUFFS_FHFLAG_NFSV2 | PUFFS_FHFLAG_NFSV3
	    | (dynamicfh ? PUFFS_FHFLAG_DYNAMIC : 0));
	puffs_setncookiehash(pu, khashbuckets);

	if (signal(SIGALRM, wipe_the_sleep_out_of_my_eyes) == SIG_ERR)
		warn("cannot set alarm sighandler");

	/* init */
	if (dtfs_domount(pu, rtstr) != 0)
		errx(1, "dtfs_domount failed");

	po_root = puffs_getrootpathobj(pu);
	po_root->po_path = argv[0];
	po_root->po_len = strlen(argv[0]);

	/* often enough for testing poll */
	ts.tv_sec = 1;
	ts.tv_nsec = 0;
	puffs_ml_setloopfn(pu, loopfun);
	puffs_ml_settimeout(pu, &ts);

	if (maxreqsize != MAXREQMAGIC)
		puffs_setmaxreqlen(pu, maxreqsize);

	puffs_set_errnotify(pu, puffs_kernerr_abort);
	if (detach)
		if (puffs_daemon(pu, 1, 1) == -1)
			err(1, "puffs_daemon");

	if (puffs_mount(pu,  argv[1], mntflags, puffs_getroot(pu)) == -1)
		err(1, "mount");
	if (puffs_mainloop(pu) == -1)
		err(1, "mainloop");

	return 0;
}