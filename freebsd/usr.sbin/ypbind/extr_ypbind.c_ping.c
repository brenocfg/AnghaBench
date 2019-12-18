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
struct timeval {scalar_t__ tv_usec; void* tv_sec; } ;
struct _dom_binding {int dom_vers; char* dom_domain; scalar_t__ dom_alive; int /*<<< orphan*/  dom_server_addr; scalar_t__ dom_broadcast_pid; } ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 void* FAIL_THRESHOLD ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  RPCSMALLMSGSIZE ; 
 int RPC_ANYSOCK ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  YPPROC_DOMAIN ; 
 int /*<<< orphan*/  YPPROG ; 
 int /*<<< orphan*/  YPVERS ; 
 int /*<<< orphan*/  broadcast (struct _dom_binding*) ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,scalar_t__*,struct timeval) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clntudp_bufcreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_bool ; 
 scalar_t__ xdr_domainname ; 

int
ping(struct _dom_binding *ypdb)
{
	bool_t out;
	struct timeval interval, timeout;
	enum clnt_stat stat;
	int rpcsock = RPC_ANYSOCK;
	CLIENT *client_handle;

	interval.tv_sec = FAIL_THRESHOLD;
	interval.tv_usec = 0;
	timeout.tv_sec = FAIL_THRESHOLD;
	timeout.tv_usec = 0;

	if (ypdb->dom_broadcast_pid)
		return(1);

	if ((client_handle = clntudp_bufcreate(&ypdb->dom_server_addr,
		YPPROG, YPVERS, interval, &rpcsock, RPCSMALLMSGSIZE,
		RPCSMALLMSGSIZE)) == (CLIENT *)NULL) {
		/* Can't get a handle: we're dead. */
		ypdb->dom_alive = 0;
		ypdb->dom_vers = -1;
		broadcast(ypdb);
		return(1);
	}

	{
		char *ptr;

		ptr = ypdb->dom_domain;

		stat = clnt_call(client_handle, YPPROC_DOMAIN,
		    (xdrproc_t)xdr_domainname, &ptr,
		    (xdrproc_t)xdr_bool, &out, timeout);
		if (stat != RPC_SUCCESS || out == FALSE) {
			ypdb->dom_alive = 0;
			ypdb->dom_vers = -1;
			clnt_destroy(client_handle);
			broadcast(ypdb);
			return(1);
		}
	}

	clnt_destroy(client_handle);
	return(0);
}