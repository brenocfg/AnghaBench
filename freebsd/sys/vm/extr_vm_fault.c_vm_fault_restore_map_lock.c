#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct faultstate {int lookup_still_valid; TYPE_1__* first_object; int /*<<< orphan*/  map; } ;
struct TYPE_4__ {int /*<<< orphan*/  paging_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ REFCOUNT_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trylock_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_fault_restore_map_lock(struct faultstate *fs)
{

	VM_OBJECT_ASSERT_WLOCKED(fs->first_object);
	MPASS(REFCOUNT_COUNT(fs->first_object->paging_in_progress) > 0);

	if (!vm_map_trylock_read(fs->map)) {
		VM_OBJECT_WUNLOCK(fs->first_object);
		vm_map_lock_read(fs->map);
		VM_OBJECT_WLOCK(fs->first_object);
	}
	fs->lookup_still_valid = true;
}