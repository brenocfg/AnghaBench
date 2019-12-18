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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_WAIT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cont_search ; 
 int /*<<< orphan*/  find_snapshot (struct statfs*) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbose ; 

int
main(int argc, char **argv)
{
	char *path;
	struct stat st;
	struct statfs *mntbuf;
	int all = 0, ch, done = 0, fscount, n;

	while ((ch = getopt(argc, argv, "adv")) != -1) {
		switch (ch) {
		case 'a':
			all++;
			break;
		case 'd':
			/* continue to search when matching inode is found 
			 * this feature is not documented */
			cont_search++;
			break;
		case 'v':
			verbose++;
			break;
		default:
			usage();
		}
	}

	argc -= optind;
	argv += optind;

	if ((all == 0 && argc != 1) || (all == 1 && argc > 0))
		usage();

	if (!all) {
		char resolved[PATH_MAX];

		path = *argv;
		/*
		 * mount(8) use realpath(3) before mounting file system,
		 * so let's do the same with the given path.
		 */
		if (realpath(path, resolved) == NULL ||	/* can create full path */
		    stat(resolved, &st) == -1 ||	/* is it stat'able */
		    !S_ISDIR(st.st_mode)) {		/* is it a directory */
			usage();
		}
		path = resolved;
	}

	fscount = getmntinfo(&mntbuf, MNT_WAIT);
	for (n = 0; n < fscount; n++) {
		if (!strncmp(mntbuf[n].f_fstypename, "ufs", 3)) {
			if (all || strcmp(path, mntbuf[n].f_mntonname) == 0) {
				find_snapshot(&mntbuf[n]);
				done++;
			}
		}
	}

	if (done == 0)
		usage();

	return (0);
}