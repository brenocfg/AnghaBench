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
struct fpn {int* fp_mant; int fp_sticky; int /*<<< orphan*/  fp_sign; } ;
struct fpemu {int fe_cx; int fe_fpscr; } ;

/* Variables and functions */
 int FPSCR_FI ; 
 int FPSCR_FR ; 
 int FPSCR_RN ; 
 int FPSCR_XX ; 
 int /*<<< orphan*/  FPU_ADDC (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPU_ADDCS (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPU_ADDS (int,int,int) ; 
 int /*<<< orphan*/  FPU_DECL_CARRY ; 
 int FP_NG ; 
#define  FP_RM 131 
#define  FP_RN 130 
#define  FP_RP 129 
#define  FP_RZ 128 

__attribute__((used)) static int
round(struct fpemu *fe, struct fpn *fp)
{
	u_int m0, m1, m2, m3;
	int gr, s;
	FPU_DECL_CARRY;

	m0 = fp->fp_mant[0];
	m1 = fp->fp_mant[1];
	m2 = fp->fp_mant[2];
	m3 = fp->fp_mant[3];
	gr = m3 & 3;
	s = fp->fp_sticky;

	/* mant >>= FP_NG */
	m3 = (m3 >> FP_NG) | (m2 << (32 - FP_NG));
	m2 = (m2 >> FP_NG) | (m1 << (32 - FP_NG));
	m1 = (m1 >> FP_NG) | (m0 << (32 - FP_NG));
	m0 >>= FP_NG;

	if ((gr | s) == 0)	/* result is exact: no rounding needed */
		goto rounddown;

	fe->fe_cx |= FPSCR_XX|FPSCR_FI;	/* inexact */

	/* Go to rounddown to round down; break to round up. */
	switch ((fe->fe_fpscr) & FPSCR_RN) {

	case FP_RN:
	default:
		/*
		 * Round only if guard is set (gr & 2).  If guard is set,
		 * but round & sticky both clear, then we want to round
		 * but have a tie, so round to even, i.e., add 1 iff odd.
		 */
		if ((gr & 2) == 0)
			goto rounddown;
		if ((gr & 1) || fp->fp_sticky || (m3 & 1))
			break;
		goto rounddown;

	case FP_RZ:
		/* Round towards zero, i.e., down. */
		goto rounddown;

	case FP_RM:
		/* Round towards -Inf: up if negative, down if positive. */
		if (fp->fp_sign)
			break;
		goto rounddown;

	case FP_RP:
		/* Round towards +Inf: up if positive, down otherwise. */
		if (!fp->fp_sign)
			break;
		goto rounddown;
	}

	/* Bump low bit of mantissa, with carry. */
	fe->fe_cx |= FPSCR_FR;

	FPU_ADDS(m3, m3, 1);
	FPU_ADDCS(m2, m2, 0);
	FPU_ADDCS(m1, m1, 0);
	FPU_ADDC(m0, m0, 0);
	fp->fp_mant[0] = m0;
	fp->fp_mant[1] = m1;
	fp->fp_mant[2] = m2;
	fp->fp_mant[3] = m3;
	return (1);

rounddown:
	fp->fp_mant[0] = m0;
	fp->fp_mant[1] = m1;
	fp->fp_mant[2] = m2;
	fp->fp_mant[3] = m3;
	return (0);
}