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
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  pmap_ptelist_free (scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void
pmap_ptelist_init(vm_offset_t *head, void *base, int npages)
{
	int i;
	vm_offset_t va;

	*head = 0;
	for (i = npages - 1; i >= 0; i--) {
		va = (vm_offset_t)base + i * PAGE_SIZE;
		pmap_ptelist_free(head, va);
	}
}