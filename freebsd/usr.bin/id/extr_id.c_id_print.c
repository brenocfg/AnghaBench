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
struct passwd {int pw_uid; int pw_gid; char* pw_name; } ;
struct group {char* gr_name; } ;
typedef  int gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int getegid () ; 
 int geteuid () ; 
 int getgid () ; 
 struct group* getgrgid (int) ; 
 int /*<<< orphan*/  getgrouplist (char*,int,int*,int*) ; 
 int getgroups (long,int*) ; 
 struct passwd* getpwuid (int) ; 
 int getuid () ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  printf (char const*,...) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
id_print(struct passwd *pw, int use_ggl, int p_euid, int p_egid)
{
	struct group *gr;
	gid_t gid, egid, lastgid;
	uid_t uid, euid;
	int cnt, ngroups;
	long ngroups_max;
	gid_t *groups;
	const char *fmt;

	if (pw != NULL) {
		uid = pw->pw_uid;
		gid = pw->pw_gid;
	}
	else {
		uid = getuid();
		gid = getgid();
	}

	ngroups_max = sysconf(_SC_NGROUPS_MAX) + 1;
	if ((groups = malloc(sizeof(gid_t) * ngroups_max)) == NULL)
		err(1, "malloc");

	if (use_ggl && pw != NULL) {
		ngroups = ngroups_max;
		getgrouplist(pw->pw_name, gid, groups, &ngroups);
	}
	else {
		ngroups = getgroups(ngroups_max, groups);
	}

	if (pw != NULL)
		printf("uid=%u(%s)", uid, pw->pw_name);
	else 
		printf("uid=%u", getuid());
	printf(" gid=%u", gid);
	if ((gr = getgrgid(gid)))
		(void)printf("(%s)", gr->gr_name);
	if (p_euid && (euid = geteuid()) != uid) {
		(void)printf(" euid=%u", euid);
		if ((pw = getpwuid(euid)))
			(void)printf("(%s)", pw->pw_name);
	}
	if (p_egid && (egid = getegid()) != gid) {
		(void)printf(" egid=%u", egid);
		if ((gr = getgrgid(egid)))
			(void)printf("(%s)", gr->gr_name);
	}
	fmt = " groups=%u";
	for (lastgid = -1, cnt = 0; cnt < ngroups; ++cnt) {
		if (lastgid == (gid = groups[cnt]))
			continue;
		printf(fmt, gid);
		fmt = ",%u";
		if ((gr = getgrgid(gid)))
			printf("(%s)", gr->gr_name);
		lastgid = gid;
	}
	printf("\n");
	free(groups);
}