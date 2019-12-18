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
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct TYPE_4__ {int /*<<< orphan*/ * object; int /*<<< orphan*/  busy_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPB_SINGLE_EXCLUSIVER ; 
 int /*<<< orphan*/  VPB_UNBUSIED ; 
 scalar_t__ atomic_cmpset_acq_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_busied (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 

int
vm_page_tryxbusy(vm_page_t m)
{
	vm_object_t obj;

        if (atomic_cmpset_acq_int(&(m)->busy_lock, VPB_UNBUSIED,
            VPB_SINGLE_EXCLUSIVER) == 0)
		return (0);

	obj = m->object;
	if (obj != NULL && vm_object_busied(obj)) {
		vm_page_xunbusy(m);
		return (0);
	}
	return (1);
}