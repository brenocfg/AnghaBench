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
struct kvm_memory_slot {int /*<<< orphan*/  dirty_bitmap; scalar_t__ base_gfn; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  set_dirty_bits_atomic (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

void kvmppc_update_dirty_map(const struct kvm_memory_slot *memslot,
			     unsigned long gfn, unsigned long psize)
{
	unsigned long npages;

	if (!psize || !memslot->dirty_bitmap)
		return;
	npages = (psize + PAGE_SIZE - 1) / PAGE_SIZE;
	gfn -= memslot->base_gfn;
	set_dirty_bits_atomic(memslot->dirty_bitmap, gfn, npages);
}