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
typedef  int uint32_t ;
struct fpn {int fp_sign; int* fp_mant; int fp_class; scalar_t__ fp_sticky; } ;
struct fpemu {int /*<<< orphan*/  fe_cx; } ;

/* Variables and functions */
#define  DOUBLE 129 
 int FPC_QNAN ; 
 int FPC_SNAN ; 
 int /*<<< orphan*/  FPSCR_VXSNAN ; 
 int FP_QUIETBIT ; 
#define  SINGLE 128 
 int fpu_dtof (struct fpn*,int,int) ; 
 int fpu_stof (struct fpn*,int) ; 

__attribute__((used)) static int
spe_explode(struct fpemu *fe, struct fpn *fp, uint32_t type,
    uint32_t hi, uint32_t lo)
{
	uint32_t s;

	fp->fp_sign = hi >> 31;
	fp->fp_sticky = 0;
	switch (type) {
	case SINGLE:
		s = fpu_stof(fp, hi);
		break;

	case DOUBLE:
		s = fpu_dtof(fp, hi, lo);
		break;
	}

	if (s == FPC_QNAN && (fp->fp_mant[0] & FP_QUIETBIT) == 0) {
		/*
		 * Input is a signalling NaN.  All operations that return
		 * an input NaN operand put it through a ``NaN conversion'',
		 * which basically just means ``turn on the quiet bit''.
		 * We do this here so that all NaNs internally look quiet
		 * (we can tell signalling ones by their class).
		 */
		fp->fp_mant[0] |= FP_QUIETBIT;
		fe->fe_cx = FPSCR_VXSNAN;	/* assert invalid operand */
		s = FPC_SNAN;
	}
	fp->fp_class = s;

	return (0);
}