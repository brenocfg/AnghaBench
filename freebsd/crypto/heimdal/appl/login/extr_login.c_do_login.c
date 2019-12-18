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
struct user_cap {char* ca_default; } ;
struct udb {long* ue_pcpulim; long* ue_jcpulim; int /*<<< orphan*/ * ue_nice; } ;
struct spwd {int dummy; } ;
struct passwd {scalar_t__ pw_uid; char const* pw_name; char* pw_dir; char const* pw_shell; scalar_t__ pw_gid; } ;
struct group {scalar_t__ gr_gid; } ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/ * cap_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ AUTH_KRB5 ; 
 int CLOCKS_PER_SEC ; 
 long CPUUNLIM ; 
 int /*<<< orphan*/  C_JOBPROCS ; 
 int /*<<< orphan*/  C_PROC ; 
 int /*<<< orphan*/  L_CPU ; 
 int MAXPATHLEN ; 
 int NSIG ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWUSR ; 
 size_t UDBRC_INTER ; 
 struct udb* UDB_NULL ; 
 char const* _PATH_DEFPATH ; 
 char* _PATH_ETC_ENVIRONMENT ; 
 char* _PATH_LIMITS_CONF ; 
 int /*<<< orphan*/  add_env (char*,char const*) ; 
 scalar_t__ auth ; 
 int /*<<< orphan*/  cap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_from_text (char*) ; 
 scalar_t__ cap_set_proc (int /*<<< orphan*/ *) ; 
 scalar_t__ chdir (char const*) ; 
 int /*<<< orphan*/  check_shadow (struct passwd const*,struct spwd*) ; 
 int /*<<< orphan*/  checknologin () ; 
 scalar_t__ chmod (char*,int) ; 
 scalar_t__ chown (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ do_osfc2_magic (scalar_t__) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exec_shell (char const*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct user_cap*) ; 
 struct group* getgrnam (char*) ; 
 struct spwd* getspnam (char const*) ; 
 struct udb* getudbnam (char const*) ; 
 scalar_t__ initgroups (char const*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_finish () ; 
 int /*<<< orphan*/  krb5_get_afs_tokens (struct passwd const*) ; 
 int /*<<< orphan*/  krb5_start_session (struct passwd const*) ; 
 scalar_t__ limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 char* login_conf_get_string (char*) ; 
 int /*<<< orphan*/  login_read_env (char*) ; 
 int /*<<< orphan*/  nice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_limits_conf (char const*,struct passwd const*) ; 
 char* remote_host ; 
 scalar_t__ setgid (scalar_t__) ; 
 scalar_t__ setlogin (char const*) ; 
 int setpcred (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ setuid (scalar_t__) ; 
 struct user_cap* sgi_getcapabilitybyname (char const*) ; 
 int /*<<< orphan*/  show_file (char const*) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int strsep_copy (char const**,char*,char*,int) ; 
 int /*<<< orphan*/  update_utmp (char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static void
do_login(const struct passwd *pwd, char *tty, char *ttyn)
{
#ifdef HAVE_GETSPNAM
    struct spwd *sp;
#endif
    int rootlogin = (pwd->pw_uid == 0);
    gid_t tty_gid;
    struct group *gr;
    const char *home_dir;
    int i;

    if(!rootlogin)
	checknologin();

#ifdef HAVE_GETSPNAM
    sp = getspnam(pwd->pw_name);
#endif

    update_utmp(pwd->pw_name, remote_host ? remote_host : "",
		tty, ttyn);

    gr = getgrnam ("tty");
    if (gr != NULL)
	tty_gid = gr->gr_gid;
    else
	tty_gid = pwd->pw_gid;

    if (chown (ttyn, pwd->pw_uid, tty_gid) < 0) {
	warn("chown %s", ttyn);
	if (rootlogin == 0)
	    exit (1);
    }

    if (chmod (ttyn, S_IRUSR | S_IWUSR | S_IWGRP) < 0) {
	warn("chmod %s", ttyn);
	if (rootlogin == 0)
	    exit (1);
    }

#ifdef HAVE_SETLOGIN
    if(setlogin(pwd->pw_name)){
	warn("setlogin(%s)", pwd->pw_name);
	if(rootlogin == 0)
	    exit(1);
    }
#endif
    if(rootlogin == 0) {
	const char *file = login_conf_get_string("limits");
	if(file == NULL)
	    file = _PATH_LIMITS_CONF;

	read_limits_conf(file, pwd);
    }

#ifdef HAVE_SETPCRED
    if (setpcred (pwd->pw_name, NULL) == -1)
	warn("setpcred(%s)", pwd->pw_name);
#endif /* HAVE_SETPCRED */
#ifdef HAVE_INITGROUPS
    if(initgroups(pwd->pw_name, pwd->pw_gid)){
	warn("initgroups(%s, %u)", pwd->pw_name, (unsigned)pwd->pw_gid);
	if(rootlogin == 0)
	    exit(1);
    }
#endif
    if(do_osfc2_magic(pwd->pw_uid))
	exit(1);
    if(setgid(pwd->pw_gid)){
	warn("setgid(%u)", (unsigned)pwd->pw_gid);
	if(rootlogin == 0)
	    exit(1);
    }
    if(setuid(pwd->pw_uid) || (pwd->pw_uid != 0 && setuid(0) == 0)) {
	warn("setuid(%u)", (unsigned)pwd->pw_uid);
	if(rootlogin == 0)
	    exit(1);
    }

    /* make sure signals are set to default actions, apparently some
       OS:es like to ignore SIGINT, which is not very convenient */

    for (i = 1; i < NSIG; ++i)
	signal(i, SIG_DFL);

    /* all kinds of different magic */

#ifdef HAVE_GETSPNAM
    check_shadow(pwd, sp);
#endif

#if defined(HAVE_GETUDBNAM) && defined(HAVE_SETLIM)
    {
	struct udb *udb;
	long t;
	const long maxcpu = 46116860184; /* some random constant */
	udb = getudbnam(pwd->pw_name);
	if(udb == UDB_NULL)
	    errx(1, "Failed to get UDB entry.");
	t = udb->ue_pcpulim[UDBRC_INTER];
	if(t == 0 || t > maxcpu)
	    t = CPUUNLIM;
	else
	    t *= 100 * CLOCKS_PER_SEC;

	if(limit(C_PROC, 0, L_CPU, t) < 0)
	    warn("limit C_PROC");

	t = udb->ue_jcpulim[UDBRC_INTER];
	if(t == 0 || t > maxcpu)
	    t = CPUUNLIM;
	else
	    t *= 100 * CLOCKS_PER_SEC;

	if(limit(C_JOBPROCS, 0, L_CPU, t) < 0)
	    warn("limit C_JOBPROCS");

	nice(udb->ue_nice[UDBRC_INTER]);
    }
#endif
#if defined(HAVE_SGI_GETCAPABILITYBYNAME) && defined(HAVE_CAP_SET_PROC)
	/* XXX SGI capability hack IRIX 6.x (x >= 0?) has something
	   called capabilities, that allow you to give away
	   permissions (such as chown) to specific processes. From 6.5
	   this is default on, and the default capability set seems to
	   not always be the empty set. The problem is that the
	   runtime linker refuses to do just about anything if the
	   process has *any* capabilities set, so we have to remove
	   them here (unless otherwise instructed by /etc/capability).
	   In IRIX < 6.5, these functions was called sgi_cap_setproc,
	   etc, but we ignore this fact (it works anyway). */
	{
	    struct user_cap *ucap = sgi_getcapabilitybyname(pwd->pw_name);
	    cap_t cap;
	    if(ucap == NULL)
		cap = cap_from_text("all=");
	    else
		cap = cap_from_text(ucap->ca_default);
	    if(cap == NULL)
		err(1, "cap_from_text");
	    if(cap_set_proc(cap) < 0)
		err(1, "cap_set_proc");
	    cap_free(cap);
	    free(ucap);
	}
#endif
    home_dir = pwd->pw_dir;
    if (chdir(home_dir) < 0) {
	fprintf(stderr, "No home directory \"%s\"!\n", pwd->pw_dir);
	if (chdir("/"))
	    exit(0);
	home_dir = "/";
	fprintf(stderr, "Logging in with home = \"/\".\n");
    }
#ifdef KRB5
    if (auth == AUTH_KRB5) {
	krb5_start_session (pwd);
    }

    krb5_get_afs_tokens (pwd);

    krb5_finish ();
#endif /* KRB5 */

    add_env("PATH", _PATH_DEFPATH);

    {
	const char *str = login_conf_get_string("environment");
	char buf[MAXPATHLEN];

	if(str == NULL) {
	    login_read_env(_PATH_ETC_ENVIRONMENT);
	} else {
	    while(strsep_copy(&str, ",", buf, sizeof(buf)) != -1) {
		if(buf[0] == '\0')
		    continue;
		login_read_env(buf);
	    }
	}
    }
    {
	const char *str = login_conf_get_string("motd");
	char buf[MAXPATHLEN];

	if(str != NULL) {
	    while(strsep_copy(&str, ",", buf, sizeof(buf)) != -1) {
		if(buf[0] == '\0')
		    continue;
		show_file(buf);
	    }
	} else {
	    str = login_conf_get_string("welcome");
	    if(str != NULL)
		show_file(str);
	}
    }
    add_env("HOME", home_dir);
    add_env("USER", pwd->pw_name);
    add_env("LOGNAME", pwd->pw_name);
    add_env("SHELL", pwd->pw_shell);
    exec_shell(pwd->pw_shell, rootlogin);
}