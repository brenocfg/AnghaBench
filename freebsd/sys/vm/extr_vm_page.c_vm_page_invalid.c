#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_7__ {scalar_t__ valid; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_BITS_ALL ; 
 int /*<<< orphan*/  pmap_page_is_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_bits_clear (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_xbusied (TYPE_1__*) ; 

void
vm_page_invalid(vm_page_t m)
{

	vm_page_assert_busied(m);
	VM_OBJECT_ASSERT_LOCKED(m->object);
	MPASS(!pmap_page_is_mapped(m));

	if (vm_page_xbusied(m))
		m->valid = 0;
	else
		vm_page_bits_clear(m, &m->valid, VM_PAGE_BITS_ALL);
}