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
 int EXT_RQUOTAVERS ; 
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int LOG_PID ; 
 int /*<<< orphan*/  RQUOTAPROG ; 
 int RQUOTAVERS ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ from_inetd ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcb_unset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rquota_service_1 ; 
 int /*<<< orphan*/  rquota_service_2 ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int svc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int svc_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_run () ; 
 int /*<<< orphan*/ * svc_tli_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

int
main(int argc, char **argv)
{
	SVCXPRT *transp;
	int ok;
	struct sockaddr_storage from;
	socklen_t fromlen;
	int vers;
	int ch;

	while ((ch = getopt(argc, argv, "d")) != -1) {
		switch (ch) {
		case 'd':
			debug++;
			break;
		default:
			break;
		}
	}

	fromlen = sizeof(from);
	if (getsockname(0, (struct sockaddr *)&from, &fromlen) < 0)
		from_inetd = 0;

	if (!from_inetd) {
		if (!debug)
			daemon(0, 0);
		(void)rpcb_unset(RQUOTAPROG, RQUOTAVERS, NULL);
		(void)signal(SIGINT, cleanup);
		(void)signal(SIGTERM, cleanup);
		(void)signal(SIGHUP, cleanup);
	}

	openlog("rpc.rquotad", LOG_CONS|LOG_PID, LOG_DAEMON);

	/* create and register the service */
	if (from_inetd) {
		transp = svc_tli_create(0, NULL, NULL, 0, 0);
		if (transp == NULL) {
			syslog(LOG_ERR, "couldn't create udp service.");
			exit(1);
		}
		vers = RQUOTAVERS;
		ok = svc_reg(transp, RQUOTAPROG, RQUOTAVERS,
		    rquota_service_1, NULL);
		if (ok) {
			vers = EXT_RQUOTAVERS;
			ok = svc_reg(transp, RQUOTAPROG, EXT_RQUOTAVERS,
				     rquota_service_2, NULL);
		}
	} else {
		vers = RQUOTAVERS;
		ok = svc_create(rquota_service_1,
		    RQUOTAPROG, RQUOTAVERS, "udp");
		if (ok) {
			vers = EXT_RQUOTAVERS;
			ok = svc_create(rquota_service_2,
					RQUOTAPROG, EXT_RQUOTAVERS, "udp");

		}
	}
	if (!ok) {
		syslog(LOG_ERR,
		    "unable to register (RQUOTAPROG, %s, %s)",
		       vers == RQUOTAVERS ? "RQUOTAVERS" : "EXT_RQUOTAVERS",
		       from_inetd ? "(inetd)" : "udp");
		exit(1);
	}

	svc_run();
	syslog(LOG_ERR, "svc_run returned");
	exit(1);
}