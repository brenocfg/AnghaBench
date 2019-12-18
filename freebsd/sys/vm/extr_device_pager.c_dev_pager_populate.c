#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_4__* vm_object_t ;
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_10__ {TYPE_2__ devp; } ;
struct TYPE_11__ {TYPE_3__ un_pager; } ;
struct TYPE_8__ {int (* cdev_pg_populate ) (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_4__*) ; 
 int VM_PAGER_FAIL ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dev_pager_populate(vm_object_t object, vm_pindex_t pidx, int fault_type,
    vm_prot_t max_prot, vm_pindex_t *first, vm_pindex_t *last)
{

	VM_OBJECT_ASSERT_WLOCKED(object);
	if (object->un_pager.devp.ops->cdev_pg_populate == NULL)
		return (VM_PAGER_FAIL);
	return (object->un_pager.devp.ops->cdev_pg_populate(object, pidx,
	    fault_type, max_prot, first, last));
}