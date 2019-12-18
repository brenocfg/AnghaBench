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
 scalar_t__ direct_mode_enabled ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hv_clock_event ; 
 int /*<<< orphan*/  hv_remove_stimer0_irq (scalar_t__) ; 
 scalar_t__ stimer0_irq ; 

void hv_stimer_free(void)
{
	if (direct_mode_enabled && (stimer0_irq != 0)) {
		hv_remove_stimer0_irq(stimer0_irq);
		stimer0_irq = 0;
	}
	free_percpu(hv_clock_event);
	hv_clock_event = NULL;
}