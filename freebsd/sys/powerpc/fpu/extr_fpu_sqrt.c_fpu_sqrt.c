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
typedef  int u_int ;
struct fpn {int* fp_mant; int fp_exp; int fp_sticky; scalar_t__ fp_sign; int /*<<< orphan*/  fp_class; } ;
struct fpemu {int /*<<< orphan*/  fe_cx; struct fpn fe_f1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOUBLE_X ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DUMPFPN (int /*<<< orphan*/ ,struct fpn*) ; 
 int /*<<< orphan*/  EVEN_DOUBLE ; 
 int /*<<< orphan*/  FPC_INF ; 
 int /*<<< orphan*/  FPE_REG ; 
 int /*<<< orphan*/  FPSCR_VXSNAN ; 
 int /*<<< orphan*/  FPSCR_VXSQRT ; 
 int /*<<< orphan*/  FPSCR_ZX ; 
 int /*<<< orphan*/  FPU_DECL_CARRY ; 
 int /*<<< orphan*/  FPU_SUBC (int,int,int) ; 
 int /*<<< orphan*/  FPU_SUBCS (int,int,int) ; 
 int /*<<< orphan*/  FPU_SUBS (int,int,int) ; 
 int FP_1 ; 
 scalar_t__ ISINF (struct fpn*) ; 
 scalar_t__ ISNAN (struct fpn*) ; 
 scalar_t__ ISZERO (struct fpn*) ; 
 int /*<<< orphan*/  ODD_DOUBLE ; 
 struct fpn* fpu_newnan (struct fpemu*) ; 
 int t0 ; 
 int t1 ; 
 int t2 ; 
 int t3 ; 

struct fpn *
fpu_sqrt(struct fpemu *fe)
{
	struct fpn *x = &fe->fe_f1;
	u_int bit, q, tt;
	u_int x0, x1, x2, x3;
	u_int y0, y1, y2, y3;
	u_int d0, d1, d2, d3;
	int e;
	FPU_DECL_CARRY;

	/*
	 * Take care of special cases first.  In order:
	 *
	 *	sqrt(NaN) = NaN
	 *	sqrt(+0) = +0
	 *	sqrt(-0) = -0
	 *	sqrt(x < 0) = NaN	(including sqrt(-Inf))
	 *	sqrt(+Inf) = +Inf
	 *
	 * Then all that remains are numbers with mantissas in [1..2).
	 */
	DPRINTF(FPE_REG, ("fpu_sqer:\n"));
	DUMPFPN(FPE_REG, x);
	DPRINTF(FPE_REG, ("=>\n"));
	if (ISNAN(x)) {
		fe->fe_cx |= FPSCR_VXSNAN;
		DUMPFPN(FPE_REG, x);
		return (x);
	}
	if (ISZERO(x)) {
		fe->fe_cx |= FPSCR_ZX;
		x->fp_class = FPC_INF;
		DUMPFPN(FPE_REG, x);
		return (x);
	}
	if (x->fp_sign) {
		fe->fe_cx |= FPSCR_VXSQRT;
		return (fpu_newnan(fe));
	}
	if (ISINF(x)) {
		DUMPFPN(FPE_REG, x);
		return (x);
	}

	/*
	 * Calculate result exponent.  As noted above, this may involve
	 * doubling the mantissa.  We will also need to double x each
	 * time around the loop, so we define a macro for this here, and
	 * we break out the multiword mantissa.
	 */
#ifdef FPU_SHL1_BY_ADD
#define	DOUBLE_X { \
	FPU_ADDS(x3, x3, x3); FPU_ADDCS(x2, x2, x2); \
	FPU_ADDCS(x1, x1, x1); FPU_ADDC(x0, x0, x0); \
}
#else
#define	DOUBLE_X { \
	x0 = (x0 << 1) | (x1 >> 31); x1 = (x1 << 1) | (x2 >> 31); \
	x2 = (x2 << 1) | (x3 >> 31); x3 <<= 1; \
}
#endif
#if (FP_NMANT & 1) != 0
# define ODD_DOUBLE	DOUBLE_X
# define EVEN_DOUBLE	/* nothing */
#else
# define ODD_DOUBLE	/* nothing */
# define EVEN_DOUBLE	DOUBLE_X
#endif
	x0 = x->fp_mant[0];
	x1 = x->fp_mant[1];
	x2 = x->fp_mant[2];
	x3 = x->fp_mant[3];
	e = x->fp_exp;
	if (e & 1)		/* exponent is odd; use sqrt(2mant) */
		DOUBLE_X;
	/* THE FOLLOWING ASSUMES THAT RIGHT SHIFT DOES SIGN EXTENSION */
	x->fp_exp = e >> 1;	/* calculates (e&1 ? (e-1)/2 : e/2 */

	/*
	 * Now calculate the mantissa root.  Since x is now in [1..4),
	 * we know that the first trip around the loop will definitely
	 * set the top bit in q, so we can do that manually and start
	 * the loop at the next bit down instead.  We must be sure to
	 * double x correctly while doing the `known q=1.0'.
	 *
	 * We do this one mantissa-word at a time, as noted above, to
	 * save work.  To avoid `(1U << 31) << 1', we also do the top bit
	 * outside of each per-word loop.
	 *
	 * The calculation `t = y + bit' breaks down into `t0 = y0, ...,
	 * t3 = y3, t? |= bit' for the appropriate word.  Since the bit
	 * is always a `new' one, this means that three of the `t?'s are
	 * just the corresponding `y?'; we use `#define's here for this.
	 * The variable `tt' holds the actual `t?' variable.
	 */

	/* calculate q0 */
#define	t0 tt
	bit = FP_1;
	EVEN_DOUBLE;
	/* if (x >= (t0 = y0 | bit)) { */	/* always true */
		q = bit;
		x0 -= bit;
		y0 = bit << 1;
	/* } */
	ODD_DOUBLE;
	while ((bit >>= 1) != 0) {	/* for remaining bits in q0 */
		EVEN_DOUBLE;
		t0 = y0 | bit;		/* t = y + bit */
		if (x0 >= t0) {		/* if x >= t then */
			x0 -= t0;	/*	x -= t */
			q |= bit;	/*	q += bit */
			y0 |= bit << 1;	/*	y += bit << 1 */
		}
		ODD_DOUBLE;
	}
	x->fp_mant[0] = q;
#undef t0

	/* calculate q1.  note (y0&1)==0. */
#define t0 y0
#define t1 tt
	q = 0;
	y1 = 0;
	bit = 1 << 31;
	EVEN_DOUBLE;
	t1 = bit;
	FPU_SUBS(d1, x1, t1);
	FPU_SUBC(d0, x0, t0);		/* d = x - t */
	if ((int)d0 >= 0) {		/* if d >= 0 (i.e., x >= t) then */
		x0 = d0, x1 = d1;	/*	x -= t */
		q = bit;		/*	q += bit */
		y0 |= 1;		/*	y += bit << 1 */
	}
	ODD_DOUBLE;
	while ((bit >>= 1) != 0) {	/* for remaining bits in q1 */
		EVEN_DOUBLE;		/* as before */
		t1 = y1 | bit;
		FPU_SUBS(d1, x1, t1);
		FPU_SUBC(d0, x0, t0);
		if ((int)d0 >= 0) {
			x0 = d0, x1 = d1;
			q |= bit;
			y1 |= bit << 1;
		}
		ODD_DOUBLE;
	}
	x->fp_mant[1] = q;
#undef t1

	/* calculate q2.  note (y1&1)==0; y0 (aka t0) is fixed. */
#define t1 y1
#define t2 tt
	q = 0;
	y2 = 0;
	bit = 1 << 31;
	EVEN_DOUBLE;
	t2 = bit;
	FPU_SUBS(d2, x2, t2);
	FPU_SUBCS(d1, x1, t1);
	FPU_SUBC(d0, x0, t0);
	if ((int)d0 >= 0) {
		x0 = d0, x1 = d1, x2 = d2;
		q = bit;
		y1 |= 1;		/* now t1, y1 are set in concrete */
	}
	ODD_DOUBLE;
	while ((bit >>= 1) != 0) {
		EVEN_DOUBLE;
		t2 = y2 | bit;
		FPU_SUBS(d2, x2, t2);
		FPU_SUBCS(d1, x1, t1);
		FPU_SUBC(d0, x0, t0);
		if ((int)d0 >= 0) {
			x0 = d0, x1 = d1, x2 = d2;
			q |= bit;
			y2 |= bit << 1;
		}
		ODD_DOUBLE;
	}
	x->fp_mant[2] = q;
#undef t2

	/* calculate q3.  y0, t0, y1, t1 all fixed; y2, t2, almost done. */
#define t2 y2
#define t3 tt
	q = 0;
	y3 = 0;
	bit = 1 << 31;
	EVEN_DOUBLE;
	t3 = bit;
	FPU_SUBS(d3, x3, t3);
	FPU_SUBCS(d2, x2, t2);
	FPU_SUBCS(d1, x1, t1);
	FPU_SUBC(d0, x0, t0);
	if ((int)d0 >= 0) {
		x0 = d0, x1 = d1, x2 = d2; x3 = d3;
		q = bit;
		y2 |= 1;
	}
	ODD_DOUBLE;
	while ((bit >>= 1) != 0) {
		EVEN_DOUBLE;
		t3 = y3 | bit;
		FPU_SUBS(d3, x3, t3);
		FPU_SUBCS(d2, x2, t2);
		FPU_SUBCS(d1, x1, t1);
		FPU_SUBC(d0, x0, t0);
		if ((int)d0 >= 0) {
			x0 = d0, x1 = d1, x2 = d2; x3 = d3;
			q |= bit;
			y3 |= bit << 1;
		}
		ODD_DOUBLE;
	}
	x->fp_mant[3] = q;

	/*
	 * The result, which includes guard and round bits, is exact iff
	 * x is now zero; any nonzero bits in x represent sticky bits.
	 */
	x->fp_sticky = x0 | x1 | x2 | x3;
	DUMPFPN(FPE_REG, x);
	return (x);
}