#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cf_conn {int /*<<< orphan*/  strm_stat; } ;
struct TYPE_4__ {int /*<<< orphan*/ * xp_ops; int /*<<< orphan*/ * xp_p2; struct cf_conn* xp_p1; int /*<<< orphan*/ * xp_socket; int /*<<< orphan*/ * xp_pool; int /*<<< orphan*/  xp_lock; } ;
typedef  TYPE_1__ SVCXPRT ;
typedef  int /*<<< orphan*/  SVCPOOL ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_IDLE ; 
 struct cf_conn* mem_alloc (int) ; 
 int /*<<< orphan*/  svc_vc_backchannel_ops ; 
 TYPE_1__* svc_xprt_alloc () ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

SVCXPRT *
svc_vc_create_backchannel(SVCPOOL *pool)
{
	SVCXPRT *xprt = NULL;
	struct cf_conn *cd = NULL;

	cd = mem_alloc(sizeof(*cd));
	cd->strm_stat = XPRT_IDLE;

	xprt = svc_xprt_alloc();
	sx_init(&xprt->xp_lock, "xprt->xp_lock");
	xprt->xp_pool = pool;
	xprt->xp_socket = NULL;
	xprt->xp_p1 = cd;
	xprt->xp_p2 = NULL;
	xprt->xp_ops = &svc_vc_backchannel_ops;
	return (xprt);
}