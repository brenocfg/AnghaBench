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
typedef  int /*<<< orphan*/  uint16_t ;
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
xdr_uint16_t(XDR *xdrs, uint16_t *uint16_p)
{
	u_long l;

	switch (xdrs->x_op) {

	case XDR_ENCODE:
		l = (u_long) *uint16_p;
		return (XDR_PUTLONG(xdrs, (long *)&l));

	case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, (long *)&l)) {
			return (FALSE);
		}
		*uint16_p = (uint16_t) l;
		return (TRUE);

	case XDR_FREE:
		return (TRUE);
	}
	/* NOTREACHED */
	return (FALSE);
}