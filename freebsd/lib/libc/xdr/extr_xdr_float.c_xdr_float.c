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
struct vax_single {int mantissa2; void* exp; int mantissa1; int /*<<< orphan*/  sign; } ;
struct ieee_single {void* exp; int mantissa; int /*<<< orphan*/  sign; } ;
struct sgl_limits {struct vax_single s; struct ieee_single ieee; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {int x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* IEEE_SNG_BIAS ; 
 int /*<<< orphan*/  TRUE ; 
 void* VAX_SNG_BIAS ; 
#define  XDR_DECODE 130 
#define  XDR_ENCODE 129 
#define  XDR_FREE 128 
 int /*<<< orphan*/  XDR_GETINT32 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_PUTINT32 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nitems (struct sgl_limits*) ; 
 struct sgl_limits* sgl_limits ; 

bool_t
xdr_float(XDR *xdrs, float *fp)
{
#ifndef IEEEFP
	struct ieee_single is;
	struct vax_single vs, *vsp;
	struct sgl_limits *lim;
	u_int i;
#endif
	switch (xdrs->x_op) {

	case XDR_ENCODE:
#ifdef IEEEFP
		return (XDR_PUTINT32(xdrs, (int32_t *)fp));
#else
		vs = *((struct vax_single *)fp);
		for (i = 0, lim = sgl_limits; i < nitems(sgl_limits);
		    i++, lim++) {
			if ((vs.mantissa2 == lim->s.mantissa2) &&
				(vs.exp == lim->s.exp) &&
				(vs.mantissa1 == lim->s.mantissa1)) {
				is = lim->ieee;
				goto shipit;
			}
		}
		is.exp = vs.exp - VAX_SNG_BIAS + IEEE_SNG_BIAS;
		is.mantissa = (vs.mantissa1 << 16) | vs.mantissa2;
	shipit:
		is.sign = vs.sign;
		return (XDR_PUTINT32(xdrs, (int32_t *)&is));
#endif

	case XDR_DECODE:
#ifdef IEEEFP
		return (XDR_GETINT32(xdrs, (int32_t *)fp));
#else
		vsp = (struct vax_single *)fp;
		if (!XDR_GETINT32(xdrs, (int32_t *)&is))
			return (FALSE);
		for (i = 0, lim = sgl_limits; i < nitems(sgl_limits);
		    i++, lim++) {
			if ((is.exp == lim->ieee.exp) &&
				(is.mantissa == lim->ieee.mantissa)) {
				*vsp = lim->s;
				goto doneit;
			}
		}
		vsp->exp = is.exp - IEEE_SNG_BIAS + VAX_SNG_BIAS;
		vsp->mantissa2 = is.mantissa;
		vsp->mantissa1 = (is.mantissa >> 16);
	doneit:
		vsp->sign = is.sign;
		return (TRUE);
#endif

	case XDR_FREE:
		return (TRUE);
	}
	/* NOTREACHED */
	return (FALSE);
}