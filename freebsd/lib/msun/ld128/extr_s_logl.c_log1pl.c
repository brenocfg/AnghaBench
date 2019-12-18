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
typedef  long long uint64_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOPRINT_START (long double*) ; 
 long double E (int) ; 
 int /*<<< orphan*/  ENTERI () ; 
 int /*<<< orphan*/  EXTRACT_LDBL128_WORDS (int,long long,long long,long double) ; 
 int /*<<< orphan*/  FE_UNDERFLOW ; 
 scalar_t__ F_hi (int) ; 
 double F_lo (int) ; 
 long double G (int) ; 
 long double H (int) ; 
 int /*<<< orphan*/  INSERT_LDBL128_WORDS (long double,int,long long,long long) ; 
 int L2I ; 
 double P10 ; 
 double P11 ; 
 double P12 ; 
 double P13 ; 
 double P14 ; 
 long double P2 ; 
 long double P3 ; 
 long double P4 ; 
 long double P5 ; 
 long double P6 ; 
 long double P7 ; 
 double P8 ; 
 double P9 ; 
 int /*<<< orphan*/  RETURN2PI (long double,long double) ; 
 int /*<<< orphan*/  RETURNP (long double) ; 
 int /*<<< orphan*/  SET_LDBL_EXPSIGN (long double,int) ; 
 int /*<<< orphan*/  _3sumF (long double,long double,scalar_t__) ; 
 int /*<<< orphan*/  breakpoint () ; 
 scalar_t__ fetestexcept (int /*<<< orphan*/ ) ; 
 double ln2_hi ; 
 double ln2_lo ; 
 int zero ; 

long double
log1pl(long double x)
{
	long double d, d_hi, f_lo, val_hi, val_lo;
	long double f_hi, twopminusk;
	double d_lo, dd, dk;
	uint64_t lx, llx;
	int i, k;
	int16_t ax, hx;

	DOPRINT_START(&x);
	EXTRACT_LDBL128_WORDS(hx, lx, llx, x);
	if (hx < 0x3fff) {		/* x < 1, or x neg NaN */
		ax = hx & 0x7fff;
		if (ax >= 0x3fff) {	/* x <= -1, or x neg NaN */
			if (ax == 0x3fff && (lx | llx) == 0)
				RETURNP(-1 / zero);	/* log1p(-1) = -Inf */
			/* log1p(x < 1, or x NaN) = qNaN: */
			RETURNP((x - x) / (x - x));
		}
		if (ax <= 0x3f8d) {	/* |x| < 2**-113 */
			if ((int)x == 0)
				RETURNP(x);	/* x with inexact if x != 0 */
		}
		f_hi = 1;
		f_lo = x;
	} else if (hx >= 0x7fff) {	/* x +Inf or non-neg NaN */
		RETURNP(x + x);		/* log1p(Inf or NaN) = Inf or qNaN */
	} else if (hx < 0x40e1) {	/* 1 <= x < 2**226 */
		f_hi = x;
		f_lo = 1;
	} else {			/* 2**226 <= x < +Inf */
		f_hi = x;
		f_lo = 0;		/* avoid underflow of the P3 term */
	}
	ENTERI();
	x = f_hi + f_lo;
	f_lo = (f_hi - x) + f_lo;

	EXTRACT_LDBL128_WORDS(hx, lx, llx, x);
	k = -16383;

	k += hx;
	dk = k;

	SET_LDBL_EXPSIGN(x, 0x3fff);
	twopminusk = 1;
	SET_LDBL_EXPSIGN(twopminusk, 0x7ffe - (hx & 0x7fff));
	f_lo *= twopminusk;

	i = (lx + (1LL << (L2I - 2))) >> (L2I - 1);

	/*
	 * x*G(i)-1 (with a reduced x) can be represented exactly, as
	 * above, but now we need to evaluate the polynomial on d =
	 * (x+f_lo)*G(i)-1 and extra precision is needed for that.
	 * Since x+x_lo is a hi+lo decomposition and subtracting 1
	 * doesn't lose too many bits, an inexact calculation for
	 * f_lo*G(i) is good enough.
	 */
	if (0)
		d_hi = x * G(i) - 1;
	else {
#ifdef USE_UTAB
		d_hi = (x - H(i)) * G(i) + E(i);
#else
		long double x_hi;
		double x_lo;

		INSERT_LDBL128_WORDS(x_hi, 0x3fff, lx,
		    llx & 0xffffffffff000000ULL);
		x_lo = x - x_hi;
		d_hi = x_hi * G(i) - 1 + x_lo * G(i);
#endif
	}
	d_lo = f_lo * G(i);

	/*
	 * This is _2sumF(d_hi, d_lo) inlined.  The condition
	 * (d_hi == 0 || |d_hi| >= |d_lo|) for using _2sumF() is not
	 * always satisifed, so it is not clear that this works, but
	 * it works in practice.  It works even if it gives a wrong
	 * normalized d_lo, since |d_lo| > |d_hi| implies that i is
	 * nonzero and d is tiny, so the F(i) term dominates d_lo.
	 * In float precision:
	 * (By exhaustive testing, the worst case is d_hi = 0x1.bp-25.
	 * And if d is only a little tinier than that, we would have
	 * another underflow problem for the P3 term; this is also ruled
	 * out by exhaustive testing.)
	 */
	d = d_hi + d_lo;
	d_lo = d_hi - d + d_lo;
	d_hi = d;

	dd = (double)d;
	val_lo = d * d * d * (P3 +
	    d * (P4 + d * (P5 + d * (P6 + d * (P7 + d * (P8 +
	    dd * (P9 + dd * (P10 + dd * (P11 + dd * (P12 + dd * (P13 +
	    dd * P14))))))))))) + (F_lo(i) + dk * ln2_lo + d_lo) + d * d * P2;
	val_hi = d_hi;
#ifdef DEBUG
	if (fetestexcept(FE_UNDERFLOW))
		breakpoint();
#endif

	_3sumF(val_hi, val_lo, F_hi(i) + dk * ln2_hi);
	RETURN2PI(val_hi, val_lo);
}