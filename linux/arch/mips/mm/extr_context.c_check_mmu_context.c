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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_VM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  asid_cache (unsigned int) ; 
 int /*<<< orphan*/  asid_versions_eq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_context (unsigned int,struct mm_struct*) ; 
 scalar_t__ cpu_has_mmid ; 
 int /*<<< orphan*/  get_new_mmu_context (struct mm_struct*) ; 
 unsigned int smp_processor_id () ; 

void check_mmu_context(struct mm_struct *mm)
{
	unsigned int cpu = smp_processor_id();

	/*
	 * This function is specific to ASIDs, and should not be called when
	 * MMIDs are in use.
	 */
	if (WARN_ON(IS_ENABLED(CONFIG_DEBUG_VM) && cpu_has_mmid))
		return;

	/* Check if our ASID is of an older version and thus invalid */
	if (!asid_versions_eq(cpu, cpu_context(cpu, mm), asid_cache(cpu)))
		get_new_mmu_context(mm);
}