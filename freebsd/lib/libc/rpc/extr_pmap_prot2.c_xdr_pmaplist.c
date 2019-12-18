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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_int ;
struct pmaplist {struct pmaplist* pml_next; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  scalar_t__ bool_t ;
struct TYPE_5__ {scalar_t__ x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ XDR_FREE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_bool (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ xdr_pmap ; 
 int /*<<< orphan*/  xdr_reference (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool_t
xdr_pmaplist(XDR *xdrs, struct pmaplist **rp)
{
	/*
	 * more_elements is pre-computed in case the direction is
	 * XDR_ENCODE or XDR_FREE.  more_elements is overwritten by
	 * xdr_bool when the direction is XDR_DECODE.
	 */
	bool_t more_elements;
	int freeing;
	struct pmaplist **next	= NULL; /* pacify gcc */

	assert(xdrs != NULL);
	assert(rp != NULL);

	freeing = (xdrs->x_op == XDR_FREE);

	for (;;) {
		more_elements = (bool_t)(*rp != NULL);
		if (! xdr_bool(xdrs, &more_elements))
			return (FALSE);
		if (! more_elements)
			return (TRUE);  /* we are done */
		/*
		 * the unfortunate side effect of non-recursion is that in
		 * the case of freeing we must remember the next object
		 * before we free the current object ...
		 */
		if (freeing)
			next = &((*rp)->pml_next); 
		if (! xdr_reference(xdrs, (caddr_t *)rp,
		    (u_int)sizeof(struct pmaplist), (xdrproc_t)xdr_pmap))
			return (FALSE);
		rp = (freeing) ? next : &((*rp)->pml_next);
	}
}