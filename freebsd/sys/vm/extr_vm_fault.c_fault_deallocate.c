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
struct faultstate {scalar_t__ object; scalar_t__ first_object; int /*<<< orphan*/ * first_m; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_WLOCK (scalar_t__) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  unlock_map (struct faultstate*) ; 
 int /*<<< orphan*/  unlock_vp (struct faultstate*) ; 
 int /*<<< orphan*/  vm_object_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_pip_wakeup (scalar_t__) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fault_deallocate(struct faultstate *fs)
{

	vm_object_pip_wakeup(fs->object);
	if (fs->object != fs->first_object) {
		VM_OBJECT_WLOCK(fs->first_object);
		vm_page_free(fs->first_m);
		vm_object_pip_wakeup(fs->first_object);
		VM_OBJECT_WUNLOCK(fs->first_object);
		fs->first_m = NULL;
	}
	vm_object_deallocate(fs->first_object);
	unlock_map(fs);
	unlock_vp(fs);
}