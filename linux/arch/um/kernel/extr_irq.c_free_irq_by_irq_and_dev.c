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
struct irq_entry {struct irq_entry* next; } ;

/* Variables and functions */
 struct irq_entry* active_fds ; 
 int /*<<< orphan*/  do_free_by_irq_and_dev (struct irq_entry*,unsigned int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garbage_collect_irq_entries () ; 
 int /*<<< orphan*/  irq_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_irq_by_irq_and_dev(unsigned int irq, void *dev)
{
	struct irq_entry *to_free;
	unsigned long flags;

	spin_lock_irqsave(&irq_lock, flags);
	to_free = active_fds;
	while (to_free != NULL) {
		do_free_by_irq_and_dev(
			to_free,
			irq,
			dev,
			0
		);
		to_free = to_free->next;
	}
	garbage_collect_irq_entries();
	spin_unlock_irqrestore(&irq_lock, flags);
}