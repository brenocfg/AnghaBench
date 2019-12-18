#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct group {scalar_t__ gr_gid; char** gr_mem; char* gr_passwd; } ;
typedef  scalar_t__ gid_t ;
struct TYPE_2__ {scalar_t__ pw_gid; char* pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_END ; 
 int /*<<< orphan*/  PRIV_START ; 
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 char* crypt (char*,char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ getegid () ; 
 struct group* getgrgid (scalar_t__) ; 
 struct group* getgrnam (char const*) ; 
 int getgroups (long,scalar_t__*) ; 
 char* getpass (char*) ; 
 scalar_t__ getuid () ; 
 scalar_t__ inarray (scalar_t__,scalar_t__*,int) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 TYPE_1__* pwd ; 
 scalar_t__ setgid (scalar_t__) ; 
 scalar_t__ setgroups (int,scalar_t__ const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 long strtol (char const*,char**,int) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
addgroup(const char *grpname)
{
	gid_t *grps;
	long lgid, ngrps_max;
	int dbmember, i, ngrps;
	gid_t egid;
	struct group *grp;
	char *ep, *pass, *cryptpw;
	char **p;

	egid = getegid();

	/* Try it as a group name, then a group id. */
	if ((grp = getgrnam(grpname)) == NULL)
		if ((lgid = strtol(grpname, &ep, 10)) <= 0 || *ep != '\0' ||
		    (grp = getgrgid((gid_t)lgid)) == NULL ) {
			warnx("%s: bad group name", grpname);
			return;
		}

	/*
	 * If the user is not a member of the requested group and the group
	 * has a password, prompt and check it.
	 */
	dbmember = 0;
	if (pwd->pw_gid == grp->gr_gid)
		dbmember = 1;
	for (p = grp->gr_mem; *p != NULL; p++)
		if (strcmp(*p, pwd->pw_name) == 0) {
			dbmember = 1;
			break;
		}
	if (!dbmember && *grp->gr_passwd != '\0' && getuid() != 0) {
		pass = getpass("Password:");
		if (pass == NULL)
			return;
		cryptpw = crypt(pass, grp->gr_passwd);
		if (cryptpw == NULL || strcmp(grp->gr_passwd, cryptpw) != 0) {
			fprintf(stderr, "Sorry\n");
			return;
		}
	}

	ngrps_max = sysconf(_SC_NGROUPS_MAX) + 1;
	if ((grps = malloc(sizeof(gid_t) * ngrps_max)) == NULL)
		err(1, "malloc");
	if ((ngrps = getgroups(ngrps_max, (gid_t *)grps)) < 0) {
		warn("getgroups");
		goto end;
	}

	/* Remove requested gid from supp. list if it exists. */
	if (grp->gr_gid != egid && inarray(grp->gr_gid, grps, ngrps)) {
		for (i = 0; i < ngrps; i++)
			if (grps[i] == grp->gr_gid)
				break;
		ngrps--;
		memmove(&grps[i], &grps[i + 1], (ngrps - i) * sizeof(gid_t));
		PRIV_START;
		if (setgroups(ngrps, (const gid_t *)grps) < 0) {
			PRIV_END;
			warn("setgroups");
			goto end;
		}
		PRIV_END;
	}

	PRIV_START;
	if (setgid(grp->gr_gid)) {
		PRIV_END;
		warn("setgid");
		goto end;
	}
	PRIV_END;
	grps[0] = grp->gr_gid;

	/* Add old effective gid to supp. list if it does not exist. */
	if (egid != grp->gr_gid && !inarray(egid, grps, ngrps)) {
		if (ngrps == ngrps_max)
			warnx("too many groups");
		else {
			grps[ngrps++] = egid;
			PRIV_START;
			if (setgroups(ngrps, (const gid_t *)grps)) {
				PRIV_END;
				warn("setgroups");
				goto end;
			}
			PRIV_END;
		}
	}
end:
	free(grps);
}