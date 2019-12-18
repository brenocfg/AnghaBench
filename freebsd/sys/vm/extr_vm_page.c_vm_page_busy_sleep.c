#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _vm_page_busy_sleep (int /*<<< orphan*/ ,TYPE_1__*,char const*,int,int) ; 
 int /*<<< orphan*/  vm_page_lock_assert (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
vm_page_busy_sleep(vm_page_t m, const char *wmesg, bool nonshared)
{
	vm_object_t obj;

	obj = m->object;
	VM_OBJECT_ASSERT_LOCKED(obj);
	vm_page_lock_assert(m, MA_NOTOWNED);

	_vm_page_busy_sleep(obj, m, wmesg, nonshared, true);
}