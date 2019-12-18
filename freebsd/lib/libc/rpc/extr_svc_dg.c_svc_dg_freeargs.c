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
typedef  int /*<<< orphan*/  (* xdrproc_t ) (TYPE_1__*,void*) ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_6__ {int /*<<< orphan*/  x_op; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_7__ {TYPE_1__ su_xdrs; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_FREE ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 
 TYPE_4__* su_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t
svc_dg_freeargs(SVCXPRT *xprt, xdrproc_t xdr_args, void *args_ptr)
{
	XDR *xdrs = &(su_data(xprt)->su_xdrs);

	xdrs->x_op = XDR_FREE;
	return (*xdr_args)(xdrs, args_ptr);
}