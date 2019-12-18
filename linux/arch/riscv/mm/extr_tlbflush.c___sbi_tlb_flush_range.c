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
struct cpumask {int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  riscv_cpuid_to_hartid_mask (struct cpumask*,struct cpumask*) ; 
 int /*<<< orphan*/  sbi_remote_sfence_vma (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static void __sbi_tlb_flush_range(struct cpumask *cmask, unsigned long start,
				  unsigned long size)
{
	struct cpumask hmask;

	riscv_cpuid_to_hartid_mask(cmask, &hmask);
	sbi_remote_sfence_vma(hmask.bits, start, size);
}