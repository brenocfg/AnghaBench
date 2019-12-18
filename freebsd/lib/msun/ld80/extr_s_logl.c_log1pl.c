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
typedef  int uint64_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOPRINT_START (long double*) ; 
 long double E (int) ; 
 int /*<<< orphan*/  ENTERI () ; 
 int /*<<< orphan*/  EXTRACT_LDBL80_WORDS (int,int,long double) ; 
 int /*<<< orphan*/  FE_UNDERFLOW ; 
 scalar_t__ F_hi (int) ; 
 long double F_lo (int) ; 
 long double G (int) ; 
 long double H (int) ; 
 int L2I ; 
 long double P2 ; 
 long double P3 ; 
 long double P4 ; 
 long double P5 ; 
 long double P6 ; 
 long double P7 ; 
 long double P8 ; 
 int /*<<< orphan*/  RETURN2PI (long double,long double) ; 
 int /*<<< orphan*/  RETURNP (long double) ; 
 int /*<<< orphan*/  SET_FLOAT_WORD (float,int) ; 
 int /*<<< orphan*/  SET_LDBL_EXPSIGN (long double,int) ; 
 int /*<<< orphan*/  _3sumF (long double,long double,scalar_t__) ; 
 int /*<<< orphan*/  breakpoint () ; 
 scalar_t__ fetestexcept (int /*<<< orphan*/ ) ; 
 long double ln2_hi ; 
 long double ln2_lo ; 
 int zero ; 

long double
log1pl(long double x)
{
	long double d, d_hi, d_lo, dk, f_lo, val_hi, val_lo, z;
	long double f_hi, twopminusk;
	uint64_t ix, lx;
	int i, k;
	int16_t ax, hx;

	DOPRINT_START(&x);
	EXTRACT_LDBL80_WORDS(hx, lx, x);
	if (hx < 0x3fff) {		/* x < 1, or x neg NaN */
		ax = hx & 0x7fff;
		if (ax >= 0x3fff) {	/* x <= -1, or x neg NaN */
			if (ax == 0x3fff && lx == 0x8000000000000000ULL)
				RETURNP(-1 / zero);	/* log1p(-1) = -Inf */
			/* log1p(x < 1, or x [pseudo-]NaN) = qNaN: */
			RETURNP((x - x) / (x - x));
		}
		if (ax <= 0x3fbe) {	/* |x| < 2**-64 */
			if ((int)x == 0)
				RETURNP(x);	/* x with inexact if x != 0 */
		}
		f_hi = 1;
		f_lo = x;
	} else if (hx >= 0x7fff) {	/* x +Inf or non-neg NaN */
		RETURNP(x + x);		/* log1p(Inf or NaN) = Inf or qNaN */
					/* log1p(pseudo-Inf) = qNaN */
					/* log1p(pseudo-NaN) = qNaN */
					/* log1p(unnormal) = qNaN */
	} else if (hx < 0x407f) {	/* 1 <= x < 2**128 */
		f_hi = x;
		f_lo = 1;
	} else {			/* 2**128 <= x < +Inf */
		f_hi = x;
		f_lo = 0;		/* avoid underflow of the P5 term */
	}
	ENTERI();
	x = f_hi + f_lo;
	f_lo = (f_hi - x) + f_lo;

	EXTRACT_LDBL80_WORDS(hx, lx, x);
	k = -16383;

	k += hx;
	ix = lx & 0x7fffffffffffffffULL;
	dk = k;

	SET_LDBL_EXPSIGN(x, 0x3fff);
	twopminusk = 1;
	SET_LDBL_EXPSIGN(twopminusk, 0x7ffe - (hx & 0x7fff));
	f_lo *= twopminusk;

	i = (ix + (1LL << (L2I - 2))) >> (L2I - 1);

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
		long double x_hi, x_lo;
		float fx_hi;

		SET_FLOAT_WORD(fx_hi, (lx >> 40) | 0x3f800000);
		x_hi = fx_hi;
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

	z = d * d;
	val_lo = z * d * z * (z * (d * P8 + P7) + (d * P6 + P5)) +
	    (F_lo(i) + dk * ln2_lo + d_lo + z * d * (d * P4 + P3)) + z * P2;
	val_hi = d_hi;
#ifdef DEBUG
	if (fetestexcept(FE_UNDERFLOW))
		breakpoint();
#endif

	_3sumF(val_hi, val_lo, F_hi(i) + dk * ln2_hi);
	RETURN2PI(val_hi, val_lo);
}