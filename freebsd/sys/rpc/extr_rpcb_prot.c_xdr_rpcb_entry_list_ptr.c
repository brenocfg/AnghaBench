#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  TYPE_1__* rpcb_entry_list_ptr ;
typedef  int /*<<< orphan*/  rpcb_entry_list ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  scalar_t__ bool_t ;
struct TYPE_8__ {scalar_t__ x_op; } ;
typedef  TYPE_2__ XDR ;
struct TYPE_7__ {struct TYPE_7__* rpcb_entry_next; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ XDR_FREE ; 
 int /*<<< orphan*/  xdr_bool (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  xdr_reference (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_rpcb_entry ; 

bool_t
xdr_rpcb_entry_list_ptr(XDR *xdrs, rpcb_entry_list_ptr *rp)
{
	/*
	 * more_elements is pre-computed in case the direction is
	 * XDR_ENCODE or XDR_FREE.  more_elements is overwritten by
	 * xdr_bool when the direction is XDR_DECODE.
	 */
	bool_t more_elements;
	int freeing = (xdrs->x_op == XDR_FREE);
	rpcb_entry_list_ptr next;
	rpcb_entry_list_ptr next_copy;

	next = NULL;
	for (;;) {
		more_elements = (bool_t)(*rp != NULL);
		if (! xdr_bool(xdrs, &more_elements)) {
			return (FALSE);
		}
		if (! more_elements) {
			return (TRUE);  /* we are done */
		}
		/*
		 * the unfortunate side effect of non-recursion is that in
		 * the case of freeing we must remember the next object
		 * before we free the current object ...
		 */
		if (freeing)
			next = (*rp)->rpcb_entry_next;
		if (! xdr_reference(xdrs, (caddr_t *)rp,
		    (u_int)sizeof (rpcb_entry_list),
				    (xdrproc_t)xdr_rpcb_entry)) {
			return (FALSE);
		}
		if (freeing && *rp) {
			next_copy = next;
			rp = &next_copy;
			/*
			 * Note that in the subsequent iteration, next_copy
			 * gets nulled out by the xdr_reference
			 * but next itself survives.
			 */
		} else if (*rp) {
			rp = &((*rp)->rpcb_entry_next);
		}
	}
	/*NOTREACHED*/
}