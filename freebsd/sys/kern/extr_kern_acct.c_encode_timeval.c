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
typedef  int uint32_t ;
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 scalar_t__ CALC_BITS ; 
 int FLT_MANT_DIG ; 
 int FLT_MAX_EXP ; 
 scalar_t__ LOG2_1M ; 
 int MANT_MASK ; 
 int fls (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static uint32_t
encode_timeval(struct timeval tv)
{
	int log2_s;
	int val, exp;	/* Unnormalized value and exponent */
	int norm_exp;	/* Normalized exponent */
	int shift;

	/*
	 * First calculate value and exponent to about CALC_BITS precision.
	 * Note that the following conditionals have been ordered so that
	 * the most common cases appear first.
	 */
	if (tv.tv_sec == 0) {
		if (tv.tv_usec == 0)
			return (0);
		exp = 0;
		val = tv.tv_usec;
	} else {
		/*
		 * Calculate the value to a precision of approximately
		 * CALC_BITS.
		 */
		log2_s = fls(tv.tv_sec) - 1;
		if (log2_s + LOG2_1M < CALC_BITS) {
			exp = 0;
			val = 1000000 * tv.tv_sec + tv.tv_usec;
		} else {
			exp = log2_s + LOG2_1M - CALC_BITS;
			val = (unsigned int)(((uint64_t)1000000 * tv.tv_sec +
			    tv.tv_usec) >> exp);
		}
	}
	/* Now normalize and pack the value into an IEEE-754 float. */
	norm_exp = fls(val) - 1;
	shift = FLT_MANT_DIG - norm_exp - 1;
#ifdef ACCT_DEBUG
	printf("val=%d exp=%d shift=%d log2(val)=%d\n",
	    val, exp, shift, norm_exp);
	printf("exp=%x mant=%x\n", FLT_MAX_EXP - 1 + exp + norm_exp,
	    ((shift > 0 ? (val << shift) : (val >> -shift)) & MANT_MASK));
#endif
	return (((FLT_MAX_EXP - 1 + exp + norm_exp) << (FLT_MANT_DIG - 1)) |
	    ((shift > 0 ? val << shift : val >> -shift) & MANT_MASK));
}