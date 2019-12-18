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
struct TYPE_6__ {int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PAGE_BITS_ALL ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_bits_set (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_xbusied (TYPE_1__*) ; 

void
vm_page_valid(vm_page_t m)
{

	vm_page_assert_busied(m);
	if (vm_page_xbusied(m))
		m->valid = VM_PAGE_BITS_ALL;
	else
		vm_page_bits_set(m, &m->valid, VM_PAGE_BITS_ALL);
}