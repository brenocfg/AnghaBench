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
typedef  int /*<<< orphan*/  u_int ;
struct vax_double {int mantissa4; int mantissa3; int mantissa2; int mantissa1; void* exp; int /*<<< orphan*/  sign; } ;
struct ieee_double {void* exp; int mantissa1; int mantissa2; int /*<<< orphan*/  sign; } ;
struct dbl_limits {struct vax_double d; struct ieee_double ieee; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int bool_t ;
struct TYPE_5__ {int x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int FALSE ; 
 void* IEEE_DBL_BIAS ; 
 int MASK (int) ; 
 int TRUE ; 
 void* VAX_DBL_BIAS ; 
#define  XDR_DECODE 130 
#define  XDR_ENCODE 129 
#define  XDR_FREE 128 
 int XDR_GETINT32 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int XDR_PUTINT32 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct dbl_limits* dbl_limits ; 
 int /*<<< orphan*/  nitems (struct dbl_limits*) ; 

bool_t
xdr_double(XDR *xdrs, double *dp)
{
#ifdef IEEEFP
	int32_t *i32p;
	bool_t rv;
#else
	int32_t *lp;
	struct	ieee_double id;
	struct	vax_double vd;
	struct dbl_limits *lim;
	u_int i;
#endif

	switch (xdrs->x_op) {

	case XDR_ENCODE:
#ifdef IEEEFP
		i32p = (int32_t *)(void *)dp;
#if BYTE_ORDER == BIG_ENDIAN
		rv = XDR_PUTINT32(xdrs, i32p);
		if (!rv)
			return (rv);
		rv = XDR_PUTINT32(xdrs, i32p+1);
#else
		rv = XDR_PUTINT32(xdrs, i32p+1);
		if (!rv)
			return (rv);
		rv = XDR_PUTINT32(xdrs, i32p);
#endif
		return (rv);
#else
		vd = *((struct vax_double *)dp);
		for (i = 0, lim = dbl_limits; i < nitems(dbl_limits);
		    i++, lim++) {
			if ((vd.mantissa4 == lim->d.mantissa4) &&
				(vd.mantissa3 == lim->d.mantissa3) &&
				(vd.mantissa2 == lim->d.mantissa2) &&
				(vd.mantissa1 == lim->d.mantissa1) &&
				(vd.exp == lim->d.exp)) {
				id = lim->ieee;
				goto shipit;
			}
		}
		id.exp = vd.exp - VAX_DBL_BIAS + IEEE_DBL_BIAS;
		id.mantissa1 = (vd.mantissa1 << 13) | (vd.mantissa2 >> 3);
		id.mantissa2 = ((vd.mantissa2 & MASK(3)) << 29) |
				(vd.mantissa3 << 13) |
				((vd.mantissa4 >> 3) & MASK(13));
	shipit:
		id.sign = vd.sign;
		lp = (int32_t *)&id;
		return (XDR_PUTINT32(xdrs, lp++) && XDR_PUTINT32(xdrs, lp));
#endif

	case XDR_DECODE:
#ifdef IEEEFP
		i32p = (int32_t *)(void *)dp;
#if BYTE_ORDER == BIG_ENDIAN
		rv = XDR_GETINT32(xdrs, i32p);
		if (!rv)
			return (rv);
		rv = XDR_GETINT32(xdrs, i32p+1);
#else
		rv = XDR_GETINT32(xdrs, i32p+1);
		if (!rv)
			return (rv);
		rv = XDR_GETINT32(xdrs, i32p);
#endif
		return (rv);
#else
		lp = (int32_t *)&id;
		if (!XDR_GETINT32(xdrs, lp++) || !XDR_GETINT32(xdrs, lp))
			return (FALSE);
		for (i = 0, lim = dbl_limits; i < nitems(dbl_limits);
		    i++, lim++) {
			if ((id.mantissa2 == lim->ieee.mantissa2) &&
				(id.mantissa1 == lim->ieee.mantissa1) &&
				(id.exp == lim->ieee.exp)) {
				vd = lim->d;
				goto doneit;
			}
		}
		vd.exp = id.exp - IEEE_DBL_BIAS + VAX_DBL_BIAS;
		vd.mantissa1 = (id.mantissa1 >> 13);
		vd.mantissa2 = ((id.mantissa1 & MASK(13)) << 3) |
				(id.mantissa2 >> 29);
		vd.mantissa3 = (id.mantissa2 >> 13);
		vd.mantissa4 = (id.mantissa2 << 3);
	doneit:
		vd.sign = id.sign;
		*dp = *((double *)&vd);
		return (TRUE);
#endif

	case XDR_FREE:
		return (TRUE);
	}
	/* NOTREACHED */
	return (FALSE);
}