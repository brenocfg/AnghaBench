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
struct statfs {char* f_mntonname; int /*<<< orphan*/  f_flags; } ;
struct stat {int st_mode; scalar_t__ st_uid; int st_flags; } ;
struct iovec {int dummy; } ;
struct group {int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int SF_SNAPSHOT ; 
 int S_IRGRP ; 
 int S_IRUSR ; 
 int S_ISTXT ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,char*,int) ; 
 int /*<<< orphan*/  err (int,char*,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fchmod (int,int) ; 
 scalar_t__ fchown (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 struct group* getgrnam (char*) ; 
 scalar_t__ getuid () ; 
 int isdir (char*,struct stat*) ; 
 int issamefs (char*,struct statfs*) ; 
 scalar_t__ nmount (struct iovec*,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ statfs (char*,struct statfs*) ; 
 char* strchrnul (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	char errmsg[255], path[PATH_MAX];
	char *cp, *snapname;
	struct statfs stfsbuf;
	struct group *grp;
	struct stat stbuf;
	struct iovec *iov;
	int fd, iovlen;

	if (argc == 2)
		snapname = argv[1];
	else if (argc == 3)
		snapname = argv[2];	/* Old usage. */
	else
		usage();

	/*
	 * Check that the user running this program has permission
	 * to create and remove a snapshot file from the directory
	 * in which they have requested to have it made. If the 
	 * directory is sticky and not owned by the user, then they
	 * will not be able to remove the snapshot when they are
	 * done with it.
	 */
	if (strlen(snapname) >= PATH_MAX)
		errx(1, "pathname too long %s", snapname);
	cp = strrchr(snapname, '/');
	if (cp == NULL) {
		strlcpy(path, ".", PATH_MAX);
	} else if (cp == snapname) {
		strlcpy(path, "/", PATH_MAX);
	} else {
		strlcpy(path, snapname, cp - snapname + 1);
	}
	if (statfs(path, &stfsbuf) < 0)
		err(1, "%s", path);
	switch (isdir(path, &stbuf)) {
	case -1:
		err(1, "%s", path);
	case 0:
		errx(1, "%s: Not a directory", path);
	default:
		break;
	}
	if (access(path, W_OK) < 0)
		err(1, "Lack write permission in %s", path);
	if ((stbuf.st_mode & S_ISTXT) && stbuf.st_uid != getuid())
		errx(1, "Lack write permission in %s: Sticky bit set", path);

	/*
	 * Work around an issue when mksnap_ffs is started in chroot'ed
	 * environment and f_mntonname contains absolute path within
	 * real root.
	 */
	for (cp = stfsbuf.f_mntonname; issamefs(cp, &stfsbuf) != 1;
	    cp = strchrnul(cp + 1, '/')) {
		if (cp[0] == '\0')
			errx(1, "%s: Not a mount point", stfsbuf.f_mntonname);
	}
	if (cp != stfsbuf.f_mntonname)
		strlcpy(stfsbuf.f_mntonname, cp, sizeof(stfsbuf.f_mntonname));

	/*
	 * Having verified access to the directory in which the
	 * snapshot is to be built, proceed with creating it.
	 */
	if ((grp = getgrnam("operator")) == NULL)
		errx(1, "Cannot retrieve operator gid");

	iov = NULL;
	iovlen = 0;
	build_iovec(&iov, &iovlen, "fstype", "ffs", 4);
	build_iovec(&iov, &iovlen, "from", snapname, (size_t)-1);
	build_iovec(&iov, &iovlen, "fspath", stfsbuf.f_mntonname, (size_t)-1);
	build_iovec(&iov, &iovlen, "errmsg", errmsg, sizeof(errmsg));
	build_iovec(&iov, &iovlen, "update", NULL, 0);
	build_iovec(&iov, &iovlen, "snapshot", NULL, 0);

	*errmsg = '\0';
	if (nmount(iov, iovlen, stfsbuf.f_flags) < 0) {
		errmsg[sizeof(errmsg) - 1] = '\0';
		err(1, "Cannot create snapshot %s%s%s", snapname,
		    *errmsg != '\0' ? ": " : "", errmsg);
	}
	if ((fd = open(snapname, O_RDONLY)) < 0)
		err(1, "Cannot open %s", snapname);
	if (fstat(fd, &stbuf) != 0)
		err(1, "Cannot stat %s", snapname);
	if ((stbuf.st_flags & SF_SNAPSHOT) == 0)
		errx(1, "File %s is not a snapshot", snapname);
	if (fchown(fd, -1, grp->gr_gid) != 0)
		err(1, "Cannot chown %s", snapname);
	if (fchmod(fd, S_IRUSR | S_IRGRP) != 0)
		err(1, "Cannot chmod %s", snapname);

	exit(EXIT_SUCCESS);
}