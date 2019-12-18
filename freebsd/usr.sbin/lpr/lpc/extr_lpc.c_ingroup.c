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
struct group {scalar_t__ gr_gid; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct group* getgrnam (char const*) ; 
 int getgroups (long,scalar_t__*) ; 
 scalar_t__* malloc (int) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
ingroup(const char *grname)
{
	static struct group *gptr=NULL;
	static int ngroups = 0;
	static long ngroups_max;
	static gid_t *groups;
	register gid_t gid;
	register int i;

	if (gptr == NULL) {
		if ((gptr = getgrnam(grname)) == NULL) {
			warnx("warning: unknown group '%s'", grname);
			return(0);
		}
		ngroups_max = sysconf(_SC_NGROUPS_MAX);
		if ((groups = malloc(sizeof(gid_t) * ngroups_max)) == NULL)
			err(1, "malloc");
		ngroups = getgroups(ngroups_max, groups);
		if (ngroups < 0)
			err(1, "getgroups");
	}
	gid = gptr->gr_gid;
	for (i = 0; i < ngroups; i++)
		if (gid == groups[i])
			return(1);
	return(0);
}