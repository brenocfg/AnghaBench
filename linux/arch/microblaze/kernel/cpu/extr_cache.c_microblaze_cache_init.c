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
struct scache {int dummy; } ;
struct TYPE_2__ {int use_instr; scalar_t__ ver_code; scalar_t__ dcache_wb; } ;

/* Variables and functions */
 scalar_t__ CPUVER_7_20_A ; 
 scalar_t__ CPUVER_7_20_D ; 
 int PVR2_USE_MSR_INSTR ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  enable_dcache () ; 
 int /*<<< orphan*/  enable_icache () ; 
 int /*<<< orphan*/  invalidate_icache () ; 
 struct scache* mbc ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  wb_msr ; 
 int /*<<< orphan*/  wb_nomsr ; 
 int /*<<< orphan*/  wt_msr ; 
 int /*<<< orphan*/  wt_msr_noirq ; 
 int /*<<< orphan*/  wt_nomsr ; 
 int /*<<< orphan*/  wt_nomsr_noirq ; 

void microblaze_cache_init(void)
{
	if (cpuinfo.use_instr & PVR2_USE_MSR_INSTR) {
		if (cpuinfo.dcache_wb) {
			pr_info("wb_msr\n");
			mbc = (struct scache *)&wb_msr;
			if (cpuinfo.ver_code <= CPUVER_7_20_D) {
				/* MS: problem with signal handling - hw bug */
				pr_info("WB won't work properly\n");
			}
		} else {
			if (cpuinfo.ver_code >= CPUVER_7_20_A) {
				pr_info("wt_msr_noirq\n");
				mbc = (struct scache *)&wt_msr_noirq;
			} else {
				pr_info("wt_msr\n");
				mbc = (struct scache *)&wt_msr;
			}
		}
	} else {
		if (cpuinfo.dcache_wb) {
			pr_info("wb_nomsr\n");
			mbc = (struct scache *)&wb_nomsr;
			if (cpuinfo.ver_code <= CPUVER_7_20_D) {
				/* MS: problem with signal handling - hw bug */
				pr_info("WB won't work properly\n");
			}
		} else {
			if (cpuinfo.ver_code >= CPUVER_7_20_A) {
				pr_info("wt_nomsr_noirq\n");
				mbc = (struct scache *)&wt_nomsr_noirq;
			} else {
				pr_info("wt_nomsr\n");
				mbc = (struct scache *)&wt_nomsr;
			}
		}
	}
	/*
	 * FIXME Invalidation is done in U-BOOT
	 * WT cache: Data is already written to main memory
	 * WB cache: Discard data on noMMU which caused that kernel doesn't boot
	 */
	/* invalidate_dcache(); */
	enable_dcache();

	invalidate_icache();
	enable_icache();
}