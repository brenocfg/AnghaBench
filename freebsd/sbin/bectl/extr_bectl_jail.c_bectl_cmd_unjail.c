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

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  be ; 
 scalar_t__ be_mounted_at (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_unmount (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bectl_jail_cleanup (char*,int) ; 
 int bectl_locate_jail (char*) ; 
 int /*<<< orphan*/  bzero (char**,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* jail_getname (int) ; 
 int jail_getv (int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int usage (int) ; 

int
bectl_cmd_unjail(int argc, char *argv[])
{
	char path[MAXPATHLEN];
	char *cmd, *name, *target;
	int jid;

	/* Store alias used */
	cmd = argv[0];

	if (argc != 2) {
		fprintf(stderr, "bectl %s: wrong number of arguments\n", cmd);
		return (usage(false));
	}

	target = argv[1];

	/* Locate the jail */
	if ((jid = bectl_locate_jail(target)) == -1) {
		fprintf(stderr, "bectl %s: failed to locate BE by '%s'\n", cmd,
		    target);
		return (1);
	}

	bzero(&path, MAXPATHLEN);
	name = jail_getname(jid);
	if (jail_getv(0, "name", name, "path", path, NULL) != jid) {
		free(name);
		fprintf(stderr,
		    "bectl %s: failed to get path for jail requested by '%s'\n",
		    cmd, target);
		return (1);
	}

	free(name);

	if (be_mounted_at(be, path, NULL) != 0) {
		fprintf(stderr, "bectl %s: jail requested by '%s' not a BE\n",
		    cmd, target);
		return (1);
	}

	bectl_jail_cleanup(path, jid);
	be_unmount(be, target, 0);

	return (0);
}