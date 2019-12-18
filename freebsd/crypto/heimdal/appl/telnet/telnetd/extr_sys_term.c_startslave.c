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
struct utmp {int dummy; } ;
struct TYPE_4__ {int ut_pid; char const* ut_user; char const* ut_host; char const* ut_line; char const* ut_id; int /*<<< orphan*/  ut_type; int /*<<< orphan*/  ut_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGIN_PROCESS ; 
 int O_APPEND ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  WJSIGNAL ; 
 int auth_level ; 
 char const* clean_ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ decrypt_input ; 
 scalar_t__ encrypt_output ; 
 int /*<<< orphan*/  endutent () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fatalperror (int /*<<< orphan*/ ,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  getptyslave () ; 
 int /*<<< orphan*/  kerberos5_dfspag () ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  net ; 
 int /*<<< orphan*/  no_warn ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pututline (TYPE_1__*) ; 
 int /*<<< orphan*/  setpgrp () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 int /*<<< orphan*/  start_login (char const*,int,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char const*,char const*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utmp_sig_init () ; 
 int /*<<< orphan*/  utmp_sig_notify (int) ; 
 int /*<<< orphan*/  utmp_sig_reset () ; 
 int /*<<< orphan*/  write (int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  writenet (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ wtmp ; 
 int /*<<< orphan*/  wtmpf ; 

void
startslave(const char *host, const char *utmp_host,
	   int autologin, char *autoname)
{
    int i;

#ifdef AUTHENTICATION
    if (!autoname || !autoname[0])
	autologin = 0;

    if (autologin < auth_level) {
	fatal(net, "Authorization failed");
	exit(1);
    }
#endif

    {
	char *tbuf =
	    "\r\n*** Connection not encrypted! "
	    "Communication may be eavesdropped. ***\r\n";
#ifdef ENCRYPTION
	if (!no_warn && (encrypt_output == 0 || decrypt_input == 0))
#endif
	    writenet(tbuf, strlen(tbuf));
    }
# ifdef	PARENT_DOES_UTMP
    utmp_sig_init();
# endif	/* PARENT_DOES_UTMP */

    if ((i = fork()) < 0)
	fatalperror(net, "fork");
    if (i) {
# ifdef PARENT_DOES_UTMP
	/*
	 * Cray parent will create utmp entry for child and send
	 * signal to child to tell when done.  Child waits for signal
	 * before doing anything important.
	 */
	int pid = i;
	void sigjob (int);

	setpgrp();
	utmp_sig_reset();		/* reset handler to default */
	/*
	 * Create utmp entry for child
	 */
	wtmp.ut_time = time(NULL);
	wtmp.ut_type = LOGIN_PROCESS;
	wtmp.ut_pid = pid;
	strncpy(wtmp.ut_user,  "LOGIN", sizeof(wtmp.ut_user));
	strncpy(wtmp.ut_host,  utmp_host, sizeof(wtmp.ut_host));
	strncpy(wtmp.ut_line,  clean_ttyname(line), sizeof(wtmp.ut_line));
#ifdef HAVE_STRUCT_UTMP_UT_ID
	strncpy(wtmp.ut_id, wtmp.ut_line + 3, sizeof(wtmp.ut_id));
#endif

	pututline(&wtmp);
	endutent();
	if ((i = open(wtmpf, O_WRONLY|O_APPEND)) >= 0) {
	    write(i, &wtmp, sizeof(struct utmp));
	    close(i);
	}
#ifdef	_CRAY
	signal(WJSIGNAL, sigjob);
#endif
	utmp_sig_notify(pid);
# endif	/* PARENT_DOES_UTMP */
    } else {
	getptyslave();
#if defined(DCE)
	/* if we authenticated via K5, try and join the PAG */
	kerberos5_dfspag();
#endif
	start_login(host, autologin, autoname);
	/*NOTREACHED*/
    }
}