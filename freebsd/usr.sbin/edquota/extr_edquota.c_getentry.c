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
struct passwd {int pw_uid; } ;
struct group {int gr_gid; } ;

/* Variables and functions */
#define  GRPQUOTA 129 
#define  USRQUOTA 128 
 scalar_t__ alldigits (char const*) ; 
 int atoi (char const*) ; 
 struct group* getgrnam (char const*) ; 
 struct passwd* getpwnam (char const*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
getentry(const char *name, int quotatype)
{
	struct passwd *pw;
	struct group *gr;

	if (alldigits(name))
		return (atoi(name));
	switch(quotatype) {
	case USRQUOTA:
		if ((pw = getpwnam(name)))
			return (pw->pw_uid);
		warnx("%s: no such user", name);
		sleep(3);
		break;
	case GRPQUOTA:
		if ((gr = getgrnam(name)))
			return (gr->gr_gid);
		warnx("%s: no such group", name);
		sleep(3);
		break;
	default:
		warnx("%d: unknown quota type", quotatype);
		sleep(3);
		break;
	}
	sleep(1);
	return (-1);
}