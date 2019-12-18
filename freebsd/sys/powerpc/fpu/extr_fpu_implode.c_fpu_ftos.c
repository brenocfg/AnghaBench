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
struct fpn {int fp_sign; int fp_exp; int* fp_mant; } ;
struct fpemu {int fe_cx; int fe_fpscr; } ;

/* Variables and functions */
 int FPSCR_FI ; 
 int FPSCR_UX ; 
 int FP_NG ; 
 int FP_NMANT ; 
 scalar_t__ ISINF (struct fpn*) ; 
 scalar_t__ ISNAN (struct fpn*) ; 
 scalar_t__ ISZERO (struct fpn*) ; 
 int SNG_EXP (int) ; 
 int SNG_EXP_BIAS ; 
 int SNG_EXP_INFNAN ; 
 int SNG_FRACBITS ; 
 int SNG_MASK ; 
 int /*<<< orphan*/  fpu_shr (struct fpn*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ round (struct fpemu*,struct fpn*) ; 
 scalar_t__ toinf (struct fpemu*,int) ; 

u_int
fpu_ftos(struct fpemu *fe, struct fpn *fp)
{
	u_int sign = fp->fp_sign << 31;
	int exp;

#define	SNG_EXP(e)	((e) << SNG_FRACBITS)	/* makes e an exponent */
#define	SNG_MASK	(SNG_EXP(1) - 1)	/* mask for fraction */

	/* Take care of non-numbers first. */
	if (ISNAN(fp)) {
		/*
		 * Preserve upper bits of NaN, per SPARC V8 appendix N.
		 * Note that fp->fp_mant[0] has the quiet bit set,
		 * even if it is classified as a signalling NaN.
		 */
		(void) fpu_shr(fp, FP_NMANT - 1 - SNG_FRACBITS);
		exp = SNG_EXP_INFNAN;
		goto done;
	}
	if (ISINF(fp))
		return (sign | SNG_EXP(SNG_EXP_INFNAN));
	if (ISZERO(fp))
		return (sign);

	/*
	 * Normals (including subnormals).  Drop all the fraction bits
	 * (including the explicit ``implied'' 1 bit) down into the
	 * single-precision range.  If the number is subnormal, move
	 * the ``implied'' 1 into the explicit range as well, and shift
	 * right to introduce leading zeroes.  Rounding then acts
	 * differently for normals and subnormals: the largest subnormal
	 * may round to the smallest normal (1.0 x 2^minexp), or may
	 * remain subnormal.  In the latter case, signal an underflow
	 * if the result was inexact or if underflow traps are enabled.
	 *
	 * Rounding a normal, on the other hand, always produces another
	 * normal (although either way the result might be too big for
	 * single precision, and cause an overflow).  If rounding a
	 * normal produces 2.0 in the fraction, we need not adjust that
	 * fraction at all, since both 1.0 and 2.0 are zero under the
	 * fraction mask.
	 *
	 * Note that the guard and round bits vanish from the number after
	 * rounding.
	 */
	if ((exp = fp->fp_exp + SNG_EXP_BIAS) <= 0) {	/* subnormal */
		/* -NG for g,r; -SNG_FRACBITS-exp for fraction */
		(void) fpu_shr(fp, FP_NMANT - FP_NG - SNG_FRACBITS - exp);
		if (round(fe, fp) && fp->fp_mant[3] == SNG_EXP(1))
			return (sign | SNG_EXP(1) | 0);
		if ((fe->fe_cx & FPSCR_FI) ||
		    (fe->fe_fpscr & FPSCR_UX))
			fe->fe_cx |= FPSCR_UX;
		return (sign | SNG_EXP(0) | fp->fp_mant[3]);
	}
	/* -FP_NG for g,r; -1 for implied 1; -SNG_FRACBITS for fraction */
	(void) fpu_shr(fp, FP_NMANT - FP_NG - 1 - SNG_FRACBITS);
#ifdef DIAGNOSTIC
	if ((fp->fp_mant[3] & SNG_EXP(1 << FP_NG)) == 0)
		panic("fpu_ftos");
#endif
	if (round(fe, fp) && fp->fp_mant[3] == SNG_EXP(2))
		exp++;
	if (exp >= SNG_EXP_INFNAN) {
		/* overflow to inf or to max single */
		if (toinf(fe, sign))
			return (sign | SNG_EXP(SNG_EXP_INFNAN));
		return (sign | SNG_EXP(SNG_EXP_INFNAN - 1) | SNG_MASK);
	}
done:
	/* phew, made it */
	return (sign | SNG_EXP(exp) | (fp->fp_mant[3] & SNG_MASK));
}