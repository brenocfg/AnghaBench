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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int LOG_PID ; 
 int /*<<< orphan*/  RSTATPROG ; 
 int /*<<< orphan*/  RSTATVERS_ORIG ; 
 int /*<<< orphan*/  RSTATVERS_SWTCH ; 
 int /*<<< orphan*/  RSTATVERS_TIME ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  cleanup ; 
 int closedown ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ from_inetd ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcb_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rstat_service ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int svc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int svc_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_run () ; 
 int /*<<< orphan*/ * svc_tli_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

int
main(int argc, char *argv[])
{
	SVCXPRT *transp;
	int ok;
	struct sockaddr_storage from;
	socklen_t fromlen;

        if (argc == 2)
                closedown = atoi(argv[1]);
        if (closedown <= 0)
                closedown = 20;

        /*
         * See if inetd started us
         */
	fromlen = sizeof(from);
        if (getsockname(0, (struct sockaddr *)&from, &fromlen) < 0) {
                from_inetd = 0;
        }

        if (!from_inetd) {
                daemon(0, 0);

                (void)rpcb_unset(RSTATPROG, RSTATVERS_TIME, NULL);
                (void)rpcb_unset(RSTATPROG, RSTATVERS_SWTCH, NULL);
                (void)rpcb_unset(RSTATPROG, RSTATVERS_ORIG, NULL);

		(void) signal(SIGINT, cleanup);
		(void) signal(SIGTERM, cleanup);
		(void) signal(SIGHUP, cleanup);
        }

        openlog("rpc.rstatd", LOG_CONS|LOG_PID, LOG_DAEMON);

	if (from_inetd) {
		transp = svc_tli_create(0, NULL, NULL, 0, 0);
		if (transp == NULL) {
			syslog(LOG_ERR, "cannot create udp service.");
			exit(1);
		}
		ok = svc_reg(transp, RSTATPROG, RSTATVERS_TIME,
			     rstat_service, NULL);
	} else
		ok = svc_create(rstat_service,
				RSTATPROG, RSTATVERS_TIME, "udp");
	if (!ok) {
		syslog(LOG_ERR, "unable to register (RSTATPROG, RSTATVERS_TIME, %s)", (!from_inetd)?"udp":"(inetd)");
  		exit(1);
	}
	if (from_inetd)
		ok = svc_reg(transp, RSTATPROG, RSTATVERS_SWTCH,
			     rstat_service, NULL);
	else
		ok = svc_create(rstat_service,
				RSTATPROG, RSTATVERS_SWTCH, "udp");
	if (!ok) {
		syslog(LOG_ERR, "unable to register (RSTATPROG, RSTATVERS_SWTCH, %s)", (!from_inetd)?"udp":"(inetd)");
  		exit(1);
	}
	if (from_inetd)
		ok = svc_reg(transp, RSTATPROG, RSTATVERS_ORIG,
			     rstat_service, NULL);
	else
		ok = svc_create(rstat_service,
				RSTATPROG, RSTATVERS_ORIG, "udp");
	if (!ok) {
		syslog(LOG_ERR, "unable to register (RSTATPROG, RSTATVERS_ORIG, %s)", (!from_inetd)?"udp":"(inetd)");
  		exit(1);
	}

        svc_run();
	syslog(LOG_ERR, "svc_run returned");
	exit(1);
}