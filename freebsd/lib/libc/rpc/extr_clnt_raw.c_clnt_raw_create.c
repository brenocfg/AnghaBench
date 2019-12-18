#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int32_t ;
struct TYPE_5__ {void* cb_vers; void* cb_prog; int /*<<< orphan*/  cb_rpcvers; } ;
struct rpc_msg {TYPE_1__ rm_call; int /*<<< orphan*/  rm_direction; } ;
struct TYPE_6__ {char* mashl_callmsg; } ;
struct TYPE_7__ {int /*<<< orphan*/  cl_auth; int /*<<< orphan*/  cl_ops; } ;
struct clntraw_private {char* _raw_buf; int /*<<< orphan*/  mcnt; TYPE_2__ u; TYPE_3__ client_object; int /*<<< orphan*/  xdr_stream; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  scalar_t__ rpcprog_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  TYPE_3__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CALL ; 
 int MCALL_MSG_SIZE ; 
 int /*<<< orphan*/  RPC_MSG_VERSION ; 
 int UDPMSGSIZE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  XDR_FREE ; 
 int /*<<< orphan*/  XDR_GETPOS (int /*<<< orphan*/ *) ; 
 char* __rpc_rawcombuf ; 
 int /*<<< orphan*/  authnone_create () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  clnt_raw_ops () ; 
 int /*<<< orphan*/  clntraw_lock ; 
 struct clntraw_private* clntraw_private ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  xdr_callhdr (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

CLIENT *
clnt_raw_create(rpcprog_t prog, rpcvers_t vers)
{
	struct clntraw_private *clp;
	struct rpc_msg call_msg;
	XDR *xdrs;
	CLIENT	*client;

	mutex_lock(&clntraw_lock);
	if ((clp = clntraw_private) == NULL) {
		clp = (struct clntraw_private *)calloc(1, sizeof (*clp));
		if (clp == NULL) {
			mutex_unlock(&clntraw_lock);
			return NULL;
		}
		if (__rpc_rawcombuf == NULL)
			__rpc_rawcombuf =
			    (char *)calloc(UDPMSGSIZE, sizeof (char));
		clp->_raw_buf = __rpc_rawcombuf;
		clntraw_private = clp;
	}
	xdrs = &clp->xdr_stream;
	client = &clp->client_object;

	/*
	 * pre-serialize the static part of the call msg and stash it away
	 */
	call_msg.rm_direction = CALL;
	call_msg.rm_call.cb_rpcvers = RPC_MSG_VERSION;
	/* XXX: prog and vers have been long historically :-( */
	call_msg.rm_call.cb_prog = (u_int32_t)prog;
	call_msg.rm_call.cb_vers = (u_int32_t)vers;
	xdrmem_create(xdrs, clp->u.mashl_callmsg, MCALL_MSG_SIZE, XDR_ENCODE); 
	if (! xdr_callhdr(xdrs, &call_msg))
		warnx("clntraw_create - Fatal header serialization error.");
	clp->mcnt = XDR_GETPOS(xdrs);
	XDR_DESTROY(xdrs);

	/*
	 * Set xdrmem for client/server shared buffer
	 */
	xdrmem_create(xdrs, clp->_raw_buf, UDPMSGSIZE, XDR_FREE);

	/*
	 * create client handle
	 */
	client->cl_ops = clnt_raw_ops();
	client->cl_auth = authnone_create();
	mutex_unlock(&clntraw_lock);
	return (client);
}