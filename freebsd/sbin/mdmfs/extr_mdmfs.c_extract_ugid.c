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
struct passwd {scalar_t__ pw_uid; } ;
struct mtpt_info {scalar_t__ mi_uid; scalar_t__ mi_gid; int mi_have_uid; int mi_have_gid; } ;
struct group {scalar_t__ gr_gid; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct group* getgrnam (char*) ; 
 struct passwd* getpwnam (char*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
extract_ugid(const char *str, struct mtpt_info *mip)
{
	char *ug;			/* Writable 'str'. */
	char *user, *group;		/* Result of extracton. */
	struct passwd *pw;
	struct group *gr;
	char *p;
	uid_t *uid;
	gid_t *gid;

	uid = &mip->mi_uid;
	gid = &mip->mi_gid;
	mip->mi_have_uid = mip->mi_have_gid = false;

	/* Extract the user and group from 'str'.  Format above. */
	ug = strdup(str);
	assert(ug != NULL);
	group = ug;
	user = strsep(&group, ":");
	if (user == NULL || group == NULL || *user == '\0' || *group == '\0')
		usage();

	/* Derive uid. */
	*uid = strtoul(user, &p, 10);
	if (*uid == (uid_t)ULONG_MAX)
		usage();
	if (*p != '\0') {
		pw = getpwnam(user);
		if (pw == NULL)
			errx(1, "invalid user: %s", user);
		*uid = pw->pw_uid;
	}
	mip->mi_have_uid = true;

	/* Derive gid. */
	*gid = strtoul(group, &p, 10);
	if (*gid == (gid_t)ULONG_MAX)
		usage();
	if (*p != '\0') {
		gr = getgrnam(group);
		if (gr == NULL)
			errx(1, "invalid group: %s", group);
		*gid = gr->gr_gid;
	}
	mip->mi_have_gid = true;

	free(ug);
}