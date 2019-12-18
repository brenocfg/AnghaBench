#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct finfo {int /*<<< orphan*/  caller_xid; int /*<<< orphan*/  caller_addr; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/ * __rpcb_get_dg_xidp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netbuf_copybuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_getrpccaller (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xprt_set_caller(SVCXPRT *xprt, struct finfo *fi)
{
	u_int32_t *xidp;

	netbuf_copybuf(svc_getrpccaller(xprt), fi->caller_addr);
	xidp = __rpcb_get_dg_xidp(xprt);
	*xidp = fi->caller_xid;
}