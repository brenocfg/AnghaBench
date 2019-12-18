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
typedef  int /*<<< orphan*/  u8 ;
struct chip {int throttled; size_t throttle_reason; int /*<<< orphan*/  id; int /*<<< orphan*/  throttle_turbo; int /*<<< orphan*/  throttle_sub_turbo; } ;
struct TYPE_2__ {unsigned int max; unsigned int nominal; } ;

/* Variables and functions */
 unsigned long PMSR_PSAFE_ENABLE ; 
 unsigned long PMSR_SPR_EM_DISABLE ; 
 int /*<<< orphan*/  SPRN_PMSR ; 
 int /*<<< orphan*/  chip_info ; 
 int /*<<< orphan*/  extract_max_pstate (unsigned long) ; 
 unsigned long get_pmspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idx_to_pstate (unsigned int) ; 
 TYPE_1__ powernv_pstate_info ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  pr_warn_once (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int pstate_to_idx (int /*<<< orphan*/ ) ; 
 unsigned int smp_processor_id () ; 
 struct chip* this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * throttle_reason ; 
 int throttled ; 
 int /*<<< orphan*/  trace_powernv_throttle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void powernv_cpufreq_throttle_check(void *data)
{
	struct chip *chip;
	unsigned int cpu = smp_processor_id();
	unsigned long pmsr;
	u8 pmsr_pmax;
	unsigned int pmsr_pmax_idx;

	pmsr = get_pmspr(SPRN_PMSR);
	chip = this_cpu_read(chip_info);

	/* Check for Pmax Capping */
	pmsr_pmax = extract_max_pstate(pmsr);
	pmsr_pmax_idx = pstate_to_idx(pmsr_pmax);
	if (pmsr_pmax_idx != powernv_pstate_info.max) {
		if (chip->throttled)
			goto next;
		chip->throttled = true;
		if (pmsr_pmax_idx > powernv_pstate_info.nominal) {
			pr_warn_once("CPU %d on Chip %u has Pmax(0x%x) reduced below that of nominal frequency(0x%x)\n",
				     cpu, chip->id, pmsr_pmax,
				     idx_to_pstate(powernv_pstate_info.nominal));
			chip->throttle_sub_turbo++;
		} else {
			chip->throttle_turbo++;
		}
		trace_powernv_throttle(chip->id,
				      throttle_reason[chip->throttle_reason],
				      pmsr_pmax);
	} else if (chip->throttled) {
		chip->throttled = false;
		trace_powernv_throttle(chip->id,
				      throttle_reason[chip->throttle_reason],
				      pmsr_pmax);
	}

	/* Check if Psafe_mode_active is set in PMSR. */
next:
	if (pmsr & PMSR_PSAFE_ENABLE) {
		throttled = true;
		pr_info("Pstate set to safe frequency\n");
	}

	/* Check if SPR_EM_DISABLE is set in PMSR */
	if (pmsr & PMSR_SPR_EM_DISABLE) {
		throttled = true;
		pr_info("Frequency Control disabled from OS\n");
	}

	if (throttled) {
		pr_info("PMSR = %16lx\n", pmsr);
		pr_warn("CPU Frequency could be throttled\n");
	}
}