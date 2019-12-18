#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  so_rcv; TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct __rpc_sockinfo {int /*<<< orphan*/  si_proto; int /*<<< orphan*/  si_af; } ;
struct TYPE_11__ {int /*<<< orphan*/  xp_ltaddr; int /*<<< orphan*/ * xp_ops; int /*<<< orphan*/ * xp_p2; int /*<<< orphan*/ * xp_p1; struct socket* xp_socket; int /*<<< orphan*/ * xp_pool; int /*<<< orphan*/  xp_lock; } ;
struct TYPE_10__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_9__ {int (* pru_sockaddr ) (struct socket*,struct sockaddr**) ;} ;
typedef  TYPE_3__ SVCXPRT ;
typedef  int /*<<< orphan*/  SVCPOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  __no_mem_str ; 
 size_t __rpc_get_t_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __rpc_socket2sockinfo (struct socket*,struct __rpc_sockinfo*) ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soupcall_set (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub1 (struct socket*,struct sockaddr**) ; 
 int /*<<< orphan*/  svc_dg_err1 ; 
 int /*<<< orphan*/  svc_dg_err2 ; 
 int /*<<< orphan*/  svc_dg_ops ; 
 int /*<<< orphan*/  svc_dg_soupcall ; 
 char* svc_dg_str ; 
 TYPE_3__* svc_xprt_alloc () ; 
 int /*<<< orphan*/  svc_xprt_free (TYPE_3__*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xprt_register (TYPE_3__*) ; 

SVCXPRT *
svc_dg_create(SVCPOOL *pool, struct socket *so, size_t sendsize,
    size_t recvsize)
{
	SVCXPRT *xprt;
	struct __rpc_sockinfo si;
	struct sockaddr* sa;
	int error;

	if (!__rpc_socket2sockinfo(so, &si)) {
		printf(svc_dg_str, svc_dg_err1);
		return (NULL);
	}
	/*
	 * Find the receive and the send size
	 */
	sendsize = __rpc_get_t_size(si.si_af, si.si_proto, (int)sendsize);
	recvsize = __rpc_get_t_size(si.si_af, si.si_proto, (int)recvsize);
	if ((sendsize == 0) || (recvsize == 0)) {
		printf(svc_dg_str, svc_dg_err2);
		return (NULL);
	}

	xprt = svc_xprt_alloc();
	sx_init(&xprt->xp_lock, "xprt->xp_lock");
	xprt->xp_pool = pool;
	xprt->xp_socket = so;
	xprt->xp_p1 = NULL;
	xprt->xp_p2 = NULL;
	xprt->xp_ops = &svc_dg_ops;

	CURVNET_SET(so->so_vnet);
	error = so->so_proto->pr_usrreqs->pru_sockaddr(so, &sa);
	CURVNET_RESTORE();
	if (error)
		goto freedata;

	memcpy(&xprt->xp_ltaddr, sa, sa->sa_len);
	free(sa, M_SONAME);

	xprt_register(xprt);

	SOCKBUF_LOCK(&so->so_rcv);
	soupcall_set(so, SO_RCV, svc_dg_soupcall, xprt);
	SOCKBUF_UNLOCK(&so->so_rcv);

	return (xprt);
freedata:
	(void) printf(svc_dg_str, __no_mem_str);
	svc_xprt_free(xprt);

	return (NULL);
}