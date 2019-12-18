#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (TYPE_1__*,void*) ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {int /*<<< orphan*/  x_op; } ;
typedef  TYPE_1__ XDR ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_FREE ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 

__attribute__((used)) static bool_t
clnt_bck_freeres(CLIENT *cl, xdrproc_t xdr_res, void *res_ptr)
{
	XDR xdrs;
	bool_t dummy;

	xdrs.x_op = XDR_FREE;
	dummy = (*xdr_res)(&xdrs, res_ptr);

	return (dummy);
}