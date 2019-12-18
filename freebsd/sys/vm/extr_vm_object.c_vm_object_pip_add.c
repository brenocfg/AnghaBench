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
struct TYPE_3__ {int /*<<< orphan*/  paging_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_acquiren (int /*<<< orphan*/ *,short) ; 

void
vm_object_pip_add(vm_object_t object, short i)
{

	refcount_acquiren(&object->paging_in_progress, i);
}