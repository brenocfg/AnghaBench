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
struct netconfig {int dummy; } ;
struct netbuf {int dummy; } ;
typedef  int /*<<< orphan*/  rpcproc_t ;
struct TYPE_2__ {int /*<<< orphan*/  cf_stat; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLNT_DESTROY (int /*<<< orphan*/ *) ; 
 scalar_t__ RPCBPROC_TADDR2UADDR ; 
 int /*<<< orphan*/  RPC_UNKNOWNADDR ; 
 int /*<<< orphan*/  RPC_UNKNOWNPROTO ; 
 int /*<<< orphan*/ * local_rpcb () ; 
 TYPE_1__ rpc_createerr ; 
 int /*<<< orphan*/  tottimeout ; 
 scalar_t__ xdr_netbuf ; 
 scalar_t__ xdr_wrapstring ; 

char *
rpcb_taddr2uaddr(struct netconfig *nconf, struct netbuf *taddr)
{
	CLIENT *client;
	char *uaddr = NULL;


	/* parameter checking */
	if (nconf == NULL) {
		rpc_createerr.cf_stat = RPC_UNKNOWNPROTO;
		return (NULL);
	}
	if (taddr == NULL) {
		rpc_createerr.cf_stat = RPC_UNKNOWNADDR;
		return (NULL);
	}
	client = local_rpcb();
	if (! client) {
		return (NULL);
	}

	CLNT_CALL(client, (rpcproc_t)RPCBPROC_TADDR2UADDR,
	    (xdrproc_t) xdr_netbuf, (char *)(void *)taddr,
	    (xdrproc_t) xdr_wrapstring, (char *)(void *)&uaddr, tottimeout);
	CLNT_DESTROY(client);
	return (uaddr);
}