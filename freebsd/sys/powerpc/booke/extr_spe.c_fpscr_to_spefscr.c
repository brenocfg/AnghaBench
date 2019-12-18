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

/* Variables and functions */
 int FPSCR_OX ; 
 int FPSCR_UX ; 
 int FPSCR_VX ; 
 int FPSCR_XX ; 
 int FPSCR_ZX ; 
 int SPEFSCR_FDBZ ; 
 int SPEFSCR_FINV ; 
 int SPEFSCR_FOVF ; 
 int SPEFSCR_FUNF ; 
 int SPEFSCR_FX ; 

__attribute__((used)) static uint32_t fpscr_to_spefscr(uint32_t fpscr)
{
	uint32_t spefscr;

	spefscr = 0;

	if (fpscr & FPSCR_VX)
		spefscr |= SPEFSCR_FINV;
	if (fpscr & FPSCR_OX)
		spefscr |= SPEFSCR_FOVF;
	if (fpscr & FPSCR_UX)
		spefscr |= SPEFSCR_FUNF;
	if (fpscr & FPSCR_ZX)
		spefscr |= SPEFSCR_FDBZ;
	if (fpscr & FPSCR_XX)
		spefscr |= SPEFSCR_FX;

	return (spefscr);
}