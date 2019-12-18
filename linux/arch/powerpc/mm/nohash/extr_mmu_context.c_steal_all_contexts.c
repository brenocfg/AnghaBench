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
struct TYPE_2__ {scalar_t__ active; int /*<<< orphan*/  id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned int FIRST_CONTEXT ; 
 unsigned int LAST_CONTEXT ; 
 int /*<<< orphan*/  MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tlbil_all () ; 
 int /*<<< orphan*/  context_map ; 
 struct mm_struct** context_mm ; 
 unsigned int nr_free_contexts ; 
 int /*<<< orphan*/  pr_hardcont (char*,unsigned int,struct mm_struct*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/ * stale_map ; 

__attribute__((used)) static unsigned int steal_all_contexts(void)
{
	struct mm_struct *mm;
#ifdef CONFIG_SMP
	int cpu = smp_processor_id();
#endif
	unsigned int id;

	for (id = FIRST_CONTEXT; id <= LAST_CONTEXT; id++) {
		/* Pick up the victim mm */
		mm = context_mm[id];

		pr_hardcont(" | steal %d from 0x%p", id, mm);

		/* Mark this mm as having no context anymore */
		mm->context.id = MMU_NO_CONTEXT;
		if (id != FIRST_CONTEXT) {
			context_mm[id] = NULL;
			__clear_bit(id, context_map);
#ifdef DEBUG_MAP_CONSISTENCY
			mm->context.active = 0;
#endif
		}
#ifdef CONFIG_SMP
		__clear_bit(id, stale_map[cpu]);
#endif
	}

	/* Flush the TLB for all contexts (not to be used on SMP) */
	_tlbil_all();

	nr_free_contexts = LAST_CONTEXT - FIRST_CONTEXT;

	return FIRST_CONTEXT;
}