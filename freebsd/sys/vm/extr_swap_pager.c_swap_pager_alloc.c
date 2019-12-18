#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  TYPE_1__* vm_object_t ;
struct ucred {int dummy; } ;
struct TYPE_6__ {void* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOBJLIST (void*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pager_object_list ; 
 int /*<<< orphan*/  sw_alloc_sx ; 
 TYPE_1__* swap_pager_alloc_init (void*,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* vm_pager_object_lookup (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static vm_object_t
swap_pager_alloc(void *handle, vm_ooffset_t size, vm_prot_t prot,
    vm_ooffset_t offset, struct ucred *cred)
{
	vm_object_t object;

	if (handle != NULL) {
		/*
		 * Reference existing named region or allocate new one.  There
		 * should not be a race here against swp_pager_meta_build()
		 * as called from vm_page_remove() in regards to the lookup
		 * of the handle.
		 */
		sx_xlock(&sw_alloc_sx);
		object = vm_pager_object_lookup(NOBJLIST(handle), handle);
		if (object == NULL) {
			object = swap_pager_alloc_init(handle, cred, size,
			    offset);
			if (object != NULL) {
				TAILQ_INSERT_TAIL(NOBJLIST(object->handle),
				    object, pager_object_list);
			}
		}
		sx_xunlock(&sw_alloc_sx);
	} else {
		object = swap_pager_alloc_init(handle, cred, size, offset);
	}
	return (object);
}