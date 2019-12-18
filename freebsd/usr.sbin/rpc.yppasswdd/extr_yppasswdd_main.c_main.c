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
struct sigaction {int /*<<< orphan*/  sa_flags; } ;
struct rlimit {scalar_t__ rlim_max; scalar_t__ rlim_cur; } ;
struct netconfig {int /*<<< orphan*/ * nc_protofmly; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  myname ;
typedef  int /*<<< orphan*/  SVCXPRT ;
typedef  int /*<<< orphan*/  SIG_PF ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  MASTER_YPPASSWDPROG ; 
 int /*<<< orphan*/  MASTER_YPPASSWDVERS ; 
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  NC_LOOPBACK ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  RLIMIT_CPU ; 
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int /*<<< orphan*/  RLIMIT_FSIZE ; 
 int /*<<< orphan*/  RLIMIT_RSS ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  RPC_ANYSOCK ; 
 int RPC_MAXDATASIZE ; 
 int /*<<< orphan*/  RPC_SVC_CONNMAXREC_SET ; 
 int /*<<< orphan*/  SA_NOCLDWAIT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int /*<<< orphan*/  YPPASSWDPROG ; 
 int /*<<< orphan*/  YPPASSWDVERS ; 
 int /*<<< orphan*/  YPPROG ; 
 int /*<<< orphan*/  YPVERS ; 
 int _RPCSVC_CLOSEDOWN ; 
 int /*<<< orphan*/  _localhost ; 
 int /*<<< orphan*/  _passwd_byname ; 
 int /*<<< orphan*/  _rpcfdtype ; 
 int _rpcpmstart ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  allow_additions ; 
 scalar_t__ chmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ closedown ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endnetconfig (void*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int gethostname (char*,int) ; 
 struct netconfig* getnetconfig (void*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getrpcport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  inplace ; 
 int /*<<< orphan*/  load_securenets () ; 
 int /*<<< orphan*/  master_yppasswdprog_1 ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  multidomain ; 
 int /*<<< orphan*/  nc_sperror () ; 
 int /*<<< orphan*/  no_chfn ; 
 int /*<<< orphan*/  no_chsh ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* optarg ; 
 void* passfile_default ; 
 scalar_t__ reload ; 
 int /*<<< orphan*/  resvport ; 
 int /*<<< orphan*/  rpc_control (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rpcb_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* setnetconfig () ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockname ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 scalar_t__ svc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netconfig*) ; 
 int /*<<< orphan*/  svc_run () ; 
 int /*<<< orphan*/ * svcunix_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ terminate ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbose ; 
 void* yp_dir ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 scalar_t__ yp_get_default_domain (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * yppasswd_domain ; 
 int /*<<< orphan*/  yppasswdprog_1 ; 
 char* ypxfr_get_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	struct rlimit rlim;
	SVCXPRT *transp = NULL;
	struct sockaddr_in saddr;
	socklen_t asize = sizeof (saddr);
	struct netconfig *nconf;
	struct sigaction sa;
	void *localhandle;
	int ch;
	char *mastername;
	char myname[MAXHOSTNAMELEN + 2];
	int maxrec = RPC_MAXDATASIZE;

	extern int debug;

	debug = 1;

	while ((ch = getopt(argc, argv, "t:d:p:sfamuivh")) != -1) {
		switch (ch) {
		case 't':
			passfile_default = optarg;
			break;
		case 'd':
			yppasswd_domain = optarg;
			break;
		case 's':
			no_chsh++;
			break;
		case 'f':
			no_chfn++;
			break;
		case 'p':
			yp_dir = optarg;
			break;
		case 'a':
			allow_additions++;
			break;
		case 'm':
			multidomain++;
			break;
		case 'i':
			inplace++;
			break;
		case 'v':
			verbose++;
			break;
		case 'u':
			resvport = 0;
			break;
		default:
		case 'h':
			usage();
			break;
		}
	}

	if (yppasswd_domain == NULL) {
		if (yp_get_default_domain(&yppasswd_domain)) {
			yp_error("no domain specified and system domain \
name isn't set -- aborting");
		usage();
		}
	}

	load_securenets();

	if (getrpcport(_localhost, YPPROG, YPVERS, IPPROTO_UDP) <= 0) {
		yp_error("no ypserv processes registered with local portmap");
		yp_error("this host is not an NIS server -- aborting");
		exit(1);
	}

	if ((mastername = ypxfr_get_master(yppasswd_domain,
		 _passwd_byname, _localhost, 0)) == NULL) {
		yp_error("can't get name of NIS master server for domain %s",
			 				yppasswd_domain);
		exit(1);
	}

	if (gethostname((char *)&myname, sizeof(myname)) == -1) {
		yp_error("can't get local hostname: %s", strerror(errno));
		exit(1);
	}

	if (strncasecmp(mastername, (char *)&myname, sizeof(myname))) {
		yp_error("master of %s is %s, but we are %s",
			"passwd.byname", mastername, myname);
		yp_error("this host is not the NIS master server for \
the %s domain -- aborting", yppasswd_domain);
		exit(1);
	}

	debug = 0;

	if (getsockname(0, (struct sockaddr *)&saddr, &asize) == 0) {
		socklen_t ssize = sizeof (int);
		if (saddr.sin_family != AF_INET)
			exit(1);
		if (getsockopt(0, SOL_SOCKET, SO_TYPE,
		    (char *)&_rpcfdtype, &ssize) == -1)
			exit(1);
		_rpcpmstart = 1;
	}

	if (!debug && _rpcpmstart == 0) {
		if (daemon(0,0)) {
			err(1,"cannot fork");
		}
	}
	openlog("rpc.yppasswdd", LOG_PID, LOG_DAEMON);
	memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &sa, NULL);

	rpcb_unset(YPPASSWDPROG, YPPASSWDVERS, NULL);
	rpcb_unset(MASTER_YPPASSWDPROG, MASTER_YPPASSWDVERS, NULL);

	rpc_control(RPC_SVC_CONNMAXREC_SET, &maxrec);

	if (svc_create(yppasswdprog_1, YPPASSWDPROG, YPPASSWDVERS, "netpath") == 0) {
		yp_error("cannot create yppasswd service.");
		exit(1);
	}
	if (svc_create(master_yppasswdprog_1, MASTER_YPPASSWDPROG,
	    MASTER_YPPASSWDVERS, "netpath") == 0) {
		yp_error("cannot create master_yppasswd service.");
		exit(1);
	}

	nconf = NULL;
	localhandle = setnetconfig();
	while ((nconf = getnetconfig(localhandle)) != NULL) {
		if (nconf->nc_protofmly != NULL &&
		    strcmp(nconf->nc_protofmly, NC_LOOPBACK) == 0)
			break;
	}
	if (nconf == NULL) {
		yp_error("getnetconfigent unix: %s", nc_sperror());
		exit(1);
	}
	unlink(sockname);
	transp = svcunix_create(RPC_ANYSOCK, 0, 0, sockname);
	if (transp == NULL) {
		yp_error("cannot create AF_LOCAL service.");
		exit(1);
	}
	if (!svc_reg(transp, MASTER_YPPASSWDPROG, MASTER_YPPASSWDVERS,
	    master_yppasswdprog_1, nconf)) {
		yp_error("unable to register (MASTER_YPPASSWDPROG, \
		    MASTER_YPPASSWDVERS, unix).");
		exit(1);
	}
	endnetconfig(localhandle);

	/* Only root may connect() to the AF_UNIX link. */
	if (chmod(sockname, 0))
		err(1, "chmod of %s failed", sockname);

	if (transp == (SVCXPRT *)NULL) {
		yp_error("could not create a handle");
		exit(1);
	}
	if (_rpcpmstart) {
		(void) signal(SIGALRM, (SIG_PF) closedown);
		(void) alarm(_RPCSVC_CLOSEDOWN/2);
	}

	/* Unlimited resource limits. */
	rlim.rlim_cur = rlim.rlim_max = RLIM_INFINITY;
	(void)setrlimit(RLIMIT_CPU, &rlim);
	(void)setrlimit(RLIMIT_FSIZE, &rlim);
	(void)setrlimit(RLIMIT_STACK, &rlim);
	(void)setrlimit(RLIMIT_DATA, &rlim);
	(void)setrlimit(RLIMIT_RSS, &rlim);

	/* Don't drop core (not really necessary, but GP's). */
	rlim.rlim_cur = rlim.rlim_max = 0;
	(void)setrlimit(RLIMIT_CORE, &rlim);

	/* Turn off signals. */
	(void)signal(SIGALRM, SIG_IGN);
	(void)signal(SIGHUP, (SIG_PF) reload);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGPIPE, SIG_IGN);
	(void)signal(SIGQUIT, SIG_IGN);
	(void)signal(SIGTERM, (SIG_PF) terminate);

	svc_run();
	yp_error("svc_run returned");
	exit(1);
	/* NOTREACHED */
}