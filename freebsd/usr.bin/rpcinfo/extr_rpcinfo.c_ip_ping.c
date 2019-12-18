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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u_long ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_in {void* sin_port; } ;
struct TYPE_2__ {scalar_t__ low; scalar_t__ high; } ;
struct rpc_err {TYPE_1__ re_vers; } ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int CLNT_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,struct timeval) ; 
 int /*<<< orphan*/  CLNT_CONTROL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLNT_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSET_FD_NCLOSE ; 
 scalar_t__ MAX_VERS ; 
 scalar_t__ MIN_VERS ; 
 int /*<<< orphan*/  NULLPROC ; 
 int RPC_ANYFD ; 
 int RPC_PROGVERSMISMATCH ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/ * clnt_com_create (struct sockaddr_in*,scalar_t__,scalar_t__,int*,char const*) ; 
 int /*<<< orphan*/  clnt_geterr (int /*<<< orphan*/ *,struct rpc_err*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_inet_address (struct sockaddr_in*,char*) ; 
 scalar_t__ getprognum (char*) ; 
 scalar_t__ getvers (char*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ pstatus (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
ip_ping(u_short portnum, const char *trans, int argc, char **argv)
{
	CLIENT *client;
	int fd = RPC_ANYFD;
	struct timeval to;
	struct sockaddr_in addr;
	enum clnt_stat rpc_stat;
	u_long prognum, vers, minvers, maxvers;
	struct rpc_err rpcerr;
	int failure = 0;

	if (argc < 2 || argc > 3)
		usage();
	to.tv_sec = 10;
	to.tv_usec = 0;
	prognum = getprognum(argv[1]);
	get_inet_address(&addr, argv[0]);
	if (argc == 2) {	/* Version number not known */
		/*
		 * A call to version 0 should fail with a program/version
		 * mismatch, and give us the range of versions supported.
		 */
		vers = MIN_VERS;
	} else {
		vers = getvers(argv[2]);
	}
	addr.sin_port = htons(portnum);
	client = clnt_com_create(&addr, prognum, vers, &fd, trans);
	rpc_stat = CLNT_CALL(client, NULLPROC, (xdrproc_t) xdr_void,
			(char *)NULL, (xdrproc_t) xdr_void, (char *)NULL,
			to);
	if (argc != 2) {
		/* Version number was known */
		if (pstatus(client, prognum, vers) < 0)
			exit(1);
		(void) CLNT_DESTROY(client);
		return;
	}
	/* Version number not known */
	(void) CLNT_CONTROL(client, CLSET_FD_NCLOSE, (char *)NULL);
	if (rpc_stat == RPC_PROGVERSMISMATCH) {
		clnt_geterr(client, &rpcerr);
		minvers = rpcerr.re_vers.low;
		maxvers = rpcerr.re_vers.high;
	} else if (rpc_stat == RPC_SUCCESS) {
		/*
		 * Oh dear, it DOES support version 0.
		 * Let's try version MAX_VERS.
		 */
		(void) CLNT_DESTROY(client);
		addr.sin_port = htons(portnum);
		client = clnt_com_create(&addr, prognum, MAX_VERS, &fd, trans);
		rpc_stat = CLNT_CALL(client, NULLPROC, (xdrproc_t) xdr_void,
				(char *)NULL, (xdrproc_t) xdr_void,
				(char *)NULL, to);
		if (rpc_stat == RPC_PROGVERSMISMATCH) {
			clnt_geterr(client, &rpcerr);
			minvers = rpcerr.re_vers.low;
			maxvers = rpcerr.re_vers.high;
		} else if (rpc_stat == RPC_SUCCESS) {
			/*
			 * It also supports version MAX_VERS.
			 * Looks like we have a wise guy.
			 * OK, we give them information on all
			 * 4 billion versions they support...
			 */
			minvers = 0;
			maxvers = MAX_VERS;
		} else {
			(void) pstatus(client, prognum, MAX_VERS);
			exit(1);
		}
	} else {
		(void) pstatus(client, prognum, (u_long)0);
		exit(1);
	}
	(void) CLNT_DESTROY(client);
	for (vers = minvers; vers <= maxvers; vers++) {
		addr.sin_port = htons(portnum);
		client = clnt_com_create(&addr, prognum, vers, &fd, trans);
		rpc_stat = CLNT_CALL(client, NULLPROC, (xdrproc_t) xdr_void,
				(char *)NULL, (xdrproc_t) xdr_void,
				(char *)NULL, to);
		if (pstatus(client, prognum, vers) < 0)
				failure = 1;
		(void) CLNT_DESTROY(client);
	}
	if (failure)
		exit(1);
	(void) close(fd);
	return;
}