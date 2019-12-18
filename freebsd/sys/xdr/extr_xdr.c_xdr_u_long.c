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
typedef  int /*<<< orphan*/  u_long ;
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
xdr_u_long(XDR *xdrs, u_long *ulp)
{
	switch (xdrs->x_op) {
	case XDR_ENCODE:
		return (XDR_PUTLONG(xdrs, (long *)ulp));
	case XDR_DECODE:
		return (XDR_GETLONG(xdrs, (long *)ulp));
	case XDR_FREE:
		return (TRUE);
	}
	/* NOTREACHED */
	return (FALSE);
}