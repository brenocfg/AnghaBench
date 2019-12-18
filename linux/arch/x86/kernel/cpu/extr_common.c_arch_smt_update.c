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
 int /*<<< orphan*/  apic_smt_update () ; 
 int /*<<< orphan*/  cpu_bugs_smt_update () ; 

void arch_smt_update(void)
{
	/* Handle the speculative execution misfeatures */
	cpu_bugs_smt_update();
	/* Check whether IPI broadcasting can be enabled */
	apic_smt_update();
}