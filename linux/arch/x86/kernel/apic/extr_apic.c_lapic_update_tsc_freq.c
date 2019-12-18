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
 int /*<<< orphan*/  __lapic_update_tsc_freq ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lapic_update_tsc_freq(void)
{
	/*
	 * The clockevent device's ->mult and ->shift can both be
	 * changed. In order to avoid races, schedule the frequency
	 * update code on each CPU.
	 */
	on_each_cpu(__lapic_update_tsc_freq, NULL, 0);
}