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
 scalar_t__ doorbell_try_core_ipi (int) ; 
 int /*<<< orphan*/  ic_cause_ipi (int) ; 

__attribute__((used)) static void pnv_cause_ipi(int cpu)
{
	if (doorbell_try_core_ipi(cpu))
		return;

	ic_cause_ipi(cpu);
}