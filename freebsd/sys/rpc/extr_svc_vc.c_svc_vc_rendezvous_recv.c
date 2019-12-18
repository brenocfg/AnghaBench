#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct rpc_msg {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_11__ {int /*<<< orphan*/  sol_comp; } ;
struct TYPE_10__ {int /*<<< orphan*/  xp_pool; int /*<<< orphan*/  xp_lock; TYPE_5__* xp_socket; scalar_t__ xp_upcallset; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  SOLISTEN_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  SOLISTEN_UNLOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  SVC_RELEASE (TYPE_1__*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int soaccept (struct socket*,struct sockaddr**) ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int /*<<< orphan*/  soupcall_clear (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int svc_vc_accept (TYPE_5__*,struct socket**) ; 
 TYPE_1__* svc_vc_create_conn (int /*<<< orphan*/ ,struct socket*,struct sockaddr*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_inactive_self (TYPE_1__*) ; 

__attribute__((used)) static bool_t
svc_vc_rendezvous_recv(SVCXPRT *xprt, struct rpc_msg *msg,
    struct sockaddr **addrp, struct mbuf **mp)
{
	struct socket *so = NULL;
	struct sockaddr *sa = NULL;
	int error;
	SVCXPRT *new_xprt;

	/*
	 * The socket upcall calls xprt_active() which will eventually
	 * cause the server to call us here. We attempt to accept a
	 * connection from the socket and turn it into a new
	 * transport. If the accept fails, we have drained all pending
	 * connections so we call xprt_inactive().
	 */
	sx_xlock(&xprt->xp_lock);

	error = svc_vc_accept(xprt->xp_socket, &so);

	if (error == EWOULDBLOCK) {
		/*
		 * We must re-test for new connections after taking
		 * the lock to protect us in the case where a new
		 * connection arrives after our call to accept fails
		 * with EWOULDBLOCK.
		 */
		SOLISTEN_LOCK(xprt->xp_socket);
		if (TAILQ_EMPTY(&xprt->xp_socket->sol_comp))
			xprt_inactive_self(xprt);
		SOLISTEN_UNLOCK(xprt->xp_socket);
		sx_xunlock(&xprt->xp_lock);
		return (FALSE);
	}

	if (error) {
		SOLISTEN_LOCK(xprt->xp_socket);
		if (xprt->xp_upcallset) {
			xprt->xp_upcallset = 0;
			soupcall_clear(xprt->xp_socket, SO_RCV);
		}
		SOLISTEN_UNLOCK(xprt->xp_socket);
		xprt_inactive_self(xprt);
		sx_xunlock(&xprt->xp_lock);
		return (FALSE);
	}

	sx_xunlock(&xprt->xp_lock);

	sa = NULL;
	error = soaccept(so, &sa);

	if (error) {
		/*
		 * XXX not sure if I need to call sofree or soclose here.
		 */
		if (sa)
			free(sa, M_SONAME);
		return (FALSE);
	}

	/*
	 * svc_vc_create_conn will call xprt_register - we don't need
	 * to do anything with the new connection except derefence it.
	 */
	new_xprt = svc_vc_create_conn(xprt->xp_pool, so, sa);
	if (!new_xprt) {
		soclose(so);
	} else {
		SVC_RELEASE(new_xprt);
	}

	free(sa, M_SONAME);

	return (FALSE); /* there is never an rpc msg to be processed */
}