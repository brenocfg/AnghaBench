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
struct TYPE_4__ {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_object_pip_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_sunbusy (TYPE_1__*) ; 

__attribute__((used)) static void
page_unbusy(vm_page_t pp)
{

	vm_page_sunbusy(pp);
	vm_object_pip_wakeup(pp->object);
}