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
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_name; } ;
struct group {int /*<<< orphan*/  gr_name; } ;
typedef  int gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 struct group* getgrgid (int) ; 
 int /*<<< orphan*/  getgrouplist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int getgroups (long,int*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  printf (char const*,...) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
group(struct passwd *pw, int nflag)
{
	struct group *gr;
	int cnt, id, lastid, ngroups;
	long ngroups_max;
	gid_t *groups;
	const char *fmt;

	ngroups_max = sysconf(_SC_NGROUPS_MAX) + 1;
	if ((groups = malloc(sizeof(gid_t) * (ngroups_max))) == NULL)
		err(1, "malloc");

	if (pw) {
		ngroups = ngroups_max;
		(void) getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);
	} else {
		ngroups = getgroups(ngroups_max, groups);
	}
	fmt = nflag ? "%s" : "%u";
	for (lastid = -1, cnt = 0; cnt < ngroups; ++cnt) {
		if (lastid == (id = groups[cnt]))
			continue;
		if (nflag) {
			if ((gr = getgrgid(id)))
				(void)printf(fmt, gr->gr_name);
			else
				(void)printf(*fmt == ' ' ? " %u" : "%u",
				    id);
			fmt = " %s";
		} else {
			(void)printf(fmt, id);
			fmt = " %u";
		}
		lastid = id;
	}
	(void)printf("\n");
	free(groups);
}