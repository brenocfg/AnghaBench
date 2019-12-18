#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct timeval {int dummy; } ;
struct sockbuf {scalar_t__ sb_upcall; scalar_t__ sb_upcallarg; } ;
struct socket {struct sockbuf so_rcv; } ;
struct sockaddr {scalar_t__ sa_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  cb_vers; int /*<<< orphan*/  cb_prog; } ;
struct rpc_msg {TYPE_3__ rm_call; int /*<<< orphan*/  rm_xid; } ;
struct TYPE_7__ {int tv_sec; int tv_usec; } ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_usec; } ;
struct cu_socket {size_t cu_sendsz; size_t cu_recvsz; char* cu_waitchan; int cu_cwnd; int cs_refs; int cl_refs; int /*<<< orphan*/ * cl_netid; int /*<<< orphan*/ * cl_tp; int /*<<< orphan*/  cl_auth; scalar_t__ cl_private; int /*<<< orphan*/ * cl_ops; int /*<<< orphan*/  cs_pending; scalar_t__ cs_upcallrefs; int /*<<< orphan*/  cs_lock; struct socket* cu_socket; void* cu_closeit; int /*<<< orphan*/  cu_mcalllen; int /*<<< orphan*/  cu_mcallc; int /*<<< orphan*/  cu_xid; void* cu_cwnd_wait; scalar_t__ cu_sent; scalar_t__ cu_waitflag; void* cu_connected; void* cu_connect; void* cu_async; TYPE_2__ cu_total; TYPE_1__ cu_wait; scalar_t__ cu_rlen; int /*<<< orphan*/  cu_raddr; void* cu_closed; void* cu_closing; scalar_t__ cu_threads; } ;
struct cu_data {size_t cu_sendsz; size_t cu_recvsz; char* cu_waitchan; int cu_cwnd; int cs_refs; int cl_refs; int /*<<< orphan*/ * cl_netid; int /*<<< orphan*/ * cl_tp; int /*<<< orphan*/  cl_auth; scalar_t__ cl_private; int /*<<< orphan*/ * cl_ops; int /*<<< orphan*/  cs_pending; scalar_t__ cs_upcallrefs; int /*<<< orphan*/  cs_lock; struct socket* cu_socket; void* cu_closeit; int /*<<< orphan*/  cu_mcalllen; int /*<<< orphan*/  cu_mcallc; int /*<<< orphan*/  cu_xid; void* cu_cwnd_wait; scalar_t__ cu_sent; scalar_t__ cu_waitflag; void* cu_connected; void* cu_connect; void* cu_async; TYPE_2__ cu_total; TYPE_1__ cu_wait; scalar_t__ cu_rlen; int /*<<< orphan*/  cu_raddr; void* cu_closed; void* cu_closing; scalar_t__ cu_threads; } ;
struct __rpc_sockinfo {int /*<<< orphan*/  si_proto; int /*<<< orphan*/  si_af; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_9__ {int re_errno; } ;
struct TYPE_10__ {TYPE_4__ cf_error; void* cf_stat; } ;
typedef  struct cu_socket CLIENT ;

/* Variables and functions */
 void* FALSE ; 
 int MAXCWND ; 
 int /*<<< orphan*/  MCALL_MSG_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 void* RPC_CANTENCODEARGS ; 
 void* RPC_FAILED ; 
 void* RPC_TLIERROR ; 
 void* RPC_UNKNOWNADDR ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  XDR_GETPOS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __RPC_GETXID (struct timeval*) ; 
 size_t __rpc_get_t_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __rpc_socket2sockinfo (struct socket*,struct __rpc_sockinfo*) ; 
 int /*<<< orphan*/  authnone_create () ; 
 int /*<<< orphan*/  clnt_dg_ops ; 
 scalar_t__ clnt_dg_soupcall ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 struct cu_socket* mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (struct cu_socket*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t rounddown (size_t,int) ; 
 TYPE_5__ rpc_createerr ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soupcall_set (struct socket*,int /*<<< orphan*/ ,scalar_t__,struct cu_socket*) ; 
 int /*<<< orphan*/  xdr_callhdr (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

CLIENT *
clnt_dg_create(
	struct socket *so,
	struct sockaddr *svcaddr,	/* servers address */
	rpcprog_t program,		/* program number */
	rpcvers_t version,		/* version number */
	size_t sendsz,			/* buffer recv size */
	size_t recvsz)			/* buffer send size */
{
	CLIENT *cl = NULL;		/* client handle */
	struct cu_data *cu = NULL;	/* private data */
	struct cu_socket *cs = NULL;
	struct sockbuf *sb;
	struct timeval now;
	struct rpc_msg call_msg;
	struct __rpc_sockinfo si;
	XDR xdrs;
	int error;

	if (svcaddr == NULL) {
		rpc_createerr.cf_stat = RPC_UNKNOWNADDR;
		return (NULL);
	}

	if (!__rpc_socket2sockinfo(so, &si)) {
		rpc_createerr.cf_stat = RPC_TLIERROR;
		rpc_createerr.cf_error.re_errno = 0;
		return (NULL);
	}

	/*
	 * Find the receive and the send size
	 */
	sendsz = __rpc_get_t_size(si.si_af, si.si_proto, (int)sendsz);
	recvsz = __rpc_get_t_size(si.si_af, si.si_proto, (int)recvsz);
	if ((sendsz == 0) || (recvsz == 0)) {
		rpc_createerr.cf_stat = RPC_TLIERROR; /* XXX */
		rpc_createerr.cf_error.re_errno = 0;
		return (NULL);
	}

	cl = mem_alloc(sizeof (CLIENT));

	/*
	 * Should be multiple of 4 for XDR.
	 */
	sendsz = rounddown(sendsz + 3, 4);
	recvsz = rounddown(recvsz + 3, 4);
	cu = mem_alloc(sizeof (*cu));
	cu->cu_threads = 0;
	cu->cu_closing = FALSE;
	cu->cu_closed = FALSE;
	(void) memcpy(&cu->cu_raddr, svcaddr, (size_t)svcaddr->sa_len);
	cu->cu_rlen = svcaddr->sa_len;
	/* Other values can also be set through clnt_control() */
	cu->cu_wait.tv_sec = 3;	/* heuristically chosen */
	cu->cu_wait.tv_usec = 0;
	cu->cu_total.tv_sec = -1;
	cu->cu_total.tv_usec = -1;
	cu->cu_sendsz = sendsz;
	cu->cu_recvsz = recvsz;
	cu->cu_async = FALSE;
	cu->cu_connect = FALSE;
	cu->cu_connected = FALSE;
	cu->cu_waitchan = "rpcrecv";
	cu->cu_waitflag = 0;
	cu->cu_cwnd = MAXCWND / 2;
	cu->cu_sent = 0;
	cu->cu_cwnd_wait = FALSE;
	(void) getmicrotime(&now);
	cu->cu_xid = __RPC_GETXID(&now);
	call_msg.rm_xid = cu->cu_xid;
	call_msg.rm_call.cb_prog = program;
	call_msg.rm_call.cb_vers = version;
	xdrmem_create(&xdrs, cu->cu_mcallc, MCALL_MSG_SIZE, XDR_ENCODE);
	if (! xdr_callhdr(&xdrs, &call_msg)) {
		rpc_createerr.cf_stat = RPC_CANTENCODEARGS;  /* XXX */
		rpc_createerr.cf_error.re_errno = 0;
		goto err2;
	}
	cu->cu_mcalllen = XDR_GETPOS(&xdrs);

	/*
	 * By default, closeit is always FALSE. It is users responsibility
	 * to do a close on it, else the user may use clnt_control
	 * to let clnt_destroy do it for him/her.
	 */
	cu->cu_closeit = FALSE;
	cu->cu_socket = so;
	error = soreserve(so, (u_long)sendsz, (u_long)recvsz);
	if (error != 0) {
		rpc_createerr.cf_stat = RPC_FAILED;
		rpc_createerr.cf_error.re_errno = error;
		goto err2;
	}

	sb = &so->so_rcv;
	SOCKBUF_LOCK(&so->so_rcv);
recheck_socket:
	if (sb->sb_upcall) {
		if (sb->sb_upcall != clnt_dg_soupcall) {
			SOCKBUF_UNLOCK(&so->so_rcv);
			printf("clnt_dg_create(): socket already has an incompatible upcall\n");
			goto err2;
		}
		cs = (struct cu_socket *) sb->sb_upcallarg;
		mtx_lock(&cs->cs_lock);
		cs->cs_refs++;
		mtx_unlock(&cs->cs_lock);
	} else {
		/*
		 * We are the first on this socket - allocate the
		 * structure and install it in the socket.
		 */
		SOCKBUF_UNLOCK(&so->so_rcv);
		cs = mem_alloc(sizeof(*cs));
		SOCKBUF_LOCK(&so->so_rcv);
		if (sb->sb_upcall) {
			/*
			 * We have lost a race with some other client.
			 */
			mem_free(cs, sizeof(*cs));
			goto recheck_socket;
		}
		mtx_init(&cs->cs_lock, "cs->cs_lock", NULL, MTX_DEF);
		cs->cs_refs = 1;
		cs->cs_upcallrefs = 0;
		TAILQ_INIT(&cs->cs_pending);
		soupcall_set(so, SO_RCV, clnt_dg_soupcall, cs);
	}
	SOCKBUF_UNLOCK(&so->so_rcv);

	cl->cl_refs = 1;
	cl->cl_ops = &clnt_dg_ops;
	cl->cl_private = (caddr_t)(void *)cu;
	cl->cl_auth = authnone_create();
	cl->cl_tp = NULL;
	cl->cl_netid = NULL;
	return (cl);
err2:
	mem_free(cl, sizeof (CLIENT));
	mem_free(cu, sizeof (*cu));

	return (NULL);
}