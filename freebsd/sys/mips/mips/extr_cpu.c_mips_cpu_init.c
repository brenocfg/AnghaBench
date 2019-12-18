#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tlb_nentries; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMWIRED_ENTRIES ; 
 int /*<<< orphan*/  cpu_identify () ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  mips_config_cache (TYPE_1__*) ; 
 int /*<<< orphan*/  mips_dcache_wbinv_all () ; 
 int /*<<< orphan*/  mips_get_identity (TYPE_1__*) ; 
 int /*<<< orphan*/  mips_icache_sync_all () ; 
 int /*<<< orphan*/  mips_vector_init () ; 
 int /*<<< orphan*/  mips_wr_wired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_tlbentries ; 
 int /*<<< orphan*/  platform_cpu_init () ; 
 int /*<<< orphan*/  tlb_invalidate_all () ; 

void
mips_cpu_init(void)
{
	platform_cpu_init();
	mips_get_identity(&cpuinfo);
	num_tlbentries = cpuinfo.tlb_nentries;
	mips_wr_wired(0);
	tlb_invalidate_all();
	mips_wr_wired(VMWIRED_ENTRIES);
	mips_config_cache(&cpuinfo);
	mips_vector_init();

	mips_icache_sync_all();
	mips_dcache_wbinv_all();
	/* Print some info about CPU */
	cpu_identify();
}