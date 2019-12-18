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
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  RIC_FLUSH_ALL ; 
 int /*<<< orphan*/  RIC_FLUSH_TLB ; 
 scalar_t__ early_cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlbiel_radix_set_isa300 (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tlbiel_all_isa300(unsigned int num_sets, unsigned int is)
{
	unsigned int set;

	asm volatile("ptesync": : :"memory");

	/*
	 * Flush the first set of the TLB, and the entire Page Walk Cache
	 * and partition table entries. Then flush the remaining sets of the
	 * TLB.
	 */

	if (early_cpu_has_feature(CPU_FTR_HVMODE)) {
		/* MSR[HV] should flush partition scope translations first. */
		tlbiel_radix_set_isa300(0, is, 0, RIC_FLUSH_ALL, 0);
		for (set = 1; set < num_sets; set++)
			tlbiel_radix_set_isa300(set, is, 0, RIC_FLUSH_TLB, 0);
	}

	/* Flush process scoped entries. */
	tlbiel_radix_set_isa300(0, is, 0, RIC_FLUSH_ALL, 1);
	for (set = 1; set < num_sets; set++)
		tlbiel_radix_set_isa300(set, is, 0, RIC_FLUSH_TLB, 1);

	asm volatile("ptesync": : :"memory");
}