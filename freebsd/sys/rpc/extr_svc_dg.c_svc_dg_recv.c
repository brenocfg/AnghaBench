#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct uio {int uio_resid; int /*<<< orphan*/  uio_td; } ;
struct sockaddr {int dummy; } ;
struct rpc_msg {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_8__ {int /*<<< orphan*/  so_rcv; } ;
struct TYPE_7__ {int /*<<< orphan*/  xp_lock; TYPE_4__* xp_socket; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  FALSE ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  soreadable (TYPE_4__*) ; 
 int soreceive (TYPE_4__*,struct sockaddr**,struct uio*,struct mbuf**,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  soupcall_clear (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_callmsg (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 int /*<<< orphan*/  xdrmbuf_create (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* xdrmbuf_getall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_inactive_self (TYPE_1__*) ; 

__attribute__((used)) static bool_t
svc_dg_recv(SVCXPRT *xprt, struct rpc_msg *msg,
    struct sockaddr **addrp, struct mbuf **mp)
{
	struct uio uio;
	struct sockaddr *raddr;
	struct mbuf *mreq;
	XDR xdrs;
	int error, rcvflag;

	/*
	 * Serialise access to the socket.
	 */
	sx_xlock(&xprt->xp_lock);

	/*
	 * The socket upcall calls xprt_active() which will eventually
	 * cause the server to call us here. We attempt to read a
	 * packet from the socket and process it. If the read fails,
	 * we have drained all pending requests so we call
	 * xprt_inactive().
	 */
	uio.uio_resid = 1000000000;
	uio.uio_td = curthread;
	mreq = NULL;
	rcvflag = MSG_DONTWAIT;
	error = soreceive(xprt->xp_socket, &raddr, &uio, &mreq, NULL, &rcvflag);

	if (error == EWOULDBLOCK) {
		/*
		 * We must re-test for readability after taking the
		 * lock to protect us in the case where a new packet
		 * arrives on the socket after our call to soreceive
		 * fails with EWOULDBLOCK. The pool lock protects us
		 * from racing the upcall after our soreadable() call
		 * returns false.
		 */
		SOCKBUF_LOCK(&xprt->xp_socket->so_rcv);
		if (!soreadable(xprt->xp_socket))
			xprt_inactive_self(xprt);
		SOCKBUF_UNLOCK(&xprt->xp_socket->so_rcv);
		sx_xunlock(&xprt->xp_lock);
		return (FALSE);
	}

	if (error) {
		SOCKBUF_LOCK(&xprt->xp_socket->so_rcv);
		soupcall_clear(xprt->xp_socket, SO_RCV);
		SOCKBUF_UNLOCK(&xprt->xp_socket->so_rcv);
		xprt_inactive_self(xprt);
		sx_xunlock(&xprt->xp_lock);
		return (FALSE);
	}

	sx_xunlock(&xprt->xp_lock);

	xdrmbuf_create(&xdrs, mreq, XDR_DECODE);
	if (! xdr_callmsg(&xdrs, msg)) {
		XDR_DESTROY(&xdrs);
		return (FALSE);
	}

	*addrp = raddr;
	*mp = xdrmbuf_getall(&xdrs);
	XDR_DESTROY(&xdrs);

	return (TRUE);
}