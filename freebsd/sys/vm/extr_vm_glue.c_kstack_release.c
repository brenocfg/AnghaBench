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
typedef  scalar_t__ vm_offset_t ;
struct TYPE_2__ {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstack_pages ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 int /*<<< orphan*/  vm_thread_stack_dispose (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kstack_release(void *arg, void **store, int cnt)
{
	vm_offset_t ks;
	int i;

	for (i = 0; i < cnt; i++) {
		ks = (vm_offset_t)store[i];
		vm_thread_stack_dispose(
		    PHYS_TO_VM_PAGE(pmap_kextract(ks))->object,
		    ks, kstack_pages);
	}
}