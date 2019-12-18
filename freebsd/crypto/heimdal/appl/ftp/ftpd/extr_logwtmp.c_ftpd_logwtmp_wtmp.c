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
struct TYPE_2__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct utmpx {int ut_syslen; void* ut_type; TYPE_1__ ut_tv; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_time; int /*<<< orphan*/  ut_pid; int /*<<< orphan*/  ut_name; } ;
struct utmp {int ut_syslen; void* ut_type; TYPE_1__ ut_tv; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_time; int /*<<< orphan*/  ut_pid; int /*<<< orphan*/  ut_name; } ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 void* DEAD_PROCESS ; 
 int O_APPEND ; 
 int O_WRONLY ; 
 void* USER_PROCESS ; 
 int /*<<< orphan*/  WTMPX_FILE ; 
 int /*<<< orphan*/  WTMP_FILE ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct utmpx*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pututxline (struct utmpx*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write (int,struct utmpx*,int) ; 

__attribute__((used)) static void
ftpd_logwtmp_wtmp(char *line, char *name, char *host)
{
    static int init = 0;
    static int fd;
#ifdef WTMPX_FILE
    static int fdx;
#endif
#ifdef HAVE_UTMP_H
    struct utmp ut;
#endif
#if defined(WTMPX_FILE) || defined(HAVE_UTMPX_H)
    struct utmpx utx;
#endif

#ifdef HAVE_UTMPX_H
    memset(&utx, 0, sizeof(struct utmpx));
#endif
#ifdef HAVE_UTMP_H
    memset(&ut, 0, sizeof(struct utmp));
#ifdef HAVE_STRUCT_UTMP_UT_TYPE
    if(name[0])
	ut.ut_type = USER_PROCESS;
    else
	ut.ut_type = DEAD_PROCESS;
#endif
    strncpy(ut.ut_line, line, sizeof(ut.ut_line));
    strncpy(ut.ut_name, name, sizeof(ut.ut_name));
#ifdef HAVE_STRUCT_UTMP_UT_PID
    ut.ut_pid = getpid();
#endif
#ifdef HAVE_STRUCT_UTMP_UT_HOST
    strncpy(ut.ut_host, host, sizeof(ut.ut_host));
#endif
    ut.ut_time = time(NULL);
#endif

#if defined(WTMPX_FILE) || defined(HAVE_UTMPX_H)
    strncpy(utx.ut_line, line, sizeof(utx.ut_line));
    strncpy(utx.ut_user, name, sizeof(utx.ut_user));
    strncpy(utx.ut_host, host, sizeof(utx.ut_host));
#ifdef HAVE_STRUCT_UTMPX_UT_SYSLEN
    utx.ut_syslen = strlen(host) + 1;
    if (utx.ut_syslen > sizeof(utx.ut_host))
        utx.ut_syslen = sizeof(utx.ut_host);
#endif
    {
	struct timeval tv;

	gettimeofday (&tv, 0);
	utx.ut_tv.tv_sec = tv.tv_sec;
	utx.ut_tv.tv_usec = tv.tv_usec;
    }

    if(name[0])
	utx.ut_type = USER_PROCESS;
    else
	utx.ut_type = DEAD_PROCESS;
#endif

#ifdef HAVE_UTMPX_H
    pututxline(&utx);
#endif

    if(!init){
#ifdef WTMP_FILE
	fd = open(WTMP_FILE, O_WRONLY|O_APPEND, 0);
#endif
#ifdef WTMPX_FILE
	fdx = open(WTMPX_FILE, O_WRONLY|O_APPEND, 0);
#endif
	init = 1;
    }
    if(fd >= 0) {
#ifdef WTMP_FILE
	write(fd, &ut, sizeof(struct utmp)); /* XXX */
#endif
#ifdef WTMPX_FILE
	write(fdx, &utx, sizeof(struct utmpx));
#endif
    }
}