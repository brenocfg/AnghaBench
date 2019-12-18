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
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ geteuid () ; 
 int getgroups (long,scalar_t__*) ; 
 scalar_t__ gid ; 
 int /*<<< orphan*/  gname ; 
 scalar_t__* malloc (int) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ uid ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chownerr(const char *file)
{
	static uid_t euid = -1;
	static int ngroups = -1;
	static long ngroups_max;
	gid_t *groups;

	/* Check for chown without being root. */
	if (errno != EPERM || (uid != (uid_t)-1 &&
	    euid == (uid_t)-1 && (euid = geteuid()) != 0)) {
		warn("%s", file);
		return;
	}

	/* Check group membership; kernel just returns EPERM. */
	if (gid != (gid_t)-1 && ngroups == -1 &&
	    euid == (uid_t)-1 && (euid = geteuid()) != 0) {
		ngroups_max = sysconf(_SC_NGROUPS_MAX) + 1;
		if ((groups = malloc(sizeof(gid_t) * ngroups_max)) == NULL)
			err(1, "malloc");
		ngroups = getgroups(ngroups_max, groups);
		while (--ngroups >= 0 && gid != groups[ngroups]);
		free(groups);
		if (ngroups < 0) {
			warnx("you are not a member of group %s", gname);
			return;
		}
	}
	warn("%s", file);
}