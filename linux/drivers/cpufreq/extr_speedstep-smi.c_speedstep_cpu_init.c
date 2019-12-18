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
struct cpufreq_policy {scalar_t__ cpu; TYPE_1__* freq_table; } ;
struct TYPE_2__ {unsigned int frequency; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t SPEEDSTEP_HIGH ; 
 size_t SPEEDSTEP_LOW ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_1__* speedstep_freqs ; 
 int speedstep_get_freqs (int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speedstep_processor ; 
 int /*<<< orphan*/  speedstep_set_state ; 
 int speedstep_smi_get_freqs (unsigned int*,unsigned int*) ; 
 int speedstep_smi_ownership () ; 

__attribute__((used)) static int speedstep_cpu_init(struct cpufreq_policy *policy)
{
	int result;
	unsigned int *low, *high;

	/* capability check */
	if (policy->cpu != 0)
		return -ENODEV;

	result = speedstep_smi_ownership();
	if (result) {
		pr_debug("fails in acquiring ownership of a SMI interface.\n");
		return -EINVAL;
	}

	/* detect low and high frequency */
	low = &speedstep_freqs[SPEEDSTEP_LOW].frequency;
	high = &speedstep_freqs[SPEEDSTEP_HIGH].frequency;

	result = speedstep_smi_get_freqs(low, high);
	if (result) {
		/* fall back to speedstep_lib.c dection mechanism:
		 * try both states out */
		pr_debug("could not detect low and high frequencies "
				"by SMI call.\n");
		result = speedstep_get_freqs(speedstep_processor,
				low, high,
				NULL,
				&speedstep_set_state);

		if (result) {
			pr_debug("could not detect two different speeds"
					" -- aborting.\n");
			return result;
		} else
			pr_debug("workaround worked.\n");
	}

	policy->freq_table = speedstep_freqs;

	return 0;
}