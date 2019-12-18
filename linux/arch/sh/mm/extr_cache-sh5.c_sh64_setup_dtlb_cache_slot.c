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
 int /*<<< orphan*/  dtlb_cache_slot ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  sh64_setup_tlb_slot (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline void
sh64_setup_dtlb_cache_slot(unsigned long eaddr, unsigned long asid,
			   unsigned long paddr)
{
	local_irq_disable();
	sh64_setup_tlb_slot(dtlb_cache_slot, eaddr, asid, paddr);
}