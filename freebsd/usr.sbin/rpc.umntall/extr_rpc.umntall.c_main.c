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
typedef  scalar_t__ time_t ;
struct mtablist {char* mtab_host; scalar_t__ mtab_time; char* mtab_dirp; struct mtablist* mtab_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MOUNTTAB ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  clean_mtab (char*,char*,int) ; 
 int do_umntall (char*) ; 
 int do_umount (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free_mtab () ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ is_mounted (char*,char*) ; 
 struct mtablist* mtabhead ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  read_mtab () ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 
 int write_mtab (int) ; 

int
main(int argc, char **argv) {
	int ch, keep, success, pathlen;
	time_t expire, now;
	char *host, *path;
	struct mtablist *mtab;

	expire = 0;
	host = path = NULL;
	success = keep = verbose = 0;
	while ((ch = getopt(argc, argv, "h:kp:ve:")) != -1)
		switch (ch) {
		case 'h':
			host = optarg;
			break;
		case 'e':
			expire = atoi(optarg);
			break;
		case 'k':
			keep = 1;
			break;
		case 'p':
			path = optarg;
			break;
		case 'v':
			verbose = 1;
			break;
		case '?':
			usage();
		default:
			break;
		}
	argc -= optind;
	argv += optind;

	/* Default expiretime is one day */
	if (expire == 0)
		expire = 86400;
	time(&now);

	/* Read PATH_MOUNTTAB. */
	if (!read_mtab()) {
		if (verbose)
			warnx("no mounttab entries (%s does not exist)",
			    PATH_MOUNTTAB);
		mtabhead = NULL;
	}

	if (host == NULL && path == NULL) {
		/* Check each entry and do any necessary unmount RPCs. */
		for (mtab = mtabhead; mtab != NULL; mtab = mtab->mtab_next) {
			if (*mtab->mtab_host == '\0')
				continue;
			if (mtab->mtab_time + expire < now) {
				/* Clear expired entry. */
				if (verbose)
					warnx("remove expired entry %s:%s",
					    mtab->mtab_host, mtab->mtab_dirp);
				bzero(mtab->mtab_host,
				    sizeof(mtab->mtab_host));
				continue;
			}
			if (keep && is_mounted(mtab->mtab_host,
			    mtab->mtab_dirp)) {
				if (verbose)
					warnx("skip entry %s:%s",
					    mtab->mtab_host, mtab->mtab_dirp);
				continue;
			}
			if (do_umount(mtab->mtab_host, mtab->mtab_dirp)) {
				if (verbose)
					warnx("umount RPC for %s:%s succeeded",
					    mtab->mtab_host, mtab->mtab_dirp);
				/* Remove all entries for this host + path. */
				clean_mtab(mtab->mtab_host, mtab->mtab_dirp,
				    verbose);
			}
		}
		success = 1;
	} else {
		if (host == NULL && path != NULL)
			/* Missing hostname. */
			usage();
		if (path == NULL) {
			/* Do a RPC UMNTALL for this specific host */
			success = do_umntall(host);
			if (verbose && success)
				warnx("umntall RPC for %s succeeded", host);
		} else {
			/* Do a RPC UMNTALL for this specific mount */
			for (pathlen = strlen(path);
			    pathlen > 1 && path[pathlen - 1] == '/'; pathlen--)
				path[pathlen - 1] = '\0';
			success = do_umount(host, path);
			if (verbose && success)
				warnx("umount RPC for %s:%s succeeded", host,
				    path);
		}
		/* If successful, remove any corresponding mounttab entries. */
		if (success)
			clean_mtab(host, path, verbose);
	}
	/* Write and unlink PATH_MOUNTTAB if necessary */
	if (success)
		success = write_mtab(verbose);
	free_mtab();
	exit (success ? 0 : 1);
}