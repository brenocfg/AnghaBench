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
typedef  int /*<<< orphan*/  enum_t ;
typedef  enum sizecheck { ____Placeholder_sizecheck } sizecheck ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xdr_long (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  xdr_short (int /*<<< orphan*/ *,short*) ; 

bool_t
xdr_enum(XDR *xdrs, enum_t *ep)
{
	enum sizecheck { SIZEVAL };	/* used to find the size of an enum */

	/*
	 * enums are treated as ints
	 */
	/* LINTED */ if (sizeof (enum sizecheck) == sizeof (long)) {
		return (xdr_long(xdrs, (long *)(void *)ep));
	} else /* LINTED */ if (sizeof (enum sizecheck) == sizeof (int)) {
		return (xdr_int(xdrs, (int *)(void *)ep));
	} else /* LINTED */ if (sizeof (enum sizecheck) == sizeof (short)) {
		return (xdr_short(xdrs, (short *)(void *)ep));
	} else {
		return (FALSE);
	}
}