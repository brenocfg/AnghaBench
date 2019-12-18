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
typedef  int /*<<< orphan*/  (* xdrproc_t ) (int /*<<< orphan*/ *,char*) ;
struct xdr_discrim {scalar_t__ value; int /*<<< orphan*/  (* proc ) (int /*<<< orphan*/ *,char*) ;} ;
typedef  scalar_t__ enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NULL_xdrproc_t (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,scalar_t__*) ; 

bool_t
xdr_union(XDR *xdrs,
    enum_t *dscmp,		/* enum to decide which arm to work on */
    char *unp,				/* the union itself */
    const struct xdr_discrim *choices,	/* [value, xdr proc] for each arm */
    xdrproc_t dfault)			/* default xdr routine */
{
	enum_t dscm;

	/*
	 * we deal with the discriminator;  it's an enum
	 */
	if (! xdr_enum(xdrs, dscmp)) {
		return (FALSE);
	}
	dscm = *dscmp;

	/*
	 * search choices for a value that matches the discriminator.
	 * if we find one, execute the xdr routine for that value.
	 */
	for (; choices->proc != NULL_xdrproc_t; choices++) {
		if (choices->value == dscm)
			return ((*(choices->proc))(xdrs, unp));
	}

	/*
	 * no match - execute the default xdr routine if there is one
	 */
	return ((dfault == NULL_xdrproc_t) ? FALSE :
	    (*dfault)(xdrs, unp));
}