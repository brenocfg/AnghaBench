#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {char* pw_dir; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lc_class; int /*<<< orphan*/ * lc_cap; int /*<<< orphan*/ * lc_style; } ;
typedef  TYPE_1__ login_cap_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 char* LOGIN_DEFCLASS ; 
 char* LOGIN_MECLASS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MAXPATHLEN ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 char* _FILE_LOGIN_CONF ; 
 int _secure_path (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cgetent (int /*<<< orphan*/ **,char**,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  lc_object_count ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int) ; 
 char* path_login_conf ; 
 int /*<<< orphan*/  setegid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seteuid (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char const*,char const*,...) ; 

login_cap_t *
login_getclassbyname(char const *name, const struct passwd *pwd)
{
    login_cap_t	*lc;
  
    if ((lc = malloc(sizeof(login_cap_t))) != NULL) {
	int         r, me, i = 0;
	uid_t euid = 0;
	gid_t egid = 0;
	const char  *msg = NULL;
	const char  *dir;
	char	    userpath[MAXPATHLEN];

	static char *login_dbarray[] = { NULL, NULL, NULL };

	me = (name != NULL && strcmp(name, LOGIN_MECLASS) == 0);
	dir = (!me || pwd == NULL) ? NULL : pwd->pw_dir;
	/*
	 * Switch to user mode before checking/reading its ~/.login_conf
	 * - some NFSes have root read access disabled.
	 *
	 * XXX: This fails to configure additional groups.
	 */
	if (dir) {
	    euid = geteuid();
	    egid = getegid();
	    (void)setegid(pwd->pw_gid);
	    (void)seteuid(pwd->pw_uid);
	}

	if (dir && snprintf(userpath, MAXPATHLEN, "%s/%s", dir,
			    _FILE_LOGIN_CONF) < MAXPATHLEN) {
	    if (_secure_path(userpath, pwd->pw_uid, pwd->pw_gid) != -1)
		login_dbarray[i++] = userpath;
	}
	/*
	 * XXX: Why to add the system database if the class is `me'?
	 */
	if (_secure_path(path_login_conf, 0, 0) != -1)
	    login_dbarray[i++] = path_login_conf;
	login_dbarray[i] = NULL;

	memset(lc, 0, sizeof(login_cap_t));
	lc->lc_cap = lc->lc_class = lc->lc_style = NULL;

	if (name == NULL || *name == '\0')
	    name = LOGIN_DEFCLASS;

	switch (cgetent(&lc->lc_cap, login_dbarray, name)) {
	case -1:		/* Failed, entry does not exist */
	    if (me)
		break;	/* Don't retry default on 'me' */
	    if (i == 0)
	        r = -1;
	    else if ((r = open(login_dbarray[0], O_RDONLY | O_CLOEXEC)) >= 0)
	        close(r);
	    /*
	     * If there's at least one login class database,
	     * and we aren't searching for a default class
	     * then complain about a non-existent class.
	     */
	    if (r >= 0 || strcmp(name, LOGIN_DEFCLASS) != 0)
		syslog(LOG_ERR, "login_getclass: unknown class '%s'", name);
	    /* fall-back to default class */
	    name = LOGIN_DEFCLASS;
	    msg = "%s: no default/fallback class '%s'";
	    if (cgetent(&lc->lc_cap, login_dbarray, name) != 0 && r >= 0)
		break;
	    /* FALLTHROUGH - just return system defaults */
	case 0:		/* success! */
	    if ((lc->lc_class = strdup(name)) != NULL) {
		if (dir) {
		    (void)seteuid(euid);
		    (void)setegid(egid);
		}
		++lc_object_count;
		return lc;
	    }
	    msg = "%s: strdup: %m";
	    break;
	case -2:
	    msg = "%s: retrieving class information: %m";
	    break;
	case -3:
	    msg = "%s: 'tc=' reference loop '%s'";
	    break;
	case 1:
	    msg = "couldn't resolve 'tc=' reference in '%s'";
	    break;
	default:
	    msg = "%s: unexpected cgetent() error '%s': %m";
	    break;
	}
	if (dir) {
	    (void)seteuid(euid);
	    (void)setegid(egid);
	}
	if (msg != NULL)
	    syslog(LOG_ERR, msg, "login_getclass", name);
	free(lc);
    }

    return NULL;
}