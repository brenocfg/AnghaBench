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
typedef  void* uid_t ;
struct passwd {char* pw_name; char* pw_shell; int /*<<< orphan*/  pw_fields; scalar_t__* pw_dir; scalar_t__* pw_gecos; void* pw_expire; void* pw_change; scalar_t__* pw_class; void* pw_gid; void* pw_uid; scalar_t__* pw_passwd; } ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 unsigned long GID_MAX ; 
 unsigned long UID_MAX ; 
 unsigned long ULONG_MAX ; 
 void* USHRT_MAX ; 
 int /*<<< orphan*/  _PWF_CHANGE ; 
 int /*<<< orphan*/  _PWF_CLASS ; 
 int /*<<< orphan*/  _PWF_DIR ; 
 int /*<<< orphan*/  _PWF_EXPIRE ; 
 int /*<<< orphan*/  _PWF_GECOS ; 
 int /*<<< orphan*/  _PWF_GID ; 
 int /*<<< orphan*/  _PWF_NAME ; 
 int /*<<< orphan*/  _PWF_PASSWD ; 
 int /*<<< orphan*/  _PWF_SHELL ; 
 int /*<<< orphan*/  _PWF_UID ; 
 int _PWSCAN_MASTER ; 
 int _PWSCAN_WARN ; 
 void* atol (char*) ; 
 int /*<<< orphan*/  endusershell () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 char* getusershell () ; 
 int pw_big_ids_warning ; 
 int /*<<< orphan*/  setusershell () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strsep (char**,char*) ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
__pw_scan(char *bp, struct passwd *pw, int flags)
{
	uid_t id;
	int root;
	char *ep, *p, *sh;
	unsigned long temp;

	if (pw_big_ids_warning == -1)
		pw_big_ids_warning = getenv("PW_SCAN_BIG_IDS") == NULL ? 1 : 0;

	pw->pw_fields = 0;
	if (!(pw->pw_name = strsep(&bp, ":")))		/* login */
		goto fmt;
	root = !strcmp(pw->pw_name, "root");
	if (pw->pw_name[0] && (pw->pw_name[0] != '+' || pw->pw_name[1] == '\0'))
		pw->pw_fields |= _PWF_NAME;

	if (!(pw->pw_passwd = strsep(&bp, ":")))	/* passwd */
		goto fmt;
	if (pw->pw_passwd[0])
		pw->pw_fields |= _PWF_PASSWD;

	if (!(p = strsep(&bp, ":")))			/* uid */
		goto fmt;
	if (p[0])
		pw->pw_fields |= _PWF_UID;
	else {
		if (pw->pw_name[0] != '+' && pw->pw_name[0] != '-') {
			if (flags & _PWSCAN_WARN)
				warnx("no uid for user %s", pw->pw_name);
			return (0);
		}
	}
	errno = 0;
	temp = strtoul(p, &ep, 10);
	if ((temp == ULONG_MAX && errno == ERANGE) || temp > UID_MAX) {
		if (flags & _PWSCAN_WARN)
			warnx("%s > max uid value (%u)", p, UID_MAX);
		return (0);
	}
	id = temp;
	if (*ep != '\0') {
		if (flags & _PWSCAN_WARN)
			warnx("%s uid is incorrect", p);
		return (0);
	}
	if (root && id) {
		if (flags & _PWSCAN_WARN)
			warnx("root uid should be 0");
		return (0);
	}
	if (flags & _PWSCAN_WARN && pw_big_ids_warning && id > USHRT_MAX) {
		warnx("%s > recommended max uid value (%u)", p, USHRT_MAX);
		/*return (0);*/ /* THIS SHOULD NOT BE FATAL! */
	}
	pw->pw_uid = id;

	if (!(p = strsep(&bp, ":")))			/* gid */
		goto fmt;
	if (p[0])
		pw->pw_fields |= _PWF_GID;
	else {
		if (pw->pw_name[0] != '+' && pw->pw_name[0] != '-') {
			if (flags & _PWSCAN_WARN)
				warnx("no gid for user %s", pw->pw_name);
			return (0);
		}
	}
	errno = 0;
	temp = strtoul(p, &ep, 10);
	if ((temp == ULONG_MAX && errno == ERANGE) || temp > GID_MAX) {
		if (flags & _PWSCAN_WARN)
			warnx("%s > max gid value (%u)", p, GID_MAX);
		return (0);
	}
	id = temp;
	if (*ep != '\0') {
		if (flags & _PWSCAN_WARN)
			warnx("%s gid is incorrect", p);
		return (0);
	}
	if (flags & _PWSCAN_WARN && pw_big_ids_warning && id > USHRT_MAX) {
		warnx("%s > recommended max gid value (%u)", p, USHRT_MAX);
		/* return (0); This should not be fatal! */
	}
	pw->pw_gid = id;

	if (flags & _PWSCAN_MASTER ) {
		if (!(pw->pw_class = strsep(&bp, ":")))	/* class */
			goto fmt;
		if (pw->pw_class[0])
			pw->pw_fields |= _PWF_CLASS;
		
		if (!(p = strsep(&bp, ":")))		/* change */
			goto fmt;
		if (p[0])
			pw->pw_fields |= _PWF_CHANGE;
		pw->pw_change = atol(p);
		
		if (!(p = strsep(&bp, ":")))		/* expire */
			goto fmt;
		if (p[0])
			pw->pw_fields |= _PWF_EXPIRE;
		pw->pw_expire = atol(p);
	}
	if (!(pw->pw_gecos = strsep(&bp, ":")))		/* gecos */
		goto fmt;
	if (pw->pw_gecos[0])
		pw->pw_fields |= _PWF_GECOS;

	if (!(pw->pw_dir = strsep(&bp, ":")))		/* directory */
		goto fmt;
	if (pw->pw_dir[0])
		pw->pw_fields |= _PWF_DIR;

	if (!(pw->pw_shell = strsep(&bp, ":")))		/* shell */
		goto fmt;

	p = pw->pw_shell;
	if (root && *p) {				/* empty == /bin/sh */
		for (setusershell();;) {
			if (!(sh = getusershell())) {
				if (flags & _PWSCAN_WARN)
					warnx("warning, unknown root shell");
				break;
			}
			if (!strcmp(p, sh))
				break;
		}
		endusershell();
	}
	if (p[0])
		pw->pw_fields |= _PWF_SHELL;

	if ((p = strsep(&bp, ":"))) {			/* too many */
fmt:		
		if (flags & _PWSCAN_WARN)
			warnx("corrupted entry");
		return (0);
	}
	return (1);
}