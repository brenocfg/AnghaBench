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
struct fpn {int fp_sign; int fp_class; int fp_exp; int* fp_mant; } ;
struct fpemu {int /*<<< orphan*/  fe_cx; } ;

/* Variables and functions */
#define  FPC_NUM 129 
#define  FPC_ZERO 128 
 int /*<<< orphan*/  FPSCR_UX ; 
 int /*<<< orphan*/  FPSCR_VXCVI ; 
 int /*<<< orphan*/  FP_NMANT ; 
 int /*<<< orphan*/  fpu_shr (struct fpn*,int /*<<< orphan*/ ) ; 

u_int
fpu_ftoi(struct fpemu *fe, struct fpn *fp)
{
	u_int i;
	int sign, exp;

	sign = fp->fp_sign;
	switch (fp->fp_class) {

	case FPC_ZERO:
		return (0);

	case FPC_NUM:
		/*
		 * If exp >= 2^32, overflow.  Otherwise shift value right
		 * into last mantissa word (this will not exceed 0xffffffff),
		 * shifting any guard and round bits out into the sticky
		 * bit.  Then ``round'' towards zero, i.e., just set an
		 * inexact exception if sticky is set (see round()).
		 * If the result is > 0x80000000, or is positive and equals
		 * 0x80000000, overflow; otherwise the last fraction word
		 * is the result.
		 */
		if ((exp = fp->fp_exp) >= 32)
			break;
		/* NB: the following includes exp < 0 cases */
		if (fpu_shr(fp, FP_NMANT - 1 - exp) != 0)
			fe->fe_cx |= FPSCR_UX;
		i = fp->fp_mant[3];
		if (i >= ((u_int)0x80000000 + sign))
			break;
		return (sign ? -i : i);

	default:		/* Inf, qNaN, sNaN */
		break;
	}
	/* overflow: replace any inexact exception with invalid */
	fe->fe_cx |= FPSCR_VXCVI;
	return (0x7fffffff + sign);
}