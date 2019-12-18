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
typedef  int u_int32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_WORDS (int,int,double) ; 
 int /*<<< orphan*/  GET_HIGH_WORD (int,double) ; 
 int /*<<< orphan*/  SET_HIGH_WORD (double,int) ; 
 int /*<<< orphan*/  SET_LOW_WORD (double,int /*<<< orphan*/ ) ; 
 double ivln2hi ; 
 double ivln2lo ; 
 double k_log1p (double) ; 
 double two54 ; 
 double vzero ; 
 double zero ; 

double
__ieee754_log2(double x)
{
	double f,hfsq,hi,lo,r,val_hi,val_lo,w,y;
	int32_t i,k,hx;
	u_int32_t lx;

	EXTRACT_WORDS(hx,lx,x);

	k=0;
	if (hx < 0x00100000) {			/* x < 2**-1022  */
	    if (((hx&0x7fffffff)|lx)==0)
		return -two54/vzero;		/* log(+-0)=-inf */
	    if (hx<0) return (x-x)/zero;	/* log(-#) = NaN */
	    k -= 54; x *= two54; /* subnormal number, scale up x */
	    GET_HIGH_WORD(hx,x);
	}
	if (hx >= 0x7ff00000) return x+x;
	if (hx == 0x3ff00000 && lx == 0)
	    return zero;			/* log(1) = +0 */
	k += (hx>>20)-1023;
	hx &= 0x000fffff;
	i = (hx+0x95f64)&0x100000;
	SET_HIGH_WORD(x,hx|(i^0x3ff00000));	/* normalize x or x/2 */
	k += (i>>20);
	y = (double)k;
	f = x - 1.0;
	hfsq = 0.5*f*f;
	r = k_log1p(f);

	/*
	 * f-hfsq must (for args near 1) be evaluated in extra precision
	 * to avoid a large cancellation when x is near sqrt(2) or 1/sqrt(2).
	 * This is fairly efficient since f-hfsq only depends on f, so can
	 * be evaluated in parallel with R.  Not combining hfsq with R also
	 * keeps R small (though not as small as a true `lo' term would be),
	 * so that extra precision is not needed for terms involving R.
	 *
	 * Compiler bugs involving extra precision used to break Dekker's
	 * theorem for spitting f-hfsq as hi+lo, unless double_t was used
	 * or the multi-precision calculations were avoided when double_t
	 * has extra precision.  These problems are now automatically
	 * avoided as a side effect of the optimization of combining the
	 * Dekker splitting step with the clear-low-bits step.
	 *
	 * y must (for args near sqrt(2) and 1/sqrt(2)) be added in extra
	 * precision to avoid a very large cancellation when x is very near
	 * these values.  Unlike the above cancellations, this problem is
	 * specific to base 2.  It is strange that adding +-1 is so much
	 * harder than adding +-ln2 or +-log10_2.
	 *
	 * This uses Dekker's theorem to normalize y+val_hi, so the
	 * compiler bugs are back in some configurations, sigh.  And I
	 * don't want to used double_t to avoid them, since that gives a
	 * pessimization and the support for avoiding the pessimization
	 * is not yet available.
	 *
	 * The multi-precision calculations for the multiplications are
	 * routine.
	 */
	hi = f - hfsq;
	SET_LOW_WORD(hi,0);
	lo = (f - hi) - hfsq + r;
	val_hi = hi*ivln2hi;
	val_lo = (lo+hi)*ivln2lo + lo*ivln2hi;

	/* spadd(val_hi, val_lo, y), except for not using double_t: */
	w = y + val_hi;
	val_lo += (y - w) + val_hi;
	val_hi = w;

	return val_lo + val_hi;
}