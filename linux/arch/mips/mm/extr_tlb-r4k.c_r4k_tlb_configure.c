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
struct TYPE_2__ {scalar_t__ tlbsize; } ;

/* Variables and functions */
 scalar_t__ CPU_R10000 ; 
 scalar_t__ CPU_R12000 ; 
 scalar_t__ CPU_R14000 ; 
 scalar_t__ CPU_R16000 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_ELPA ; 
 int PG_RIE ; 
 int PG_XIE ; 
 scalar_t__ PM_DEFAULT_MASK ; 
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 scalar_t__ cpu_has_rixi ; 
 TYPE_1__ current_cpu_data ; 
 scalar_t__ current_cpu_type () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_c0_pagemask () ; 
 int /*<<< orphan*/  set_c0_pagegrain (int) ; 
 scalar_t__ temp_tlb_entry ; 
 int /*<<< orphan*/  write_c0_framemask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_pagemask (scalar_t__) ; 
 int /*<<< orphan*/  write_c0_wired (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r4k_tlb_configure(void)
{
	/*
	 * You should never change this register:
	 *   - On R4600 1.7 the tlbp never hits for pages smaller than
	 *     the value in the c0_pagemask register.
	 *   - The entire mm handling assumes the c0_pagemask register to
	 *     be set to fixed-size pages.
	 */
	write_c0_pagemask(PM_DEFAULT_MASK);
	back_to_back_c0_hazard();
	if (read_c0_pagemask() != PM_DEFAULT_MASK)
		panic("MMU doesn't support PAGE_SIZE=0x%lx", PAGE_SIZE);

	write_c0_wired(0);
	if (current_cpu_type() == CPU_R10000 ||
	    current_cpu_type() == CPU_R12000 ||
	    current_cpu_type() == CPU_R14000 ||
	    current_cpu_type() == CPU_R16000)
		write_c0_framemask(0);

	if (cpu_has_rixi) {
		/*
		 * Enable the no read, no exec bits, and enable large physical
		 * address.
		 */
#ifdef CONFIG_64BIT
		set_c0_pagegrain(PG_RIE | PG_XIE | PG_ELPA);
#else
		set_c0_pagegrain(PG_RIE | PG_XIE);
#endif
	}

	temp_tlb_entry = current_cpu_data.tlbsize - 1;

	/* From this point on the ARC firmware is dead.	 */
	local_flush_tlb_all();

	/* Did I tell you that ARC SUCKS?  */
}