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

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pti_add_kva_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pti ; 
 int /*<<< orphan*/  pti_obj ; 

void
pmap_pti_add_kva(vm_offset_t sva, vm_offset_t eva, bool exec)
{

	if (!pti)
		return;
	VM_OBJECT_WLOCK(pti_obj);
	pmap_pti_add_kva_locked(sva, eva, exec);
	VM_OBJECT_WUNLOCK(pti_obj);
}