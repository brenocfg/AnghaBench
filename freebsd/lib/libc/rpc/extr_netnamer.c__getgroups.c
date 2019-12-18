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
struct group {int gr_gid; scalar_t__* gr_mem; } ;
typedef  int gid_t ;

/* Variables and functions */
 int NGRPS ; 
 int /*<<< orphan*/  endgrent () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct group* getgrent () ; 
 int /*<<< orphan*/  setgrent () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int
_getgroups(char *uname, gid_t groups[NGRPS])
{
	gid_t           ngroups = 0;
	struct group *grp;
	int    i;
	int    j;
	int             filter;

	setgrent();
	while ((grp = getgrent())) {
		for (i = 0; grp->gr_mem[i]; i++)
			if (!strcmp(grp->gr_mem[i], uname)) {
				if (ngroups == NGRPS) {
#ifdef DEBUG
					fprintf(stderr,
				"initgroups: %s is in too many groups\n", uname);
#endif
					goto toomany;
				}
				/* filter out duplicate group entries */
				filter = 0;
				for (j = 0; j < ngroups; j++)
					if (groups[j] == grp->gr_gid) {
						filter++;
						break;
					}
				if (!filter)
					groups[ngroups++] = grp->gr_gid;
			}
	}
toomany:
	endgrent();
	return (ngroups);
}