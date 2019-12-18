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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct vmmap {int vm_size; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct vmmap*) ; 
 int /*<<< orphan*/  kva_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_qremove (int /*<<< orphan*/ ,int) ; 
 struct vmmap* vmmap_remove (void*) ; 

void
vunmap(void *addr)
{
	struct vmmap *vmmap;

	vmmap = vmmap_remove(addr);
	if (vmmap == NULL)
		return;
	pmap_qremove((vm_offset_t)addr, vmmap->vm_size / PAGE_SIZE);
	kva_free((vm_offset_t)addr, vmmap->vm_size);
	kfree(vmmap);
}