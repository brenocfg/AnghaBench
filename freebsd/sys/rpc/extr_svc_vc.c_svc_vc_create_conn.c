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
struct sockopt {int* sopt_val; int sopt_valsize; int /*<<< orphan*/  sopt_name; scalar_t__ sopt_level; void* sopt_dir; } ;
struct socket {int /*<<< orphan*/  so_rcv; TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct cf_conn {int /*<<< orphan*/  strm_stat; } ;
typedef  int /*<<< orphan*/  one ;
struct TYPE_12__ {int xp_idletimeout; int xp_upcallset; int /*<<< orphan*/  xp_lock; int /*<<< orphan*/  xp_ltaddr; int /*<<< orphan*/  xp_rtaddr; int /*<<< orphan*/ * xp_ops; int /*<<< orphan*/ * xp_p2; struct cf_conn* xp_p1; struct socket* xp_socket; int /*<<< orphan*/ * xp_pool; } ;
struct TYPE_11__ {scalar_t__ pr_protocol; TYPE_1__* pr_usrreqs; } ;
struct TYPE_10__ {int (* pru_sockaddr ) (struct socket*,struct sockaddr**) ;} ;
typedef  TYPE_3__ SVCXPRT ;
typedef  int /*<<< orphan*/  SVCPOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ SOL_SOCKET ; 
 void* SOPT_SET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  XPRT_IDLE ; 
 int /*<<< orphan*/  bzero (struct sockopt*,int) ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 struct cf_conn* mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (struct cf_conn*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int sosetopt (struct socket*,struct sockopt*) ; 
 int /*<<< orphan*/  soupcall_set (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub1 (struct socket*,struct sockaddr**) ; 
 int /*<<< orphan*/  svc_vc_ops ; 
 int /*<<< orphan*/  svc_vc_soupcall ; 
 TYPE_3__* svc_xprt_alloc () ; 
 int /*<<< orphan*/  svc_xprt_free (TYPE_3__*) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_active (TYPE_3__*) ; 
 int /*<<< orphan*/  xprt_register (TYPE_3__*) ; 

SVCXPRT *
svc_vc_create_conn(SVCPOOL *pool, struct socket *so, struct sockaddr *raddr)
{
	SVCXPRT *xprt;
	struct cf_conn *cd;
	struct sockaddr* sa = NULL;
	struct sockopt opt;
	int one = 1;
	int error;

	bzero(&opt, sizeof(struct sockopt));
	opt.sopt_dir = SOPT_SET;
	opt.sopt_level = SOL_SOCKET;
	opt.sopt_name = SO_KEEPALIVE;
	opt.sopt_val = &one;
	opt.sopt_valsize = sizeof(one);
	error = sosetopt(so, &opt);
	if (error) {
		return (NULL);
	}

	if (so->so_proto->pr_protocol == IPPROTO_TCP) {
		bzero(&opt, sizeof(struct sockopt));
		opt.sopt_dir = SOPT_SET;
		opt.sopt_level = IPPROTO_TCP;
		opt.sopt_name = TCP_NODELAY;
		opt.sopt_val = &one;
		opt.sopt_valsize = sizeof(one);
		error = sosetopt(so, &opt);
		if (error) {
			return (NULL);
		}
	}

	cd = mem_alloc(sizeof(*cd));
	cd->strm_stat = XPRT_IDLE;

	xprt = svc_xprt_alloc();
	sx_init(&xprt->xp_lock, "xprt->xp_lock");
	xprt->xp_pool = pool;
	xprt->xp_socket = so;
	xprt->xp_p1 = cd;
	xprt->xp_p2 = NULL;
	xprt->xp_ops = &svc_vc_ops;

	/*
	 * See http://www.connectathon.org/talks96/nfstcp.pdf - client
	 * has a 5 minute timer, server has a 6 minute timer.
	 */
	xprt->xp_idletimeout = 6 * 60;

	memcpy(&xprt->xp_rtaddr, raddr, raddr->sa_len);

	CURVNET_SET(so->so_vnet);
	error = so->so_proto->pr_usrreqs->pru_sockaddr(so, &sa);
	CURVNET_RESTORE();
	if (error)
		goto cleanup_svc_vc_create;

	memcpy(&xprt->xp_ltaddr, sa, sa->sa_len);
	free(sa, M_SONAME);

	xprt_register(xprt);

	SOCKBUF_LOCK(&so->so_rcv);
	xprt->xp_upcallset = 1;
	soupcall_set(so, SO_RCV, svc_vc_soupcall, xprt);
	SOCKBUF_UNLOCK(&so->so_rcv);

	/*
	 * Throw the transport into the active list in case it already
	 * has some data buffered.
	 */
	sx_xlock(&xprt->xp_lock);
	xprt_active(xprt);
	sx_xunlock(&xprt->xp_lock);

	return (xprt);
cleanup_svc_vc_create:
	sx_destroy(&xprt->xp_lock);
	svc_xprt_free(xprt);
	mem_free(cd, sizeof(*cd));

	return (NULL);
}