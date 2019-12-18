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
struct cpumask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_mask_allbutself ) (struct cpumask const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __send_ipi_mask (struct cpumask const*,int) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,struct cpumask*) ; 
 int /*<<< orphan*/  cpumask_copy (struct cpumask*,struct cpumask const*) ; 
 TYPE_1__ orig_apic ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct cpumask const*,int) ; 

__attribute__((used)) static void hv_send_ipi_mask_allbutself(const struct cpumask *mask, int vector)
{
	unsigned int this_cpu = smp_processor_id();
	struct cpumask new_mask;
	const struct cpumask *local_mask;

	cpumask_copy(&new_mask, mask);
	cpumask_clear_cpu(this_cpu, &new_mask);
	local_mask = &new_mask;
	if (!__send_ipi_mask(local_mask, vector))
		orig_apic.send_IPI_mask_allbutself(mask, vector);
}