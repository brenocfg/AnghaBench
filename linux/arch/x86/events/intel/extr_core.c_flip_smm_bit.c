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
 int /*<<< orphan*/  DEBUGCTLMSR_FREEZE_IN_SMM_BIT ; 
 int /*<<< orphan*/  MSR_IA32_DEBUGCTLMSR ; 
 int /*<<< orphan*/  msr_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msr_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flip_smm_bit(void *data)
{
	unsigned long set = *(unsigned long *)data;

	if (set > 0) {
		msr_set_bit(MSR_IA32_DEBUGCTLMSR,
			    DEBUGCTLMSR_FREEZE_IN_SMM_BIT);
	} else {
		msr_clear_bit(MSR_IA32_DEBUGCTLMSR,
			      DEBUGCTLMSR_FREEZE_IN_SMM_BIT);
	}
}