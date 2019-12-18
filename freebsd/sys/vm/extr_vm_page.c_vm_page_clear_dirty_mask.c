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
typedef  int /*<<< orphan*/  vm_page_bits_t ;
struct TYPE_7__ {int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_page_is_write_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_bits_clear (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_xbusied (TYPE_1__*) ; 

__attribute__((used)) static __inline void
vm_page_clear_dirty_mask(vm_page_t m, vm_page_bits_t pagebits)
{

	vm_page_assert_busied(m);

	/*
	 * If the page is xbusied and not write mapped we are the
	 * only thread that can modify dirty bits.  Otherwise, The pmap
	 * layer can call vm_page_dirty() without holding a distinguished
	 * lock.  The combination of page busy and atomic operations
	 * suffice to guarantee consistency of the page dirty field.
	 */
	if (vm_page_xbusied(m) && !pmap_page_is_write_mapped(m))
		m->dirty &= ~pagebits;
	else
		vm_page_bits_clear(m, &m->dirty, pagebits);
}