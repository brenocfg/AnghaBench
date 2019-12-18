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
struct fpemu {int fe_fpscr; int /*<<< orphan*/  fe_cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_OX ; 
 int FPSCR_RN ; 
#define  FP_RM 131 
#define  FP_RN 130 
#define  FP_RP 129 
#define  FP_RZ 128 

__attribute__((used)) static int
toinf(struct fpemu *fe, int sign)
{
	int inf;

	/* look at rounding direction */
	switch ((fe->fe_fpscr) & FPSCR_RN) {

	default:
	case FP_RN:		/* the nearest value is always Inf */
		inf = 1;
		break;

	case FP_RZ:		/* toward 0 => never towards Inf */
		inf = 0;
		break;

	case FP_RP:		/* toward +Inf iff positive */
		inf = sign == 0;
		break;

	case FP_RM:		/* toward -Inf iff negative */
		inf = sign;
		break;
	}
	if (inf)
		fe->fe_cx |= FPSCR_OX;
	return (inf);
}