#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct socket {int so_state; TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct TYPE_12__ {int xp_upcallset; int /*<<< orphan*/  xp_lock; int /*<<< orphan*/  xp_ltaddr; int /*<<< orphan*/ * xp_ops; int /*<<< orphan*/ * xp_p2; int /*<<< orphan*/ * xp_p1; struct socket* xp_socket; int /*<<< orphan*/ * xp_pool; } ;
struct TYPE_11__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_10__ {int (* pru_peeraddr ) (struct socket*,struct sockaddr**) ;int (* pru_sockaddr ) (struct socket*,struct sockaddr**) ;} ;
typedef  TYPE_3__ SVCXPRT ;
typedef  int /*<<< orphan*/  SVCPOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  SOLISTEN_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOLISTEN_UNLOCK (struct socket*) ; 
 int SS_ISCONNECTED ; 
 int SS_ISDISCONNECTED ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solisten (struct socket*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solisten_upcall_set (struct socket*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub1 (struct socket*,struct sockaddr**) ; 
 int stub2 (struct socket*,struct sockaddr**) ; 
 TYPE_3__* svc_vc_create_conn (int /*<<< orphan*/ *,struct socket*,struct sockaddr*) ; 
 int /*<<< orphan*/  svc_vc_rendezvous_ops ; 
 int /*<<< orphan*/  svc_vc_rendezvous_soupcall ; 
 TYPE_3__* svc_xprt_alloc () ; 
 int /*<<< orphan*/  svc_xprt_free (TYPE_3__*) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xprt_register (TYPE_3__*) ; 

SVCXPRT *
svc_vc_create(SVCPOOL *pool, struct socket *so, size_t sendsize,
    size_t recvsize)
{
	SVCXPRT *xprt;
	struct sockaddr* sa;
	int error;

	SOCK_LOCK(so);
	if (so->so_state & (SS_ISCONNECTED|SS_ISDISCONNECTED)) {
		SOCK_UNLOCK(so);
		CURVNET_SET(so->so_vnet);
		error = so->so_proto->pr_usrreqs->pru_peeraddr(so, &sa);
		CURVNET_RESTORE();
		if (error)
			return (NULL);
		xprt = svc_vc_create_conn(pool, so, sa);
		free(sa, M_SONAME);
		return (xprt);
	}
	SOCK_UNLOCK(so);

	xprt = svc_xprt_alloc();
	sx_init(&xprt->xp_lock, "xprt->xp_lock");
	xprt->xp_pool = pool;
	xprt->xp_socket = so;
	xprt->xp_p1 = NULL;
	xprt->xp_p2 = NULL;
	xprt->xp_ops = &svc_vc_rendezvous_ops;

	CURVNET_SET(so->so_vnet);
	error = so->so_proto->pr_usrreqs->pru_sockaddr(so, &sa);
	CURVNET_RESTORE();
	if (error) {
		goto cleanup_svc_vc_create;
	}

	memcpy(&xprt->xp_ltaddr, sa, sa->sa_len);
	free(sa, M_SONAME);

	xprt_register(xprt);

	solisten(so, -1, curthread);

	SOLISTEN_LOCK(so);
	xprt->xp_upcallset = 1;
	solisten_upcall_set(so, svc_vc_rendezvous_soupcall, xprt);
	SOLISTEN_UNLOCK(so);

	return (xprt);

cleanup_svc_vc_create:
	sx_destroy(&xprt->xp_lock);
	svc_xprt_free(xprt);

	return (NULL);
}