#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  char* u_long ;
struct rtprio {scalar_t__ prio; int /*<<< orphan*/  type; } ;
struct passwd {char* pw_name; scalar_t__ pw_gid; } ;
typedef  scalar_t__ rlim_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  mac_t ;
struct TYPE_10__ {char* lc_class; } ;
typedef  TYPE_1__ login_cap_t ;
struct TYPE_11__ {int /*<<< orphan*/  def; } ;

/* Variables and functions */
 char* LOGIN_DEFCLASS ; 
 int /*<<< orphan*/  LOGIN_DEFPRI ; 
 int /*<<< orphan*/  LOGIN_DEFUMASK ; 
 unsigned int LOGIN_SETGROUP ; 
 unsigned int LOGIN_SETLOGIN ; 
 unsigned int LOGIN_SETLOGINCLASS ; 
 unsigned int LOGIN_SETMAC ; 
 unsigned int LOGIN_SETPATH ; 
 unsigned int LOGIN_SETPRIORITY ; 
 unsigned int LOGIN_SETUMASK ; 
 unsigned int LOGIN_SETUSER ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ PRIO_MAX ; 
 scalar_t__ PRIO_MIN ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  RTP_PRIO_IDLE ; 
 scalar_t__ RTP_PRIO_MAX ; 
 scalar_t__ RTP_PRIO_MIN ; 
 int /*<<< orphan*/  RTP_PRIO_REALTIME ; 
 int /*<<< orphan*/  RTP_SET ; 
 int /*<<< orphan*/  _PATH_DEFPATH ; 
 int /*<<< orphan*/  _PATH_STDPATH ; 
 int errno ; 
 scalar_t__ getuid () ; 
 int initgroups (char*,scalar_t__) ; 
 int /*<<< orphan*/  login_close (TYPE_1__*) ; 
 scalar_t__ login_getcapnum (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* login_getcapstr (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* login_getpwclass (struct passwd const*) ; 
 TYPE_1__* login_getuserclass (struct passwd const*) ; 
 int /*<<< orphan*/  mac_free (int /*<<< orphan*/ ) ; 
 int mac_from_text (int /*<<< orphan*/ *,char const*) ; 
 int mac_is_present (int /*<<< orphan*/ *) ; 
 int mac_set_proc (int /*<<< orphan*/ ) ; 
 TYPE_4__* pathvars ; 
 scalar_t__ rtprio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtprio*) ; 
 scalar_t__ setgid (scalar_t__) ; 
 scalar_t__ setlogin (char*) ; 
 int setloginclass (char*) ; 
 int /*<<< orphan*/  setlogincontext (TYPE_1__*,struct passwd const*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setuid (scalar_t__) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

int
setusercontext(login_cap_t *lc, const struct passwd *pwd, uid_t uid, unsigned int flags)
{
    rlim_t	p;
    mode_t	mymask;
    login_cap_t *llc = NULL;
    struct rtprio rtp;
    int error;

    if (lc == NULL) {
	if (pwd != NULL && (lc = login_getpwclass(pwd)) != NULL)
	    llc = lc; /* free this when we're done */
    }

    if (flags & LOGIN_SETPATH)
	pathvars[0].def = uid ? _PATH_DEFPATH : _PATH_STDPATH;

    /* we need a passwd entry to set these */
    if (pwd == NULL)
	flags &= ~(LOGIN_SETGROUP | LOGIN_SETLOGIN | LOGIN_SETMAC);

    /* Set the process priority */
    if (flags & LOGIN_SETPRIORITY) {
	p = login_getcapnum(lc, "priority", LOGIN_DEFPRI, LOGIN_DEFPRI);

	if (p > PRIO_MAX) {
	    rtp.type = RTP_PRIO_IDLE;
	    p -= PRIO_MAX + 1;
	    rtp.prio = p > RTP_PRIO_MAX ? RTP_PRIO_MAX : p;
	    if (rtprio(RTP_SET, 0, &rtp))
		syslog(LOG_WARNING, "rtprio '%s' (%s): %m",
		    pwd ? pwd->pw_name : "-",
		    lc ? lc->lc_class : LOGIN_DEFCLASS);
	} else if (p < PRIO_MIN) {
	    rtp.type = RTP_PRIO_REALTIME;
	    p -= PRIO_MIN - RTP_PRIO_MAX;
	    rtp.prio = p < RTP_PRIO_MIN ? RTP_PRIO_MIN : p;
	    if (rtprio(RTP_SET, 0, &rtp))
		syslog(LOG_WARNING, "rtprio '%s' (%s): %m",
		    pwd ? pwd->pw_name : "-",
		    lc ? lc->lc_class : LOGIN_DEFCLASS);
	} else {
	    if (setpriority(PRIO_PROCESS, 0, (int)p) != 0)
		syslog(LOG_WARNING, "setpriority '%s' (%s): %m",
		    pwd ? pwd->pw_name : "-",
		    lc ? lc->lc_class : LOGIN_DEFCLASS);
	}
    }

    /* Setup the user's group permissions */
    if (flags & LOGIN_SETGROUP) {
	if (setgid(pwd->pw_gid) != 0) {
	    syslog(LOG_ERR, "setgid(%lu): %m", (u_long)pwd->pw_gid);
	    login_close(llc);
	    return (-1);
	}
	if (initgroups(pwd->pw_name, pwd->pw_gid) == -1) {
	    syslog(LOG_ERR, "initgroups(%s,%lu): %m", pwd->pw_name,
		   (u_long)pwd->pw_gid);
	    login_close(llc);
	    return (-1);
	}
    }

    /* Set up the user's MAC label. */
    if ((flags & LOGIN_SETMAC) && mac_is_present(NULL) == 1) {
	const char *label_string;
	mac_t label;

	label_string = login_getcapstr(lc, "label", NULL, NULL);
	if (label_string != NULL) {
	    if (mac_from_text(&label, label_string) == -1) {
		syslog(LOG_ERR, "mac_from_text('%s') for %s: %m",
		    pwd->pw_name, label_string);
		return (-1);
	    }
	    if (mac_set_proc(label) == -1)
		error = errno;
	    else
		error = 0;
	    mac_free(label);
	    if (error != 0) {
		syslog(LOG_ERR, "mac_set_proc('%s') for %s: %s",
		    label_string, pwd->pw_name, strerror(error));
		return (-1);
	    }
	}
    }

    /* Set the sessions login */
    if ((flags & LOGIN_SETLOGIN) && setlogin(pwd->pw_name) != 0) {
	syslog(LOG_ERR, "setlogin(%s): %m", pwd->pw_name);
	login_close(llc);
	return (-1);
    }

    /* Inform the kernel about current login class */
    if (lc != NULL && lc->lc_class != NULL && (flags & LOGIN_SETLOGINCLASS)) {
	error = setloginclass(lc->lc_class);
	if (error != 0) {
	    syslog(LOG_ERR, "setloginclass(%s): %m", lc->lc_class);
#ifdef notyet
	    login_close(llc);
	    return (-1);
#endif
	}
    }

    mymask = (flags & LOGIN_SETUMASK) ? umask(LOGIN_DEFUMASK) : 0;
    mymask = setlogincontext(lc, pwd, mymask, flags);
    login_close(llc);

    /* This needs to be done after anything that needs root privs */
    if ((flags & LOGIN_SETUSER) && setuid(uid) != 0) {
	syslog(LOG_ERR, "setuid(%lu): %m", (u_long)uid);
	return (-1);	/* Paranoia again */
    }

    /*
     * Now, we repeat some of the above for the user's private entries
     */
    if (getuid() == uid && (lc = login_getuserclass(pwd)) != NULL) {
	mymask = setlogincontext(lc, pwd, mymask, flags);
	login_close(lc);
    }

    /* Finally, set any umask we've found */
    if (flags & LOGIN_SETUMASK)
	umask(mymask);

    return (0);
}