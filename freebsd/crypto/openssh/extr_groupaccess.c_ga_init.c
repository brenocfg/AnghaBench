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
struct group {int /*<<< orphan*/  gr_name; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int MAX (int,int /*<<< orphan*/ ) ; 
 int NGROUPS_MAX ; 
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ga_free () ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 int getgrouplist (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * groups_byname ; 
 int /*<<< orphan*/  logit (char*) ; 
 int ngroups ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 
 void* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

int
ga_init(const char *user, gid_t base)
{
	gid_t *groups_bygid;
	int i, j;
	struct group *gr;

	if (ngroups > 0)
		ga_free();

	ngroups = NGROUPS_MAX;
#if defined(HAVE_SYSCONF) && defined(_SC_NGROUPS_MAX)
	ngroups = MAX(NGROUPS_MAX, sysconf(_SC_NGROUPS_MAX));
#endif

	groups_bygid = xcalloc(ngroups, sizeof(*groups_bygid));
	groups_byname = xcalloc(ngroups, sizeof(*groups_byname));

	if (getgrouplist(user, base, groups_bygid, &ngroups) == -1)
		logit("getgrouplist: groups list too small");
	for (i = 0, j = 0; i < ngroups; i++)
		if ((gr = getgrgid(groups_bygid[i])) != NULL)
			groups_byname[j++] = xstrdup(gr->gr_name);
	free(groups_bygid);
	return (ngroups = j);
}