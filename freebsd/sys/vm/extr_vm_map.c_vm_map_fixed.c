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
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  int /*<<< orphan*/  vm_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAP_CHECK_EXCL ; 
 int MAP_STACK_GROWS_DOWN ; 
 int MAP_STACK_GROWS_UP ; 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sgrowsiz ; 
 int /*<<< orphan*/  vm_map_delete (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int vm_map_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 int vm_map_stack_locked (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 

int
vm_map_fixed(vm_map_t map, vm_object_t object, vm_ooffset_t offset,
    vm_offset_t start, vm_size_t length, vm_prot_t prot,
    vm_prot_t max, int cow)
{
	vm_offset_t end;
	int result;

	end = start + length;
	KASSERT((cow & (MAP_STACK_GROWS_DOWN | MAP_STACK_GROWS_UP)) == 0 ||
	    object == NULL,
	    ("vm_map_fixed: non-NULL backing object for stack"));
	vm_map_lock(map);
	VM_MAP_RANGE_CHECK(map, start, end);
	if ((cow & MAP_CHECK_EXCL) == 0)
		vm_map_delete(map, start, end);
	if ((cow & (MAP_STACK_GROWS_DOWN | MAP_STACK_GROWS_UP)) != 0) {
		result = vm_map_stack_locked(map, start, length, sgrowsiz,
		    prot, max, cow);
	} else {
		result = vm_map_insert(map, object, offset, start, end,
		    prot, max, cow);
	}
	vm_map_unlock(map);
	return (result);
}