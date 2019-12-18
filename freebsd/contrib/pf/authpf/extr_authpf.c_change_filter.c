#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  PATH_PFCTL ; 
 int /*<<< orphan*/  PATH_PFRULES ; 
 int /*<<< orphan*/  PATH_USER_DIR ; 
 TYPE_1__ Tend ; 
 TYPE_1__ Tstart ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  anchorname ; 
 int asprintf (char**,char*,char const*,...) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  gettimeofday (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_stale_rulesets () ; 
 char const* rulesetname ; 
 int setregid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ user_ip ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
change_filter(int add, const char *l_user, const char *ip_src)
{
	char	*fdpath = NULL, *userstr = NULL, *ipstr = NULL;
	char	*rsn = NULL, *fn = NULL;
	pid_t	pid;
	gid_t   gid;
	int	s;

	if (add) {
		struct stat sb;
		char *pargv[13] = {
			"pfctl", "-p", "/dev/pf", "-q", "-a", "anchor/ruleset",
			"-D", "user_id=X", "-D", "user_ip=X", "-f", "file", NULL
		};

		if (l_user == NULL || !l_user[0] || ip_src == NULL || !ip_src[0]) {
			syslog(LOG_ERR, "invalid luser/ipsrc");
			goto error;
		}

		if (asprintf(&rsn, "%s/%s", anchorname, rulesetname) == -1)
			goto no_mem;
		if (asprintf(&fdpath, "/dev/fd/%d", dev) == -1)
			goto no_mem;
		if (asprintf(&ipstr, "user_ip=%s", ip_src) == -1)
			goto no_mem;
		if (asprintf(&userstr, "user_id=%s", l_user) == -1)
			goto no_mem;
		if (asprintf(&fn, "%s/%s/authpf.rules",
		    PATH_USER_DIR, l_user) == -1)
			goto no_mem;
		if (stat(fn, &sb) == -1) {
			free(fn);
			if ((fn = strdup(PATH_PFRULES)) == NULL)
				goto no_mem;
		}
		pargv[2] = fdpath;
		pargv[5] = rsn;
		pargv[7] = userstr;
		if (user_ip) {
			pargv[9] = ipstr;
			pargv[11] = fn;
		} else {
			pargv[8] = "-f";
			pargv[9] = fn;
			pargv[10] = NULL;
		}

		switch (pid = fork()) {
		case -1:
			syslog(LOG_ERR, "fork failed");
			goto error;
		case 0:
			/* revoke group privs before exec */
			gid = getgid();
			if (setregid(gid, gid) == -1) {
				err(1, "setregid");
			}
			execvp(PATH_PFCTL, pargv);
			warn("exec of %s failed", PATH_PFCTL);
			_exit(1);
		}

		/* parent */
		waitpid(pid, &s, 0);
		if (s != 0) {
			syslog(LOG_ERR, "pfctl exited abnormally");
			goto error;
		}

		gettimeofday(&Tstart, NULL);
		syslog(LOG_INFO, "allowing %s, user %s", ip_src, l_user);
	} else {
		remove_stale_rulesets();

		gettimeofday(&Tend, NULL);
		syslog(LOG_INFO, "removed %s, user %s - duration %ju seconds",
		    ip_src, l_user, (uintmax_t)(Tend.tv_sec - Tstart.tv_sec));
	}
	return (0);
no_mem:
	syslog(LOG_ERR, "malloc failed");
error:
	free(fdpath);
	free(rsn);
	free(userstr);
	free(ipstr);
	free(fn);
	return (-1);
}