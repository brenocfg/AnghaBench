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
struct fstab {int /*<<< orphan*/  fs_spec; int /*<<< orphan*/  fs_vfstype; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int) ; 
 struct fstab* getfsent () ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*) ; 
 char** malloc (int) ; 
 char** realloc (char**,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char **
enum_dumpdevs(int *argcp)
{
	struct fstab *fsp;
	char **argv;
	int argc, n;

	/*
	 * We cannot use getfsent(3) in capability mode, so we must
	 * scan /etc/fstab and build up a list of candidate devices
	 * before proceeding.
	 */
	argc = 0;
	n = 8;
	argv = malloc(n * sizeof(*argv));
	if (argv == NULL) {
		logmsg(LOG_ERR, "malloc(): %m");
		exit(1);
	}
	for (;;) {
		fsp = getfsent();
		if (fsp == NULL)
			break;
		if (strcmp(fsp->fs_vfstype, "swap") != 0 &&
		    strcmp(fsp->fs_vfstype, "dump") != 0)
			continue;
		if (argc >= n) {
			n *= 2;
			argv = realloc(argv, n * sizeof(*argv));
			if (argv == NULL) {
				logmsg(LOG_ERR, "realloc(): %m");
				exit(1);
			}
		}
		argv[argc] = strdup(fsp->fs_spec);
		if (argv[argc] == NULL) {
			logmsg(LOG_ERR, "strdup(): %m");
			exit(1);
		}
		argc++;
	}
	*argcp = argc;
	return (argv);
}