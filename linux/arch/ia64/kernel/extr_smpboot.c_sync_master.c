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
 size_t MASTER ; 
 unsigned long NUM_ITERS ; 
 unsigned long NUM_ROUNDS ; 
 size_t SLAVE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__* go ; 
 scalar_t__ ia64_get_itc () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void
sync_master (void *arg)
{
	unsigned long flags, i;

	go[MASTER] = 0;

	local_irq_save(flags);
	{
		for (i = 0; i < NUM_ROUNDS*NUM_ITERS; ++i) {
			while (!go[MASTER])
				cpu_relax();
			go[MASTER] = 0;
			go[SLAVE] = ia64_get_itc();
		}
	}
	local_irq_restore(flags);
}