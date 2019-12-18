#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  flags; scalar_t__ shadow_count; scalar_t__ resident_page_count; int /*<<< orphan*/  busy; int /*<<< orphan*/  paging_in_progress; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  rtree; int /*<<< orphan*/  type; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJT_DEAD ; 
 int /*<<< orphan*/  OBJ_DEAD ; 
 int RW_DUPOK ; 
 int RW_NEW ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_list ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_init_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vm_object_list ; 
 int /*<<< orphan*/  vm_object_list_mtx ; 
 int /*<<< orphan*/  vm_radix_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vm_object_zinit(void *mem, int size, int flags)
{
	vm_object_t object;

	object = (vm_object_t)mem;
	rw_init_flags(&object->lock, "vm object", RW_DUPOK | RW_NEW);

	/* These are true for any object that has been freed */
	object->type = OBJT_DEAD;
	vm_radix_init(&object->rtree);
	refcount_init(&object->ref_count, 0);
	refcount_init(&object->paging_in_progress, 0);
	refcount_init(&object->busy, 0);
	object->resident_page_count = 0;
	object->shadow_count = 0;
	object->flags = OBJ_DEAD;

	mtx_lock(&vm_object_list_mtx);
	TAILQ_INSERT_TAIL(&vm_object_list, object, object_list);
	mtx_unlock(&vm_object_list_mtx);
	return (0);
}