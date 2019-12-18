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
struct fpemu {int /*<<< orphan*/  fe_fsr; } ;

/* Variables and functions */
 int FSR_GET_RD (int /*<<< orphan*/ ) ; 
#define  FSR_RD_N 131 
#define  FSR_RD_NINF 130 
#define  FSR_RD_PINF 129 
#define  FSR_RD_Z 128 

__attribute__((used)) static int
toinf(struct fpemu *fe, int sign)
{
	int inf;

	/* look at rounding direction */
	switch (FSR_GET_RD(fe->fe_fsr)) {
	default:
	case FSR_RD_N:		/* the nearest value is always Inf */
		inf = 1;
		break;

	case FSR_RD_Z:		/* toward 0 => never towards Inf */
		inf = 0;
		break;

	case FSR_RD_PINF:	/* toward +Inf iff positive */
		inf = sign == 0;
		break;

	case FSR_RD_NINF:	/* toward -Inf iff negative */
		inf = sign;
		break;
	}
	return (inf);
}