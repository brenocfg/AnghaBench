#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (TYPE_1__*,void*) ;
struct TYPE_7__ {int /*<<< orphan*/  x_op; } ;
struct cf_conn {TYPE_1__ xdrs; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  TYPE_1__ XDR ;
struct TYPE_8__ {scalar_t__ xp_p1; } ;
typedef  TYPE_3__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_FREE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 

__attribute__((used)) static bool_t
svc_vc_freeargs(SVCXPRT *xprt, xdrproc_t xdr_args, void *args_ptr)
{
	XDR *xdrs;

	assert(xprt != NULL);
	/* args_ptr may be NULL */

	xdrs = &(((struct cf_conn *)(xprt->xp_p1))->xdrs);

	xdrs->x_op = XDR_FREE;
	return ((*xdr_args)(xdrs, args_ptr));
}