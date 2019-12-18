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
typedef  int /*<<< orphan*/  u_int ;
struct passwd {scalar_t__ pw_uid; scalar_t__ pw_gid; int /*<<< orphan*/  pw_name; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 void* getgroups (int,int /*<<< orphan*/ *) ; 
 scalar_t__ initgroups (int /*<<< orphan*/ ,scalar_t__) ; 
 int privileged ; 
 scalar_t__ saved_egid ; 
 int /*<<< orphan*/ * saved_egroups ; 
 scalar_t__ saved_egroupslen ; 
 scalar_t__ saved_euid ; 
 scalar_t__ setegid (scalar_t__) ; 
 int seteuid (scalar_t__) ; 
 scalar_t__ setgid (scalar_t__) ; 
 scalar_t__ setgroups (int,int /*<<< orphan*/ *) ; 
 scalar_t__ setuid (scalar_t__) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int temporarily_use_uid_effective ; 
 int /*<<< orphan*/ * user_groups ; 
 scalar_t__ user_groups_uid ; 
 int user_groupslen ; 
 int /*<<< orphan*/ * xreallocarray (int /*<<< orphan*/ *,int,int) ; 

void
temporarily_use_uid(struct passwd *pw)
{
	/* Save the current euid, and egroups. */
#ifdef SAVED_IDS_WORK_WITH_SETEUID
	saved_euid = geteuid();
	saved_egid = getegid();
	debug("temporarily_use_uid: %u/%u (e=%u/%u)",
	    (u_int)pw->pw_uid, (u_int)pw->pw_gid,
	    (u_int)saved_euid, (u_int)saved_egid);
#ifndef HAVE_CYGWIN
	if (saved_euid != 0) {
		privileged = 0;
		return;
	}
#endif
#else
	if (geteuid() != 0) {
		privileged = 0;
		return;
	}
#endif /* SAVED_IDS_WORK_WITH_SETEUID */

	privileged = 1;
	temporarily_use_uid_effective = 1;

	saved_egroupslen = getgroups(0, NULL);
	if (saved_egroupslen < 0)
		fatal("getgroups: %.100s", strerror(errno));
	if (saved_egroupslen > 0) {
		saved_egroups = xreallocarray(saved_egroups,
		    saved_egroupslen, sizeof(gid_t));
		if (getgroups(saved_egroupslen, saved_egroups) < 0)
			fatal("getgroups: %.100s", strerror(errno));
	} else { /* saved_egroupslen == 0 */
		free(saved_egroups);
		saved_egroups = NULL;
	}

	/* set and save the user's groups */
	if (user_groupslen == -1 || user_groups_uid != pw->pw_uid) {
		if (initgroups(pw->pw_name, pw->pw_gid) < 0)
			fatal("initgroups: %s: %.100s", pw->pw_name,
			    strerror(errno));

		user_groupslen = getgroups(0, NULL);
		if (user_groupslen < 0)
			fatal("getgroups: %.100s", strerror(errno));
		if (user_groupslen > 0) {
			user_groups = xreallocarray(user_groups,
			    user_groupslen, sizeof(gid_t));
			if (getgroups(user_groupslen, user_groups) < 0)
				fatal("getgroups: %.100s", strerror(errno));
		} else { /* user_groupslen == 0 */
			free(user_groups);
			user_groups = NULL;
		}
		user_groups_uid = pw->pw_uid;
	}
	/* Set the effective uid to the given (unprivileged) uid. */
	if (setgroups(user_groupslen, user_groups) < 0)
		fatal("setgroups: %.100s", strerror(errno));
#ifndef SAVED_IDS_WORK_WITH_SETEUID
	/* Propagate the privileged gid to all of our gids. */
	if (setgid(getegid()) < 0)
		debug("setgid %u: %.100s", (u_int) getegid(), strerror(errno));
	/* Propagate the privileged uid to all of our uids. */
	if (setuid(geteuid()) < 0)
		debug("setuid %u: %.100s", (u_int) geteuid(), strerror(errno));
#endif /* SAVED_IDS_WORK_WITH_SETEUID */
	if (setegid(pw->pw_gid) < 0)
		fatal("setegid %u: %.100s", (u_int)pw->pw_gid,
		    strerror(errno));
	if (seteuid(pw->pw_uid) == -1)
		fatal("seteuid %u: %.100s", (u_int)pw->pw_uid,
		    strerror(errno));
}