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
struct sockaddr_in {scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  SVCXPRT ;
typedef  int /*<<< orphan*/  SIG_PF ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  AUTH_DES ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_PID ; 
 int RPC_ANYSOCK ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int /*<<< orphan*/  YPU_PROG ; 
 int /*<<< orphan*/  YPU_VERS ; 
 int _RPCSVC_CLOSEDOWN ; 
 int /*<<< orphan*/  _msgout (char*) ; 
 scalar_t__ _rpcfdtype ; 
 int _rpcpmstart ; 
 int /*<<< orphan*/  _svcauth_des ; 
 int /*<<< orphan*/  alarm (int) ; 
 scalar_t__ closedown ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  load_securenets () ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  pmap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reaper ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int svc_auth_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svctcp_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svcudp_create (int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  yp_dir ; 
 int /*<<< orphan*/  yp_error (char*) ; 
 int /*<<< orphan*/  ypu_prog_1 ; 
 int /*<<< orphan*/  ypupdated_svc_run () ; 

int
main(int argc, char *argv[])
{
	register SVCXPRT *transp = NULL;
	int sock;
	int proto = 0;
	struct sockaddr_in saddr;
	int asize = sizeof (saddr);
	int ch;

	while ((ch = getopt(argc, argv, "p:h")) != -1) {
		switch (ch) {
		case 'p':
			yp_dir = optarg;
			break;
		default:
			usage();
			break;
		}
	}
#ifdef foo
	load_securenets();
#endif

	if (svc_auth_reg(AUTH_DES, _svcauth_des) == -1) {
		yp_error("failed to register AUTH_DES flavor");
		exit(1);
	}

	if (getsockname(0, (struct sockaddr *)&saddr, &asize) == 0) {
		int ssize = sizeof (int);

		if (saddr.sin_family != AF_INET)
			exit(1);
		if (getsockopt(0, SOL_SOCKET, SO_TYPE,
				(char *)&_rpcfdtype, &ssize) == -1)
			exit(1);
		sock = 0;
		_rpcpmstart = 1;
		proto = 0;
		openlog("rpc.ypupdatedd", LOG_PID, LOG_DAEMON);
	} else {
#ifndef RPC_SVC_FG
		if (daemon(0,0)) {
			err(1, "cannot fork");
		}
		openlog("rpc.ypupdated", LOG_PID, LOG_DAEMON);
#endif
		sock = RPC_ANYSOCK;
		(void) pmap_unset(YPU_PROG, YPU_VERS);
	}

	if ((_rpcfdtype == 0) || (_rpcfdtype == SOCK_DGRAM)) {
		transp = svcudp_create(sock);
		if (transp == NULL) {
			_msgout("cannot create udp service.");
			exit(1);
		}
		if (!_rpcpmstart)
			proto = IPPROTO_UDP;
		if (!svc_register(transp, YPU_PROG, YPU_VERS, ypu_prog_1, proto)) {
			_msgout("unable to register (YPU_PROG, YPU_VERS, udp).");
			exit(1);
		}
	}

	if ((_rpcfdtype == 0) || (_rpcfdtype == SOCK_STREAM)) {
		transp = svctcp_create(sock, 0, 0);
		if (transp == NULL) {
			_msgout("cannot create tcp service.");
			exit(1);
		}
		if (!_rpcpmstart)
			proto = IPPROTO_TCP;
		if (!svc_register(transp, YPU_PROG, YPU_VERS, ypu_prog_1, proto)) {
			_msgout("unable to register (YPU_PROG, YPU_VERS, tcp).");
			exit(1);
		}
	}

	if (transp == (SVCXPRT *)NULL) {
		_msgout("could not create a handle");
		exit(1);
	}
	if (_rpcpmstart) {
		(void) signal(SIGALRM, (SIG_PF) closedown);
		(void) alarm(_RPCSVC_CLOSEDOWN/2);
	}

	(void) signal(SIGPIPE, SIG_IGN);
	(void) signal(SIGCHLD, (SIG_PF) reaper);
	(void) signal(SIGTERM, (SIG_PF) reaper);
	(void) signal(SIGINT, (SIG_PF) reaper);
	(void) signal(SIGHUP, (SIG_PF) reaper);

	ypupdated_svc_run();
	_msgout("svc_run returned");
	exit(1);
	/* NOTREACHED */
}