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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ ARM_TMR_FREQUENCY_VARIES ; 
 int /*<<< orphan*/ * arm_tmr_et ; 
 scalar_t__ arm_tmr_freq ; 
 int arm_tmr_freq_varies ; 
 int /*<<< orphan*/  et_change_frequency (int /*<<< orphan*/ *,scalar_t__) ; 

void
arm_tmr_change_frequency(uint64_t newfreq)
{

	if (newfreq == ARM_TMR_FREQUENCY_VARIES) {
		arm_tmr_freq_varies = true;
		return;
	}

	arm_tmr_freq = newfreq;
	if (arm_tmr_et != NULL)
		et_change_frequency(arm_tmr_et, newfreq);
}