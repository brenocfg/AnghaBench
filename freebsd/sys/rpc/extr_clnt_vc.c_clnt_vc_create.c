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
typedef  scalar_t__ uint32_t ;
struct timeval {int dummy; } ;
struct sockopt {int* sopt_val; int sopt_valsize; int /*<<< orphan*/  sopt_name; scalar_t__ sopt_level; void* sopt_dir; } ;
struct socket {int so_state; int so_error; int /*<<< orphan*/  so_rcv; TYPE_2__* so_proto; int /*<<< orphan*/  so_timeo; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct TYPE_9__ {scalar_t__ cb_vers; scalar_t__ cb_prog; int /*<<< orphan*/  cb_rpcvers; } ;
struct rpc_msg {TYPE_4__ rm_call; int /*<<< orphan*/  rm_direction; scalar_t__ rm_xid; } ;
struct TYPE_8__ {int tv_sec; int tv_usec; } ;
struct ct_data {char* ct_waitchan; int cl_refs; int /*<<< orphan*/  ct_lock; int /*<<< orphan*/  ct_pending; scalar_t__ ct_record_resid; int /*<<< orphan*/ * ct_record; struct socket* ct_socket; int /*<<< orphan*/  cl_auth; struct ct_data* cl_private; int /*<<< orphan*/ * cl_ops; void* ct_closeit; scalar_t__ ct_waitflag; int /*<<< orphan*/  ct_mpos; int /*<<< orphan*/  ct_mcallc; scalar_t__ ct_xid; int /*<<< orphan*/  ct_addr; TYPE_3__ ct_wait; scalar_t__ ct_upcallrefs; void* ct_closed; void* ct_closing; scalar_t__ ct_threads; } ;
struct __rpc_sockinfo {int /*<<< orphan*/  si_proto; int /*<<< orphan*/  si_af; } ;
typedef  int /*<<< orphan*/  sopt ;
typedef  scalar_t__ rpcvers_t ;
typedef  scalar_t__ rpcprog_t ;
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_6__ {int re_errno; } ;
struct TYPE_10__ {TYPE_1__ cf_error; int /*<<< orphan*/  cf_stat; } ;
struct TYPE_7__ {int pr_flags; scalar_t__ pr_protocol; } ;
typedef  struct ct_data CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CALL ; 
 int EINTR ; 
 int ERESTART ; 
 void* FALSE ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  MCALL_MSG_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int PCATCH ; 
 int PR_CONNREQUIRED ; 
 int PSOCK ; 
 int /*<<< orphan*/  RPC_MSG_VERSION ; 
 int /*<<< orphan*/  RPC_SYSTEMERROR ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_MTX (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 scalar_t__ SOL_SOCKET ; 
 void* SOPT_SET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_RCV ; 
 int SS_ISCONFIRMING ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  XDR_GETPOS (int /*<<< orphan*/ *) ; 
 scalar_t__ __RPC_GETXID (struct timeval*) ; 
 size_t __rpc_get_t_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __rpc_socket2sockinfo (struct socket*,struct __rpc_sockinfo*) ; 
 int /*<<< orphan*/  authnone_create () ; 
 int /*<<< orphan*/  bzero (struct sockopt*,int) ; 
 int /*<<< orphan*/  clnt_vc_ops ; 
 int /*<<< orphan*/  clnt_vc_soupcall ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 scalar_t__ mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (struct ct_data*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ rpc_createerr ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int soconnect (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int soreserve (struct socket*,size_t,size_t) ; 
 int /*<<< orphan*/  sosetopt (struct socket*,struct sockopt*) ; 
 int /*<<< orphan*/  soupcall_set (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ct_data*) ; 
 int /*<<< orphan*/  xdr_callhdr (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

CLIENT *
clnt_vc_create(
	struct socket *so,		/* open file descriptor */
	struct sockaddr *raddr,		/* servers address */
	const rpcprog_t prog,		/* program number */
	const rpcvers_t vers,		/* version number */
	size_t sendsz,			/* buffer recv size */
	size_t recvsz,			/* buffer send size */
	int intrflag)			/* interruptible */
{
	CLIENT *cl;			/* client handle */
	struct ct_data *ct = NULL;	/* client handle */
	struct timeval now;
	struct rpc_msg call_msg;
	static uint32_t disrupt;
	struct __rpc_sockinfo si;
	XDR xdrs;
	int error, interrupted, one = 1, sleep_flag;
	struct sockopt sopt;

	if (disrupt == 0)
		disrupt = (uint32_t)(long)raddr;

	cl = (CLIENT *)mem_alloc(sizeof (*cl));
	ct = (struct ct_data *)mem_alloc(sizeof (*ct));

	mtx_init(&ct->ct_lock, "ct->ct_lock", NULL, MTX_DEF);
	ct->ct_threads = 0;
	ct->ct_closing = FALSE;
	ct->ct_closed = FALSE;
	ct->ct_upcallrefs = 0;

	if ((so->so_state & (SS_ISCONNECTED|SS_ISCONFIRMING)) == 0) {
		error = soconnect(so, raddr, curthread);
		SOCK_LOCK(so);
		interrupted = 0;
		sleep_flag = PSOCK;
		if (intrflag != 0)
			sleep_flag |= PCATCH;
		while ((so->so_state & SS_ISCONNECTING)
		    && so->so_error == 0) {
			error = msleep(&so->so_timeo, SOCK_MTX(so),
			    sleep_flag, "connec", 0);
			if (error) {
				if (error == EINTR || error == ERESTART)
					interrupted = 1;
				break;
			}
		}
		if (error == 0) {
			error = so->so_error;
			so->so_error = 0;
		}
		SOCK_UNLOCK(so);
		if (error) {
			if (!interrupted)
				so->so_state &= ~SS_ISCONNECTING;
			rpc_createerr.cf_stat = RPC_SYSTEMERROR;
			rpc_createerr.cf_error.re_errno = error;
			goto err;
		}
	}

	if (!__rpc_socket2sockinfo(so, &si)) {
		goto err;
	}

	if (so->so_proto->pr_flags & PR_CONNREQUIRED) {
		bzero(&sopt, sizeof(sopt));
		sopt.sopt_dir = SOPT_SET;
		sopt.sopt_level = SOL_SOCKET;
		sopt.sopt_name = SO_KEEPALIVE;
		sopt.sopt_val = &one;
		sopt.sopt_valsize = sizeof(one);
		sosetopt(so, &sopt);
	}

	if (so->so_proto->pr_protocol == IPPROTO_TCP) {
		bzero(&sopt, sizeof(sopt));
		sopt.sopt_dir = SOPT_SET;
		sopt.sopt_level = IPPROTO_TCP;
		sopt.sopt_name = TCP_NODELAY;
		sopt.sopt_val = &one;
		sopt.sopt_valsize = sizeof(one);
		sosetopt(so, &sopt);
	}

	ct->ct_closeit = FALSE;

	/*
	 * Set up private data struct
	 */
	ct->ct_socket = so;
	ct->ct_wait.tv_sec = -1;
	ct->ct_wait.tv_usec = -1;
	memcpy(&ct->ct_addr, raddr, raddr->sa_len);

	/*
	 * Initialize call message
	 */
	getmicrotime(&now);
	ct->ct_xid = ((uint32_t)++disrupt) ^ __RPC_GETXID(&now);
	call_msg.rm_xid = ct->ct_xid;
	call_msg.rm_direction = CALL;
	call_msg.rm_call.cb_rpcvers = RPC_MSG_VERSION;
	call_msg.rm_call.cb_prog = (uint32_t)prog;
	call_msg.rm_call.cb_vers = (uint32_t)vers;

	/*
	 * pre-serialize the static part of the call msg and stash it away
	 */
	xdrmem_create(&xdrs, ct->ct_mcallc, MCALL_MSG_SIZE,
	    XDR_ENCODE);
	if (! xdr_callhdr(&xdrs, &call_msg)) {
		if (ct->ct_closeit) {
			soclose(ct->ct_socket);
		}
		goto err;
	}
	ct->ct_mpos = XDR_GETPOS(&xdrs);
	XDR_DESTROY(&xdrs);
	ct->ct_waitchan = "rpcrecv";
	ct->ct_waitflag = 0;

	/*
	 * Create a client handle which uses xdrrec for serialization
	 * and authnone for authentication.
	 */
	sendsz = __rpc_get_t_size(si.si_af, si.si_proto, (int)sendsz);
	recvsz = __rpc_get_t_size(si.si_af, si.si_proto, (int)recvsz);
	error = soreserve(ct->ct_socket, sendsz, recvsz);
	if (error != 0) {
		if (ct->ct_closeit) {
			soclose(ct->ct_socket);
		}
		goto err;
	}
	cl->cl_refs = 1;
	cl->cl_ops = &clnt_vc_ops;
	cl->cl_private = ct;
	cl->cl_auth = authnone_create();

	SOCKBUF_LOCK(&ct->ct_socket->so_rcv);
	soupcall_set(ct->ct_socket, SO_RCV, clnt_vc_soupcall, ct);
	SOCKBUF_UNLOCK(&ct->ct_socket->so_rcv);

	ct->ct_record = NULL;
	ct->ct_record_resid = 0;
	TAILQ_INIT(&ct->ct_pending);
	return (cl);

err:
	mtx_destroy(&ct->ct_lock);
	mem_free(ct, sizeof (struct ct_data));
	mem_free(cl, sizeof (CLIENT));

	return ((CLIENT *)NULL);
}