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
typedef  scalar_t__ u_int ;
struct fpn {scalar_t__* fp_mant; scalar_t__ fp_exp; int fp_sticky; int /*<<< orphan*/  fp_sign; } ;
struct fpemu {int /*<<< orphan*/  fe_cx; struct fpn fe_f2; struct fpn fe_f1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DUMPFPN (int /*<<< orphan*/ ,struct fpn*) ; 
 int /*<<< orphan*/  FPE_REG ; 
 int /*<<< orphan*/  FPSCR_VXIMZ ; 
 int /*<<< orphan*/  FPSCR_VXSNAN ; 
 int /*<<< orphan*/  FPU_DECL_CARRY ; 
 scalar_t__ FP_2 ; 
 int FP_NG ; 
 scalar_t__ ISINF (struct fpn*) ; 
 scalar_t__ ISNAN (struct fpn*) ; 
 scalar_t__ ISZERO (struct fpn*) ; 
 int /*<<< orphan*/  ORDER (struct fpn*,struct fpn*) ; 
 int /*<<< orphan*/  SHR1 ; 
 int /*<<< orphan*/  SHR32 ; 
 int /*<<< orphan*/  STEP ; 
 struct fpn* fpu_newnan (struct fpemu*) ; 

struct fpn *
fpu_mul(struct fpemu *fe)
{
	struct fpn *x = &fe->fe_f1, *y = &fe->fe_f2;
	u_int a3, a2, a1, a0, x3, x2, x1, x0, bit, m;
	int sticky;
	FPU_DECL_CARRY;

	/*
	 * Put the `heavier' operand on the right (see fpu_emu.h).
	 * Then we will have one of the following cases, taken in the
	 * following order:
	 *
	 *  - y = NaN.  Implied: if only one is a signalling NaN, y is.
	 *	The result is y.
	 *  - y = Inf.  Implied: x != NaN (is 0, number, or Inf: the NaN
	 *    case was taken care of earlier).
	 *	If x = 0, the result is NaN.  Otherwise the result
	 *	is y, with its sign reversed if x is negative.
	 *  - x = 0.  Implied: y is 0 or number.
	 *	The result is 0 (with XORed sign as usual).
	 *  - other.  Implied: both x and y are numbers.
	 *	The result is x * y (XOR sign, multiply bits, add exponents).
	 */
	DPRINTF(FPE_REG, ("fpu_mul:\n"));
	DUMPFPN(FPE_REG, x);
	DUMPFPN(FPE_REG, y);
	DPRINTF(FPE_REG, ("=>\n"));

	ORDER(x, y);
	if (ISNAN(y)) {
		y->fp_sign ^= x->fp_sign;
		fe->fe_cx |= FPSCR_VXSNAN;
		DUMPFPN(FPE_REG, y);
		return (y);
	}
	if (ISINF(y)) {
		if (ISZERO(x)) {
			fe->fe_cx |= FPSCR_VXIMZ;
			return (fpu_newnan(fe));
		}
		y->fp_sign ^= x->fp_sign;
			DUMPFPN(FPE_REG, y);
		return (y);
	}
	if (ISZERO(x)) {
		x->fp_sign ^= y->fp_sign;
		DUMPFPN(FPE_REG, x);
		return (x);
	}

	/*
	 * Setup.  In the code below, the mask `m' will hold the current
	 * mantissa byte from y.  The variable `bit' denotes the bit
	 * within m.  We also define some macros to deal with everything.
	 */
	x3 = x->fp_mant[3];
	x2 = x->fp_mant[2];
	x1 = x->fp_mant[1];
	x0 = x->fp_mant[0];
	sticky = a3 = a2 = a1 = a0 = 0;

#define	ADD	/* A += X */ \
	FPU_ADDS(a3, a3, x3); \
	FPU_ADDCS(a2, a2, x2); \
	FPU_ADDCS(a1, a1, x1); \
	FPU_ADDC(a0, a0, x0)

#define	SHR1	/* A >>= 1, with sticky */ \
	sticky |= a3 & 1, a3 = (a3 >> 1) | (a2 << 31), \
	a2 = (a2 >> 1) | (a1 << 31), a1 = (a1 >> 1) | (a0 << 31), a0 >>= 1

#define	SHR32	/* A >>= 32, with sticky */ \
	sticky |= a3, a3 = a2, a2 = a1, a1 = a0, a0 = 0

#define	STEP	/* each 1-bit step of the multiplication */ \
	SHR1; if (bit & m) { ADD; }; bit <<= 1

	/*
	 * We are ready to begin.  The multiply loop runs once for each
	 * of the four 32-bit words.  Some words, however, are special.
	 * As noted above, the low order bits of Y are often zero.  Even
	 * if not, the first loop can certainly skip the guard bits.
	 * The last word of y has its highest 1-bit in position FP_NMANT-1,
	 * so we stop the loop when we move past that bit.
	 */
	if ((m = y->fp_mant[3]) == 0) {
		/* SHR32; */			/* unneeded since A==0 */
	} else {
		bit = 1 << FP_NG;
		do {
			STEP;
		} while (bit != 0);
	}
	if ((m = y->fp_mant[2]) == 0) {
		SHR32;
	} else {
		bit = 1;
		do {
			STEP;
		} while (bit != 0);
	}
	if ((m = y->fp_mant[1]) == 0) {
		SHR32;
	} else {
		bit = 1;
		do {
			STEP;
		} while (bit != 0);
	}
	m = y->fp_mant[0];		/* definitely != 0 */
	bit = 1;
	do {
		STEP;
	} while (bit <= m);

	/*
	 * Done with mantissa calculation.  Get exponent and handle
	 * 11.111...1 case, then put result in place.  We reuse x since
	 * it already has the right class (FP_NUM).
	 */
	m = x->fp_exp + y->fp_exp;
	if (a0 >= FP_2) {
		SHR1;
		m++;
	}
	x->fp_sign ^= y->fp_sign;
	x->fp_exp = m;
	x->fp_sticky = sticky;
	x->fp_mant[3] = a3;
	x->fp_mant[2] = a2;
	x->fp_mant[1] = a1;
	x->fp_mant[0] = a0;

	DUMPFPN(FPE_REG, x);
	return (x);
}