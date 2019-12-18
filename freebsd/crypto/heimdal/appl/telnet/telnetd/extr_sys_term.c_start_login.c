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
typedef  int /*<<< orphan*/  utmpx ;
struct TYPE_2__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct utmpx {int ut_pid; TYPE_1__ ut_tv; int /*<<< orphan*/  ut_type; int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_user; } ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct arg_val {int /*<<< orphan*/  argv; scalar_t__ argc; scalar_t__ size; } ;

/* Variables and functions */
 int AUTH_VALID ; 
 int /*<<< orphan*/  LOGIN_PROCESS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  addarg (struct arg_val*,char const*) ; 
 scalar_t__ auth_level ; 
 char* clean_ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/ * decrypt_input ; 
 int /*<<< orphan*/ * encrypt_output ; 
 int errno ; 
 int /*<<< orphan*/  execv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fatalperror_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* getenv (char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line ; 
 scalar_t__ log_unauth ; 
 char* make_id (char*) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct utmpx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net ; 
 int /*<<< orphan*/  new_login ; 
 int /*<<< orphan*/  no_warn ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * pututxline (struct utmpx*) ; 
 scalar_t__ require_otp ; 
 int /*<<< orphan*/  scrub_env () ; 
 int /*<<< orphan*/  sleep (int) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

void
start_login(const char *host, int autologin, char *name)
{
    struct arg_val argv;
    char *user;
    int save_errno;

#ifdef ENCRYPTION
    encrypt_output = NULL;
    decrypt_input = NULL;
#endif

#ifdef HAVE_UTMPX_H
    {
	int pid = getpid();
	struct utmpx utmpx;
	struct timeval tv;
	char *clean_tty;

	/*
	 * Create utmp entry for child
	 */

	clean_tty = clean_ttyname(line);
	memset(&utmpx, 0, sizeof(utmpx));
	strncpy(utmpx.ut_user,  ".telnet", sizeof(utmpx.ut_user));
	strncpy(utmpx.ut_line,  clean_tty, sizeof(utmpx.ut_line));
#ifdef HAVE_STRUCT_UTMP_UT_ID
	strncpy(utmpx.ut_id, make_id(clean_tty), sizeof(utmpx.ut_id));
#endif
	utmpx.ut_pid = pid;

	utmpx.ut_type = LOGIN_PROCESS;

	gettimeofday (&tv, NULL);
	utmpx.ut_tv.tv_sec = tv.tv_sec;
	utmpx.ut_tv.tv_usec = tv.tv_usec;

	if (pututxline(&utmpx) == NULL)
	    fatal(net, "pututxline failed");
    }
#endif

    scrub_env();

    /*
     * -h : pass on name of host.
     *		WARNING:  -h is accepted by login if and only if
     *			getuid() == 0.
     * -p : don't clobber the environment (so terminal type stays set).
     *
     * -f : force this login, he has already been authenticated
     */

    /* init argv structure */
    argv.size=0;
    argv.argc=0;
    argv.argv=malloc(0); /*so we can call realloc later */
    addarg(&argv, "login");
    addarg(&argv, "-h");
    addarg(&argv, host);
    addarg(&argv, "-p");
    if(name && name[0])
	user = name;
    else
	user = getenv("USER");
#ifdef AUTHENTICATION
    if (auth_level < 0 || autologin != AUTH_VALID) {
	if(!no_warn) {
	    printf("User not authenticated. ");
	    if (require_otp)
		printf("Using one-time password\r\n");
	    else
		printf("Using plaintext username and password\r\n");
	}
	if (require_otp) {
	    addarg(&argv, "-a");
	    addarg(&argv, "otp");
	}
	if(log_unauth)
	    syslog(LOG_INFO, "unauthenticated access from %s (%s)",
		   host, user ? user : "unknown user");
    }
    if (auth_level >= 0 && autologin == AUTH_VALID)
	addarg(&argv, "-f");
#endif
    if(user){
	addarg(&argv, "--");
	addarg(&argv, strdup(user));
    }
    if (getenv("USER")) {
	/*
	 * Assume that login will set the USER variable
	 * correctly.  For SysV systems, this means that
	 * USER will no longer be set, just LOGNAME by
	 * login.  (The problem is that if the auto-login
	 * fails, and the user then specifies a different
	 * account name, he can get logged in with both
	 * LOGNAME and USER in his environment, but the
	 * USER value will be wrong.
	 */
	unsetenv("USER");
    }
    closelog();
    /*
     * This sleep(1) is in here so that telnetd can
     * finish up with the tty.  There's a race condition
     * the login banner message gets lost...
     */
    sleep(1);

    execv(new_login, argv.argv);
    save_errno = errno;
    syslog(LOG_ERR, "%s: %m", new_login);
    fatalperror_errno(net, new_login, save_errno);
    /*NOTREACHED*/
}