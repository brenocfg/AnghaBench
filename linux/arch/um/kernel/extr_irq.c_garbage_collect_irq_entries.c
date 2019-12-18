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
struct irq_entry {struct irq_entry* next; int /*<<< orphan*/ ** irq_array; } ;

/* Variables and functions */
 int MAX_IRQ_TYPE ; 
 struct irq_entry* active_fds ; 
 int /*<<< orphan*/  kfree (struct irq_entry*) ; 

__attribute__((used)) static void garbage_collect_irq_entries(void)
{
	int i;
	bool reap;
	struct irq_entry *walk;
	struct irq_entry *previous = NULL;
	struct irq_entry *to_free;

	if (active_fds == NULL)
		return;
	walk = active_fds;
	while (walk != NULL) {
		reap = true;
		for (i = 0; i < MAX_IRQ_TYPE ; i++) {
			if (walk->irq_array[i] != NULL) {
				reap = false;
				break;
			}
		}
		if (reap) {
			if (previous == NULL)
				active_fds = walk->next;
			else
				previous->next = walk->next;
			to_free = walk;
		} else {
			to_free = NULL;
		}
		walk = walk->next;
		kfree(to_free);
	}
}