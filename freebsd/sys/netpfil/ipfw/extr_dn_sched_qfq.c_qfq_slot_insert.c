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
typedef  unsigned int uint64_t ;
struct qfq_group {unsigned int S; unsigned int slot_shift; unsigned int front; int /*<<< orphan*/  full_slots; struct qfq_class** slots; } ;
struct qfq_class {struct qfq_class* next; } ;

/* Variables and functions */
 unsigned int QFQ_MAX_SLOTS ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
qfq_slot_insert(struct qfq_group *grp, struct qfq_class *cl, uint64_t roundedS)
{
	uint64_t slot = (roundedS - grp->S) >> grp->slot_shift;
	unsigned int i = (grp->front + slot) % QFQ_MAX_SLOTS;

	cl->next = grp->slots[i];
	grp->slots[i] = cl;
	__set_bit(slot, &grp->full_slots);
}