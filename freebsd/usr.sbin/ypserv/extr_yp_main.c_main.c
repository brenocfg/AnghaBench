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
struct netconfig {int nc_flag; int /*<<< orphan*/  nc_netid; } ;
struct bindaddrlistent {scalar_t__ si_socktype; scalar_t__ si_af; void* ble_hostname; } ;
struct __rpc_sockinfo {scalar_t__ si_socktype; scalar_t__ si_af; void* ble_hostname; } ;
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  SIG_PF ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  MADV_PROTECT ; 
 int NC_VISIBLE ; 
 int /*<<< orphan*/  NETCONFIG ; 
 scalar_t__ RPC_ANYFD ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bindaddrlistent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _RPCSVC_CLOSEDOWN ; 
 scalar_t__ __rpc_fd2sockinfo (int /*<<< orphan*/ ,struct bindaddrlistent*) ; 
 scalar_t__ __rpc_nconf2sockinfo (struct netconfig*,struct bindaddrlistent*) ; 
 int /*<<< orphan*/  _msgout (char*,...) ; 
 scalar_t__ _rpcaf ; 
 scalar_t__ _rpcfd ; 
 scalar_t__ _rpcfdtype ; 
 int _rpcpmstart ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  ble_head ; 
 int /*<<< orphan*/  ble_next ; 
 scalar_t__ closedown ; 
 int create_service (scalar_t__,struct netconfig*,struct bindaddrlistent*) ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int debug ; 
 int do_dns ; 
 int /*<<< orphan*/  endnetconfig (void*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 struct netconfig* getnetconfig (void*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  load_securenets () ; 
 scalar_t__ madvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bindaddrlistent* malloc (int) ; 
 int /*<<< orphan*/  memset (struct bindaddrlistent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* optarg ; 
 scalar_t__ reaper ; 
 void* servname ; 
 void* setnetconfig () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister () ; 
 int /*<<< orphan*/  usage () ; 
 void* yp_dir ; 
 int /*<<< orphan*/  yp_init_dbs () ; 
 int /*<<< orphan*/  yp_init_resolver () ; 
 int /*<<< orphan*/  yp_svc_run () ; 
 int ypdb_debug ; 

int
main(int argc, char *argv[])
{
	int ch;
	int error;
	int ntrans;
	
	void *nc_handle;
	struct netconfig *nconf;
	struct __rpc_sockinfo si;
	struct bindaddrlistent *blep;

	memset(&si, 0, sizeof(si));
	SLIST_INIT(&ble_head);

	while ((ch = getopt(argc, argv, "dh:np:P:")) != -1) {
		switch (ch) {
		case 'd':
			debug = ypdb_debug = 1;
			break;
		case 'h':
			blep = malloc(sizeof(*blep));
			if (blep == NULL)
				err(1, "malloc() failed: -h %s", optarg);
			blep->ble_hostname = optarg;
			SLIST_INSERT_HEAD(&ble_head, blep, ble_next);
			break;
		case 'n':
			do_dns = 1;
			break;
		case 'p':
			yp_dir = optarg;
			break;
		case 'P':
			servname = optarg;
			break;
		default:
			usage();
		}
	}
	/*
	 * Add "anyaddr" entry if no -h is specified.
	 */
	if (SLIST_EMPTY(&ble_head)) {
		blep = malloc(sizeof(*blep));
		if (blep == NULL)
			err(1, "malloc() failed");
		memset(blep, 0, sizeof(*blep));
		SLIST_INSERT_HEAD(&ble_head, blep, ble_next);
	}

	load_securenets();
	yp_init_resolver();
#ifdef DB_CACHE
	yp_init_dbs();
#endif
	nc_handle = setnetconfig();
	if (nc_handle == NULL)
		err(1, "cannot read %s", NETCONFIG);
	if (__rpc_fd2sockinfo(0, &si) != 0) {
		/* invoked from inetd */
		_rpcpmstart = 1;
		_rpcfdtype = si.si_socktype;
		_rpcaf = si.si_af;
		_rpcfd = 0;
		openlog("ypserv", LOG_PID, LOG_DAEMON);
	} else {
		/* standalone mode */
		if (!debug) {
			if (daemon(0,0)) {
				err(1,"cannot fork");
			}
			openlog("ypserv", LOG_PID, LOG_DAEMON);
		}
		_rpcpmstart = 0;
		_rpcaf = AF_INET;
		_rpcfd = RPC_ANYFD;
		unregister();
	}

	if (madvise(NULL, 0, MADV_PROTECT) != 0)
		_msgout("madvise(): %s", strerror(errno));

	/*
	 * Create RPC service for each transport.
	 */
	ntrans = 0;
	while((nconf = getnetconfig(nc_handle))) {
		if ((nconf->nc_flag & NC_VISIBLE)) {
			if (__rpc_nconf2sockinfo(nconf, &si) == 0) {
				_msgout("cannot get information for %s.  "
				    "Ignored.", nconf->nc_netid);
				continue;
			}
			if (_rpcpmstart) {
				if (si.si_socktype != _rpcfdtype ||
				    si.si_af != _rpcaf)
					continue;
			} else if (si.si_af != _rpcaf)
					continue;
			error = create_service(_rpcfd, nconf, &si);
			if (error) {
				endnetconfig(nc_handle);
				exit(1);
			}
			ntrans++;
		}
	}
	endnetconfig(nc_handle);
	while(!(SLIST_EMPTY(&ble_head)))
		SLIST_REMOVE_HEAD(&ble_head, ble_next);
	if (ntrans == 0) {
		_msgout("no transport is available.  Aborted.");
		exit(1);
	}
	if (_rpcpmstart) {
		(void) signal(SIGALRM, (SIG_PF) closedown);
		(void) alarm(_RPCSVC_CLOSEDOWN/2);
	}
/*
 * Make sure SIGPIPE doesn't blow us away while servicing TCP
 * connections.
 */
	(void) signal(SIGPIPE, SIG_IGN);
	(void) signal(SIGCHLD, (SIG_PF) reaper);
	(void) signal(SIGTERM, (SIG_PF) reaper);
	(void) signal(SIGINT, (SIG_PF) reaper);
	(void) signal(SIGHUP, (SIG_PF) reaper);
	yp_svc_run();
	_msgout("svc_run returned");
	exit(1);
	/* NOTREACHED */
}