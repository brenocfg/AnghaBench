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
struct xucred {int cr_uid; int* cr_groups; int cr_ngroups; int /*<<< orphan*/  cr_version; } ;
struct passwd {int pw_uid; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_name; } ;
struct group {int gr_gid; } ;
typedef  void* gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  XUCRED_VERSION ; 
 int XU_NGROUPS ; 
 void* atoi (char*) ; 
 struct group* getgrnam (char*) ; 
 scalar_t__ getgrouplist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int*) ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (void*) ; 
 scalar_t__ isdigit (char) ; 
 char* strsep_quote (char**,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
parsecred(char *namelist, struct xucred *cr)
{
	char *name;
	int cnt;
	char *names;
	struct passwd *pw;
	struct group *gr;
	gid_t groups[XU_NGROUPS + 1];
	int ngroups;

	cr->cr_version = XUCRED_VERSION;
	/*
	 * Set up the unprivileged user.
	 */
	cr->cr_uid = 65534;
	cr->cr_groups[0] = 65533;
	cr->cr_ngroups = 1;
	/*
	 * Get the user's password table entry.
	 */
	names = namelist;
	name = strsep_quote(&names, ":");
	/* Bug?  name could be NULL here */
	if (isdigit(*name) || *name == '-')
		pw = getpwuid(atoi(name));
	else
		pw = getpwnam(name);
	/*
	 * Credentials specified as those of a user.
	 */
	if (names == NULL) {
		if (pw == NULL) {
			syslog(LOG_ERR, "unknown user: %s", name);
			return;
		}
		cr->cr_uid = pw->pw_uid;
		ngroups = XU_NGROUPS + 1;
		if (getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups)) {
			syslog(LOG_ERR, "too many groups");
			ngroups = XU_NGROUPS + 1;
		}

		/*
		 * Compress out duplicate.
		 */
		cr->cr_ngroups = ngroups - 1;
		cr->cr_groups[0] = groups[0];
		for (cnt = 2; cnt < ngroups; cnt++)
			cr->cr_groups[cnt - 1] = groups[cnt];
		return;
	}
	/*
	 * Explicit credential specified as a colon separated list:
	 *	uid:gid:gid:...
	 */
	if (pw != NULL)
		cr->cr_uid = pw->pw_uid;
	else if (isdigit(*name) || *name == '-')
		cr->cr_uid = atoi(name);
	else {
		syslog(LOG_ERR, "unknown user: %s", name);
		return;
	}
	cr->cr_ngroups = 0;
	while (names != NULL && *names != '\0' && cr->cr_ngroups < XU_NGROUPS) {
		name = strsep_quote(&names, ":");
		if (isdigit(*name) || *name == '-') {
			cr->cr_groups[cr->cr_ngroups++] = atoi(name);
		} else {
			if ((gr = getgrnam(name)) == NULL) {
				syslog(LOG_ERR, "unknown group: %s", name);
				continue;
			}
			cr->cr_groups[cr->cr_ngroups++] = gr->gr_gid;
		}
	}
	if (names != NULL && *names != '\0' && cr->cr_ngroups == XU_NGROUPS)
		syslog(LOG_ERR, "too many groups");
}