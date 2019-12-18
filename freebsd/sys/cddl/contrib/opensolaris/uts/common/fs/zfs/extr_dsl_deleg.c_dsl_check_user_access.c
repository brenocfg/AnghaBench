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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int gid_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_DELEG_EVERYONE ; 
 int /*<<< orphan*/  ZFS_DELEG_GROUP ; 
 int /*<<< orphan*/  ZFS_DELEG_USER ; 
 int crgetgid (int /*<<< orphan*/ *) ; 
 int* crgetgroups (int /*<<< orphan*/ *) ; 
 int crgetngroups (int /*<<< orphan*/ *) ; 
 int crgetuid (int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_check_access (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int*,char const*) ; 

__attribute__((used)) static int
dsl_check_user_access(objset_t *mos, uint64_t zapobj, const char *perm,
    int checkflag, cred_t *cr)
{
	const	gid_t *gids;
	int	ngids;
	int	i;
	uint64_t id;

	/* check for user */
	id = crgetuid(cr);
	if (dsl_check_access(mos, zapobj,
	    ZFS_DELEG_USER, checkflag, &id, perm) == 0)
		return (0);

	/* check for users primary group */
	id = crgetgid(cr);
	if (dsl_check_access(mos, zapobj,
	    ZFS_DELEG_GROUP, checkflag, &id, perm) == 0)
		return (0);

	/* check for everyone entry */
	id = -1;
	if (dsl_check_access(mos, zapobj,
	    ZFS_DELEG_EVERYONE, checkflag, &id, perm) == 0)
		return (0);

	/* check each supplemental group user is a member of */
	ngids = crgetngroups(cr);
	gids = crgetgroups(cr);
	for (i = 0; i != ngids; i++) {
		id = gids[i];
		if (dsl_check_access(mos, zapobj,
		    ZFS_DELEG_GROUP, checkflag, &id, perm) == 0)
			return (0);
	}

	return (SET_ERROR(EPERM));
}