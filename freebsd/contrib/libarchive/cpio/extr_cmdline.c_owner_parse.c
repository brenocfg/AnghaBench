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
struct passwd {int pw_uid; int pw_gid; } ;
struct group {int gr_gid; } ;
typedef  int /*<<< orphan*/  errbuff ;

/* Variables and functions */
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 struct group* getgrnam (char const*) ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

const char *
owner_parse(const char *spec, int *uid, int *gid)
{
	static char errbuff[128];
	const char *u, *ue, *g;

	*uid = -1;
	*gid = -1;

	if (spec[0] == '\0')
		return ("Invalid empty user/group spec");

	/*
	 * Split spec into [user][:.][group]
	 *  u -> first char of username, NULL if no username
	 *  ue -> first char after username (colon, period, or \0)
	 *  g -> first char of group name
	 */
	if (*spec == ':' || *spec == '.') {
		/* If spec starts with ':' or '.', then just group. */
		ue = u = NULL;
		g = spec + 1;
	} else {
		/* Otherwise, [user] or [user][:] or [user][:][group] */
		ue = u = spec;
		while (*ue != ':' && *ue != '.' && *ue != '\0')
			++ue;
		g = ue;
		if (*g != '\0') /* Skip : or . to find first char of group. */
			++g;
	}

	if (u != NULL) {
		/* Look up user: ue is first char after end of user. */
		char *user;
		struct passwd *pwent;

		user = (char *)malloc(ue - u + 1);
		if (user == NULL)
			return ("Couldn't allocate memory");
		memcpy(user, u, ue - u);
		user[ue - u] = '\0';
		if ((pwent = getpwnam(user)) != NULL) {
			*uid = pwent->pw_uid;
			if (*ue != '\0')
				*gid = pwent->pw_gid;
		} else {
			char *end;
			errno = 0;
			*uid = (int)strtoul(user, &end, 10);
			if (errno || *end != '\0') {
				snprintf(errbuff, sizeof(errbuff),
				    "Couldn't lookup user ``%s''", user);
				errbuff[sizeof(errbuff) - 1] = '\0';
				free(user);
				return (errbuff);
			}
		}
		free(user);
	}

	if (*g != '\0') {
		struct group *grp;
		if ((grp = getgrnam(g)) != NULL) {
			*gid = grp->gr_gid;
		} else {
			char *end;
			errno = 0;
			*gid = (int)strtoul(g, &end, 10);
			if (errno || *end != '\0') {
				snprintf(errbuff, sizeof(errbuff),
				    "Couldn't lookup group ``%s''", g);
				errbuff[sizeof(errbuff) - 1] = '\0';
				return (errbuff);
			}
		}
	}
	return (NULL);
}