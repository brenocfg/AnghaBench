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
struct TYPE_2__ {unsigned long idle_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_PNV_CORE_IDLE_LOCK_BIT ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,unsigned long*) ; 
 int cpu_first_thread_sibling (int) ; 
 TYPE_1__** paca_ptrs ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static inline void atomic_unlock_thread_idle(void)
{
	int cpu = raw_smp_processor_id();
	int first = cpu_first_thread_sibling(cpu);
	unsigned long *state = &paca_ptrs[first]->idle_state;

	BUG_ON(!test_bit(NR_PNV_CORE_IDLE_LOCK_BIT, state));
	clear_bit_unlock(NR_PNV_CORE_IDLE_LOCK_BIT, state);
}