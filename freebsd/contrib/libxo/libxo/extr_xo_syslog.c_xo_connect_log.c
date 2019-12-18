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
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  saddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ CONNDEF ; 
 scalar_t__ CONNPRIV ; 
 scalar_t__ NOCONN ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  _PATH_LOG ; 
 int /*<<< orphan*/  _PATH_LOG_PRIV ; 
 int /*<<< orphan*/  _PATH_OLDLOG ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xo_logfile ; 
 scalar_t__ xo_status ; 
 int /*<<< orphan*/  xo_syslog_open () ; 

__attribute__((used)) static void
xo_connect_log (void)
{
    if (xo_syslog_open) {
	xo_syslog_open();
	return;
    }

    struct sockaddr_un saddr;    /* AF_UNIX address of local logger */

    if (xo_logfile == -1) {
        int flags = SOCK_DGRAM;
#ifdef SOCK_CLOEXEC
        flags |= SOCK_CLOEXEC;
#endif /* SOCK_CLOEXEC */
        if ((xo_logfile = socket(AF_UNIX, flags, 0)) == -1)
            return;
    }
    if (xo_logfile != -1 && xo_status == NOCONN) {
#ifdef HAVE_SUN_LEN
        saddr.sun_len = sizeof(saddr);
#endif /* HAVE_SUN_LEN */
        saddr.sun_family = AF_UNIX;

        /*
         * First try privileged socket. If no success,
         * then try default socket.
         */

#ifdef _PATH_LOG_PRIV
        (void) strncpy(saddr.sun_path, _PATH_LOG_PRIV,
            sizeof saddr.sun_path);
        if (connect(xo_logfile, (struct sockaddr *) &saddr,
            sizeof(saddr)) != -1)
            xo_status = CONNPRIV;
#endif /* _PATH_LOG_PRIV */

#ifdef _PATH_LOG
        if (xo_status == NOCONN) {
            (void) strncpy(saddr.sun_path, _PATH_LOG,
                sizeof saddr.sun_path);
            if (connect(xo_logfile, (struct sockaddr *)&saddr,
                sizeof(saddr)) != -1)
                xo_status = CONNDEF;
        }
#endif /* _PATH_LOG */

#ifdef _PATH_OLDLOG
        if (xo_status == NOCONN) {
            /*
             * Try the old "/dev/log" path, for backward
             * compatibility.
             */
            (void) strncpy(saddr.sun_path, _PATH_OLDLOG,
                sizeof saddr.sun_path);
            if (connect(xo_logfile, (struct sockaddr *)&saddr,
                sizeof(saddr)) != -1)
                xo_status = CONNDEF;
        }
#endif /* _PATH_OLDLOG */

        if (xo_status == NOCONN) {
            (void) close(xo_logfile);
            xo_logfile = -1;
        }
    }
}