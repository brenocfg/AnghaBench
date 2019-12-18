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
struct statfs {int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_fstypename; } ;
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int MNT_FORCE ; 
 int MNT_NONBUSY ; 
 int /*<<< orphan*/  NFSSVC_FORCEDISM ; 
 int /*<<< orphan*/  checkname (char*,char**) ; 
 int /*<<< orphan*/  checkvfsname (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fflag ; 
 int /*<<< orphan*/  free (struct statfs*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getfstab () ; 
 int getopt (int,char**,char*) ; 
 char** makevfslist (char*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int mntinfo (struct statfs**) ; 
 char* nfshost ; 
 int /*<<< orphan*/  nfshost_ai ; 
 int nfssvc (int /*<<< orphan*/ ,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  setfsent () ; 
 int /*<<< orphan*/  setfstab (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int umountall (char**) ; 
 int /*<<< orphan*/  umountfs (struct statfs*) ; 
 int unmount (char*,int) ; 
 int /*<<< orphan*/  usage () ; 
 int vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	int all, errs, ch, mntsize, error, nfsforce, ret;
	char **typelist = NULL;
	struct statfs *mntbuf, *sfs;
	struct addrinfo hints;

	nfsforce = all = errs = 0;
	while ((ch = getopt(argc, argv, "AaF:fh:Nnt:v")) != -1)
		switch (ch) {
		case 'A':
			all = 2;
			break;
		case 'a':
			all = 1;
			break;
		case 'F':
			setfstab(optarg);
			break;
		case 'f':
			fflag |= MNT_FORCE;
			break;
		case 'h':	/* -h implies -A. */
			all = 2;
			nfshost = optarg;
			break;
		case 'N':
			nfsforce = 1;
			break;
		case 'n':
			fflag |= MNT_NONBUSY;
			break;
		case 't':
			if (typelist != NULL)
				err(1, "only one -t option may be specified");
			typelist = makevfslist(optarg);
			break;
		case 'v':
			vflag = 1;
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	argc -= optind;
	argv += optind;

	if ((fflag & MNT_FORCE) != 0 && (fflag & MNT_NONBUSY) != 0)
		err(1, "-f and -n are mutually exclusive");

	if ((argc == 0 && !all) || (argc != 0 && all))
		usage();

	if (nfsforce != 0 && (argc == 0 || nfshost != NULL || typelist != NULL))
		usage();

	/* -h implies "-t nfs" if no -t flag. */
	if ((nfshost != NULL) && (typelist == NULL))
		typelist = makevfslist("nfs");

	if (nfshost != NULL) {
		memset(&hints, 0, sizeof hints);
		error = getaddrinfo(nfshost, NULL, &hints, &nfshost_ai);
		if (error)
			errx(1, "%s: %s", nfshost, gai_strerror(error));
	}

	switch (all) {
	case 2:
		if ((mntsize = mntinfo(&mntbuf)) <= 0)
			break;
		/*
		 * We unmount the nfs-mounts in the reverse order
		 * that they were mounted.
		 */
		for (errs = 0, mntsize--; mntsize > 0; mntsize--) {
			sfs = &mntbuf[mntsize];
			if (checkvfsname(sfs->f_fstypename, typelist))
				continue;
			if (strcmp(sfs->f_mntonname, "/dev") == 0)
				continue;
			if (umountfs(sfs) != 0)
				errs = 1;
		}
		free(mntbuf);
		break;
	case 1:
		if (setfsent() == 0)
			err(1, "%s", getfstab());
		errs = umountall(typelist);
		break;
	case 0:
		for (errs = 0; *argv != NULL; ++argv)
			if (nfsforce != 0) {
				/*
				 * First do the nfssvc() syscall to shut down
				 * the mount point and then do the forced
				 * dismount.
				 */
				ret = nfssvc(NFSSVC_FORCEDISM, *argv);
				if (ret >= 0)
					ret = unmount(*argv, MNT_FORCE);
				if (ret < 0) {
					warn("%s", *argv);
					errs = 1;
				}
			} else if (checkname(*argv, typelist) != 0)
				errs = 1;
		break;
	}
	exit(errs);
}