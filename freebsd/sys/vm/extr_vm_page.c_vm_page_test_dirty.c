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
typedef  TYPE_1__* vm_page_t ;
struct TYPE_6__ {scalar_t__ dirty; } ;

/* Variables and functions */
 scalar_t__ VM_PAGE_BITS_ALL ; 
 scalar_t__ pmap_is_modified (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_1__*) ; 

void
vm_page_test_dirty(vm_page_t m)
{

	vm_page_assert_busied(m);
	if (m->dirty != VM_PAGE_BITS_ALL && pmap_is_modified(m))
		vm_page_dirty(m);
}