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
struct fpn {scalar_t__* fp_mant; scalar_t__ fp_sign; int /*<<< orphan*/  fp_class; } ;
struct fpemu {struct fpn fe_f3; int /*<<< orphan*/  fe_cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMPFPN (int /*<<< orphan*/ ,struct fpn*) ; 
 int /*<<< orphan*/  FPC_QNAN ; 
 int /*<<< orphan*/  FPE_REG ; 
 int /*<<< orphan*/  FPSCR_VXSNAN ; 
 scalar_t__ FP_1 ; 

struct fpn *
fpu_newnan(struct fpemu *fe)
{
	struct fpn *fp;

	fe->fe_cx |= FPSCR_VXSNAN;
	fp = &fe->fe_f3;
	fp->fp_class = FPC_QNAN;
	fp->fp_sign = 0;
	fp->fp_mant[0] = FP_1 - 1;
	fp->fp_mant[1] = fp->fp_mant[2] = fp->fp_mant[3] = ~0;
	DUMPFPN(FPE_REG, fp);
	return (fp);
}