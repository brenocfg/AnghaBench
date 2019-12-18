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
struct sq_mapping {struct sq_mapping* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct sq_mapping* sq_mapping_list ; 
 int /*<<< orphan*/  sq_mapping_lock ; 

__attribute__((used)) static inline void sq_mapping_list_del(struct sq_mapping *map)
{
	struct sq_mapping **p, *tmp;

	spin_lock_irq(&sq_mapping_lock);

	for (p = &sq_mapping_list; (tmp = *p); p = &tmp->next)
		if (tmp == map) {
			*p = tmp->next;
			break;
		}

	spin_unlock_irq(&sq_mapping_lock);
}