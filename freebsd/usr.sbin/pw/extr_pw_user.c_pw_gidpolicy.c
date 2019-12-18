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
typedef  int uid_t ;
struct userconf {int dummy; } ;
struct group {int gr_gid; int /*<<< orphan*/ ** gr_mem; } ;
typedef  int intmax_t ;
typedef  int gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENDGRENT () ; 
 struct group* GETGRGID (int) ; 
 struct group* GETGRNAM (char*) ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  SETGRENT () ; 
 int /*<<< orphan*/  groupadd (struct userconf*,char*,int,int /*<<< orphan*/ *,int,int,int,int) ; 
 int pw_checkid (char*,int /*<<< orphan*/ ) ; 
 void* pw_groupnext (struct userconf*,int) ; 

__attribute__((used)) static uid_t
pw_gidpolicy(struct userconf *cnf, char *grname, char *nam, gid_t prefer, bool dryrun)
{
	struct group   *grp;
	gid_t           gid = (uid_t) - 1;

	/*
	 * Check the given gid, if any
	 */
	SETGRENT();
	if (grname) {
		if ((grp = GETGRNAM(grname)) == NULL) {
			gid = pw_checkid(grname, GID_MAX);
			grp = GETGRGID(gid);
		}
		gid = grp->gr_gid;
	} else if ((grp = GETGRNAM(nam)) != NULL &&
	    (grp->gr_mem == NULL || grp->gr_mem[0] == NULL)) {
		gid = grp->gr_gid;  /* Already created? Use it anyway... */
	} else {
		intmax_t		grid = -1;

		/*
		 * We need to auto-create a group with the user's name. We
		 * can send all the appropriate output to our sister routine
		 * bit first see if we can create a group with gid==uid so we
		 * can keep the user and group ids in sync. We purposely do
		 * NOT check the gid range if we can force the sync. If the
		 * user's name dups an existing group, then the group add
		 * function will happily handle that case for us and exit.
		 */
		if (GETGRGID(prefer) == NULL)
			grid = prefer;
		if (dryrun) {
			gid = pw_groupnext(cnf, true);
		} else {
			if (grid == -1)
				grid =  pw_groupnext(cnf, true);
			groupadd(cnf, nam, grid, NULL, -1, false, false, false);
			if ((grp = GETGRNAM(nam)) != NULL)
				gid = grp->gr_gid;
		}
	}
	ENDGRENT();
	return (gid);
}