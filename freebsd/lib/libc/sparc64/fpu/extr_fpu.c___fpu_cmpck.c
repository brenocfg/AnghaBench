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
typedef  int u_long ;
struct fpemu {int fe_cx; int fe_fsr; } ;

/* Variables and functions */
 int FSR_AEXC_SHIFT ; 
 int FSR_CEXC_SHIFT ; 
 int FSR_FTT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSR_FTT_IEEE ; 
 int FSR_FTT_MASK ; 
 int FSR_NV ; 
 int FSR_TEM_SHIFT ; 
 int SIGFPE ; 

__attribute__((used)) static int
__fpu_cmpck(struct fpemu *fe)
{
	u_long fsr;
	int cx;

	/*
	 * The only possible exception here is NV; catch it
	 * early and get out, as there is no result register.
	 */
	cx = fe->fe_cx;
	fsr = fe->fe_fsr | (cx << FSR_CEXC_SHIFT);
	if (cx != 0) {
		if (fsr & (FSR_NV << FSR_TEM_SHIFT)) {
			fe->fe_fsr = (fsr & ~FSR_FTT_MASK) |
			    FSR_FTT(FSR_FTT_IEEE);
			return (SIGFPE);
		}
		fsr |= FSR_NV << FSR_AEXC_SHIFT;
	}
	fe->fe_fsr = fsr;
	return (0);
}