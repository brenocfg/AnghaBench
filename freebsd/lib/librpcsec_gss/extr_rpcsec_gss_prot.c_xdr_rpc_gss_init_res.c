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
struct rpc_gss_init_res {int /*<<< orphan*/  gr_token; int /*<<< orphan*/  gr_win; int /*<<< orphan*/  gr_minor; int /*<<< orphan*/  gr_major; int /*<<< orphan*/  gr_handle; } ;
typedef  int bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 scalar_t__ xdr_gss_buffer_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_rpc_gss_init_res(XDR *xdrs, struct rpc_gss_init_res *p)
{

	return (xdr_gss_buffer_desc(xdrs, &p->gr_handle) &&
	    xdr_u_int(xdrs, &p->gr_major) &&
	    xdr_u_int(xdrs, &p->gr_minor) &&
	    xdr_u_int(xdrs, &p->gr_win) &&
	    xdr_gss_buffer_desc(xdrs, &p->gr_token));
}