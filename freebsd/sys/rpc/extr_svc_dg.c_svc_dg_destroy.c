#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  so_rcv; } ;
struct TYPE_6__ {scalar_t__ xp_netid; TYPE_4__* xp_socket; int /*<<< orphan*/  xp_lock; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  mem_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  soclose (TYPE_4__*) ; 
 int /*<<< orphan*/  soupcall_clear (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  svc_xprt_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
svc_dg_destroy(SVCXPRT *xprt)
{

	SOCKBUF_LOCK(&xprt->xp_socket->so_rcv);
	soupcall_clear(xprt->xp_socket, SO_RCV);
	SOCKBUF_UNLOCK(&xprt->xp_socket->so_rcv);

	sx_destroy(&xprt->xp_lock);
	if (xprt->xp_socket)
		(void)soclose(xprt->xp_socket);

	if (xprt->xp_netid)
		(void) mem_free(xprt->xp_netid, strlen(xprt->xp_netid) + 1);
	svc_xprt_free(xprt);
}