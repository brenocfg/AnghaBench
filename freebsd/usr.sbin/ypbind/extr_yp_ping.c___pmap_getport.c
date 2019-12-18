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
typedef  scalar_t__ u_short ;
typedef  void* u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct pmap {scalar_t__ pm_port; int /*<<< orphan*/  pm_prot; void* pm_vers; void* pm_prog; } ;
struct TYPE_2__ {int /*<<< orphan*/  cf_stat; int /*<<< orphan*/  cf_error; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ CLNT_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pmap*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLNT_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PMAPPORT ; 
 int /*<<< orphan*/  PMAPPROC_GETPORT ; 
 int /*<<< orphan*/  PMAPPROG ; 
 int /*<<< orphan*/  PMAPVERS ; 
 int /*<<< orphan*/  RPCSMALLMSGSIZE ; 
 int /*<<< orphan*/  RPC_PMAPFAILURE ; 
 int /*<<< orphan*/  RPC_PROGNOTREGISTERED ; 
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  clnt_geterr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clntudp_bufcreate (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_1__ rpc_createerr ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  tottimeout ; 
 scalar_t__ xdr_pmap ; 
 scalar_t__ xdr_u_short ; 

__attribute__((used)) static u_short
__pmap_getport(struct sockaddr_in *address, u_long program, u_long version,
    u_int protocol)
{
	u_short port = 0;
	int sock = -1;
	register CLIENT *client;
	struct pmap parms;

	address->sin_port = htons(PMAPPORT);

	client = clntudp_bufcreate(address, PMAPPROG,
	    PMAPVERS, timeout, &sock, RPCSMALLMSGSIZE, RPCSMALLMSGSIZE);
	if (client != (CLIENT *)NULL) {
		parms.pm_prog = program;
		parms.pm_vers = version;
		parms.pm_prot = protocol;
		parms.pm_port = 0;  /* not needed or used */
		if (CLNT_CALL(client, PMAPPROC_GETPORT,
			(xdrproc_t)xdr_pmap, &parms,
			(xdrproc_t)xdr_u_short, &port,
			tottimeout) != RPC_SUCCESS){
			rpc_createerr.cf_stat = RPC_PMAPFAILURE;
			clnt_geterr(client, &rpc_createerr.cf_error);
		} else if (port == 0) {
			rpc_createerr.cf_stat = RPC_PROGNOTREGISTERED;
		}
		CLNT_DESTROY(client);
	}
	if (sock != -1)
		(void)close(sock);
	address->sin_port = 0;
	return (port);
}