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
typedef  int uint64_t ;
struct amd_et_state {int cur_threshold; int /*<<< orphan*/  last_intr; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;
struct TYPE_2__ {int /*<<< orphan*/  (* misc ) (int) ;} ;

/* Variables and functions */
 int CMCI ; 
 int MC_MISC_AMD_CNT_MASK ; 
 int MC_MISC_AMD_CNT_MAX ; 
 int MC_MISC_AMD_CNT_SHIFT ; 
 int MC_MISC_AMD_OVERFLOW ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 struct amd_et_state** amd_et_state ; 
 int /*<<< orphan*/  cpuid ; 
 TYPE_1__ mca_msr_ops ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  time_uptime ; 
 int update_threshold (int,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
amd_thresholding_update(enum scan_mode mode, int bank, int valid)
{
	struct amd_et_state *cc;
	uint64_t misc;
	int new_threshold;
	int count;

	cc = &amd_et_state[PCPU_GET(cpuid)][bank];
	misc = rdmsr(mca_msr_ops.misc(bank));
	count = (misc & MC_MISC_AMD_CNT_MASK) >> MC_MISC_AMD_CNT_SHIFT;
	count = count - (MC_MISC_AMD_CNT_MAX - cc->cur_threshold);

	new_threshold = update_threshold(mode, valid, cc->last_intr, count,
	    cc->cur_threshold, MC_MISC_AMD_CNT_MAX);

	cc->cur_threshold = new_threshold;
	misc &= ~MC_MISC_AMD_CNT_MASK;
	misc |= (uint64_t)(MC_MISC_AMD_CNT_MAX - cc->cur_threshold)
	    << MC_MISC_AMD_CNT_SHIFT;
	misc &= ~MC_MISC_AMD_OVERFLOW;
	wrmsr(mca_msr_ops.misc(bank), misc);
	if (mode == CMCI && valid)
		cc->last_intr = time_uptime;
}