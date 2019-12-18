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
typedef  int uint64_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {int x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  XDR_DECODE 130 
#define  XDR_ENCODE 129 
#define  XDR_FREE 128 
 int /*<<< orphan*/  XDR_GETLONG (TYPE_1__*,long*) ; 
 int /*<<< orphan*/  XDR_PUTLONG (TYPE_1__*,long*) ; 

bool_t
xdr_int64_t(XDR *xdrs, int64_t *llp)
{
	u_long ul[2];

	switch (xdrs->x_op) {
	case XDR_ENCODE:
		ul[0] = (u_long)((uint64_t)*llp >> 32) & 0xffffffff;
		ul[1] = (u_long)((uint64_t)*llp) & 0xffffffff;
		if (XDR_PUTLONG(xdrs, (long *)&ul[0]) == FALSE)
			return (FALSE);
		return (XDR_PUTLONG(xdrs, (long *)&ul[1]));
	case XDR_DECODE:
		if (XDR_GETLONG(xdrs, (long *)&ul[0]) == FALSE)
			return (FALSE);
		if (XDR_GETLONG(xdrs, (long *)&ul[1]) == FALSE)
			return (FALSE);
		*llp = (int64_t)
		    (((uint64_t)ul[0] << 32) | ((uint64_t)ul[1]));
		return (TRUE);
	case XDR_FREE:
		return (TRUE);
	}
	/* NOTREACHED */
	return (FALSE);
}