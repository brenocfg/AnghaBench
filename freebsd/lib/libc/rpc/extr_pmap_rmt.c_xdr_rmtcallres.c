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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_long ;
struct rmtcallres {int /*<<< orphan*/  results_ptr; int /*<<< orphan*/  (* xdr_results ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * port_ptr; int /*<<< orphan*/  resultslen; } ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_reference (int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_long (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_rmtcallres(XDR *xdrs, struct rmtcallres *crp)
{
	caddr_t port_ptr;

	assert(xdrs != NULL);
	assert(crp != NULL);

	port_ptr = (caddr_t)(void *)crp->port_ptr;
	if (xdr_reference(xdrs, &port_ptr, sizeof (u_long),
	    (xdrproc_t)xdr_u_long) && xdr_u_long(xdrs, &crp->resultslen)) {
		crp->port_ptr = (u_long *)(void *)port_ptr;
		return ((*(crp->xdr_results))(xdrs, crp->results_ptr));
	}
	return (FALSE);
}