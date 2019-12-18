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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_uid; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int LOG_PID ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  WALLPROG ; 
 int /*<<< orphan*/  WALLVERS ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ from_inetd ; 
 scalar_t__ geteuid () ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  killkids ; 
 int nodaemon ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  possess () ; 
 int /*<<< orphan*/  rpcb_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int svc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int svc_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_run () ; 
 int /*<<< orphan*/ * svc_tli_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  wallprog_1 ; 

int
main(int argc, char *argv[])
{
	SVCXPRT *transp;
	socklen_t salen;
	int ok;
	struct sockaddr_storage sa;

	if (argc == 2 && !strcmp(argv[1], "-n"))
		nodaemon = 1;
	if (argc != 1 && !nodaemon)
		usage();

	if (geteuid() == 0) {
		struct passwd *pep = getpwnam("nobody");
		if (pep)
			setuid(pep->pw_uid);
		else
			setuid(getuid());
	}

        /*
         * See if inetd started us
         */
	salen = sizeof(sa);
        if (getsockname(0, (struct sockaddr *)&sa, &salen) < 0) {
                from_inetd = 0;
        }

        if (!from_inetd) {
                if (!nodaemon)
                        possess();

		(void)rpcb_unset(WALLPROG, WALLVERS, NULL);
        }

	(void)signal(SIGCHLD, killkids);

	openlog("rpc.rwalld", LOG_CONS|LOG_PID, LOG_DAEMON);

	/* create and register the service */
	if (from_inetd) {
		transp = svc_tli_create(0, NULL, NULL, 0, 0);
		if (transp == NULL) {
			syslog(LOG_ERR, "couldn't create udp service.");
			exit(1);
		}
		ok = svc_reg(transp, WALLPROG, WALLVERS,
			     wallprog_1, NULL);
	} else
		ok = svc_create(wallprog_1,
				WALLPROG, WALLVERS, "udp");
	if (!ok) {
		syslog(LOG_ERR, "unable to register (WALLPROG, WALLVERS, %s)", (!from_inetd)?"udp":"(inetd)");
		exit(1);
	}
	svc_run();
	syslog(LOG_ERR, "svc_run returned");
	exit(1);
}