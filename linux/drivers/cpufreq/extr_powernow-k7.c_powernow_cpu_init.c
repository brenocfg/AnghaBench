#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t CFID; int /*<<< orphan*/  SVID; int /*<<< orphan*/  MFID; } ;
union msr_fidvidstatus {TYPE_1__ bits; int /*<<< orphan*/  val; } ;
struct TYPE_4__ {int /*<<< orphan*/  transition_latency; } ;
struct cpufreq_policy {scalar_t__ cpu; int /*<<< orphan*/  freq_table; TYPE_2__ cpuinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MSR_K7_FID_VID_STATUS ; 
 scalar_t__ acpi_force ; 
 int cpu_khz ; 
 int /*<<< orphan*/  cpufreq_scale (unsigned long,int,scalar_t__) ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int* fid_codes ; 
 scalar_t__ fixup_sgtc () ; 
 int fsb ; 
 scalar_t__ latency ; 
 int maximum_speed ; 
 int minimum_speed ; 
 int powernow_acpi_init () ; 
 int powernow_decode_bios (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernow_dmi_table ; 
 int /*<<< orphan*/  powernow_table ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalibrate_cpu_khz () ; 

__attribute__((used)) static int powernow_cpu_init(struct cpufreq_policy *policy)
{
	union msr_fidvidstatus fidvidstatus;
	int result;

	if (policy->cpu != 0)
		return -ENODEV;

	rdmsrl(MSR_K7_FID_VID_STATUS, fidvidstatus.val);

	recalibrate_cpu_khz();

	fsb = (10 * cpu_khz) / fid_codes[fidvidstatus.bits.CFID];
	if (!fsb) {
		pr_warn("can not determine bus frequency\n");
		return -EINVAL;
	}
	pr_debug("FSB: %3dMHz\n", fsb/1000);

	if (dmi_check_system(powernow_dmi_table) || acpi_force) {
		pr_info("PSB/PST known to be broken - trying ACPI instead\n");
		result = powernow_acpi_init();
	} else {
		result = powernow_decode_bios(fidvidstatus.bits.MFID,
				fidvidstatus.bits.SVID);
		if (result) {
			pr_info("Trying ACPI perflib\n");
			maximum_speed = 0;
			minimum_speed = -1;
			latency = 0;
			result = powernow_acpi_init();
			if (result) {
				pr_info("ACPI and legacy methods failed\n");
			}
		} else {
			/* SGTC use the bus clock as timer */
			latency = fixup_sgtc();
			pr_info("SGTC: %d\n", latency);
		}
	}

	if (result)
		return result;

	pr_info("Minimum speed %d MHz - Maximum speed %d MHz\n",
		minimum_speed/1000, maximum_speed/1000);

	policy->cpuinfo.transition_latency =
		cpufreq_scale(2000000UL, fsb, latency);
	policy->freq_table = powernow_table;

	return 0;
}