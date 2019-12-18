#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (TYPE_1__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/ * caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_6__ {int x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  XDR_DECODE 130 
#define  XDR_ENCODE 129 
#define  XDR_FREE 128 
 int /*<<< orphan*/  mem_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*) ; 

bool_t
xdr_reference(XDR *xdrs, caddr_t *pp, u_int size, xdrproc_t proc)
/*
 *	XDR *xdrs;
 *	caddr_t *pp;		// the pointer to work on
 *	u_int size;		// size of the object pointed to
 *	xdrproc_t proc;		// xdr routine to handle the object
 */
{
	caddr_t loc = *pp;
	bool_t stat;

	if (loc == NULL)
		switch (xdrs->x_op) {
		case XDR_FREE:
			return (TRUE);

		case XDR_DECODE:
			*pp = loc = (caddr_t) mem_alloc(size);
			if (loc == NULL) {
				warnx("xdr_reference: out of memory");
				return (FALSE);
			}
			memset(loc, 0, size);
			break;

		case XDR_ENCODE:
			break;
		}

	stat = (*proc)(xdrs, loc);

	if (xdrs->x_op == XDR_FREE) {
		mem_free(loc, size);
		*pp = NULL;
	}
	return (stat);
}