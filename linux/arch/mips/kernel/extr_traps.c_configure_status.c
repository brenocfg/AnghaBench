#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int isa_level; } ;

/* Variables and functions */
 int MIPS_CPU_ISA_IV ; 
 unsigned int ST0_BEV ; 
 unsigned int ST0_CU ; 
 unsigned int ST0_CU0 ; 
 unsigned int ST0_FR ; 
 unsigned int ST0_KX ; 
 unsigned int ST0_MX ; 
 unsigned int ST0_RE ; 
 unsigned int ST0_SX ; 
 unsigned int ST0_TS ; 
 unsigned int ST0_UX ; 
 unsigned int ST0_XX ; 
 int /*<<< orphan*/  change_c0_status (unsigned int,unsigned int) ; 
 scalar_t__ cpu_has_dsp ; 
 TYPE_1__ current_cpu_data ; 

__attribute__((used)) static void configure_status(void)
{
	/*
	 * Disable coprocessors and select 32-bit or 64-bit addressing
	 * and the 16/32 or 32/32 FPR register model.  Reset the BEV
	 * flag that some firmware may have left set and the TS bit (for
	 * IP27).  Set XX for ISA IV code to work.
	 */
	unsigned int status_set = ST0_CU0;
#ifdef CONFIG_64BIT
	status_set |= ST0_FR|ST0_KX|ST0_SX|ST0_UX;
#endif
	if (current_cpu_data.isa_level & MIPS_CPU_ISA_IV)
		status_set |= ST0_XX;
	if (cpu_has_dsp)
		status_set |= ST0_MX;

	change_c0_status(ST0_CU|ST0_MX|ST0_RE|ST0_FR|ST0_BEV|ST0_TS|ST0_KX|ST0_SX|ST0_UX,
			 status_set);
}