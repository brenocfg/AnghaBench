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

/* Variables and functions */
 unsigned int FPCSR_mskDBZT ; 
 unsigned int FPCSR_mskIEXT ; 
 unsigned int FPCSR_mskIVOT ; 
 unsigned int FPCSR_mskOVFT ; 
 unsigned int FPCSR_mskUDFT ; 
 int FPE_FLTDIV ; 
 int FPE_FLTINV ; 
 int FPE_FLTOVF ; 
 int FPE_FLTRES ; 
 int FPE_FLTUND ; 

inline void fill_sigfpe_signo(unsigned int fpcsr, int *signo)
{
	if (fpcsr & FPCSR_mskOVFT)
		*signo = FPE_FLTOVF;
#ifndef CONFIG_SUPPORT_DENORMAL_ARITHMETIC
	else if (fpcsr & FPCSR_mskUDFT)
		*signo = FPE_FLTUND;
#endif
	else if (fpcsr & FPCSR_mskIVOT)
		*signo = FPE_FLTINV;
	else if (fpcsr & FPCSR_mskDBZT)
		*signo = FPE_FLTDIV;
	else if (fpcsr & FPCSR_mskIEXT)
		*signo = FPE_FLTRES;
}