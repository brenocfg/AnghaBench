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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  resultproc_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int /*<<< orphan*/  NULLPROC ; 
 int RPC_SUCCESS ; 
 int RPC_TIMEDOUT ; 
 int /*<<< orphan*/  clnt_sperrno (int) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getprognum (char*) ; 
 int /*<<< orphan*/  getvers (char*) ; 
 scalar_t__ reply_proc ; 
 int rpc_broadcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
brdcst(int argc, char **argv)
{
	enum clnt_stat rpc_stat;
	u_long prognum, vers;

	if (argc != 2)
		usage();
	prognum = getprognum(argv[0]);
	vers = getvers(argv[1]);
	rpc_stat = rpc_broadcast(prognum, vers, NULLPROC,
		(xdrproc_t) xdr_void, (char *)NULL, (xdrproc_t) xdr_void,
		(char *)NULL, (resultproc_t) reply_proc, NULL);
	if ((rpc_stat != RPC_SUCCESS) && (rpc_stat != RPC_TIMEDOUT))
		errx(1, "broadcast failed: %s", clnt_sperrno(rpc_stat));
	exit(0);
}