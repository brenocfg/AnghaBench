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
struct qfq_group {size_t front; int /*<<< orphan*/  full_slots; struct qfq_class** slots; } ;
struct qfq_class {struct qfq_class* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
qfq_front_slot_remove(struct qfq_group *grp)
{
	struct qfq_class **h = &grp->slots[grp->front];

	*h = (*h)->next;
	if (!*h)
		__clear_bit(0, &grp->full_slots);
}