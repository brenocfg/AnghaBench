#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  scalar_t__ vm_page_bits_t ;
typedef  TYPE_4__* vm_object_t ;
struct TYPE_13__ {scalar_t__ vnp_size; } ;
struct TYPE_14__ {TYPE_1__ vnp; } ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ ref_count; TYPE_2__ un_pager; } ;
struct TYPE_15__ {scalar_t__ valid; scalar_t__ dirty; int /*<<< orphan*/  pindex; TYPE_4__* object; } ;

/* Variables and functions */
 scalar_t__ IDX_TO_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OBJT_VNODE ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_4__*) ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 int /*<<< orphan*/  pmap_page_is_mapped (TYPE_3__*) ; 
 int /*<<< orphan*/  pmap_remove_all (TYPE_3__*) ; 
 scalar_t__ vm_page_all_valid (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_3__*) ; 
 scalar_t__ vm_page_bits (int,int) ; 
 int /*<<< orphan*/  vm_page_bits_clear (TYPE_3__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ vm_page_xbusied (TYPE_3__*) ; 

void
vm_page_set_invalid(vm_page_t m, int base, int size)
{
	vm_page_bits_t bits;
	vm_object_t object;

	/*
	 * The object lock is required so that pages can't be mapped
	 * read-only while we're in the process of invalidating them.
	 */
	object = m->object;
	VM_OBJECT_ASSERT_WLOCKED(object);
	vm_page_assert_busied(m);

	if (object->type == OBJT_VNODE && base == 0 && IDX_TO_OFF(m->pindex) +
	    size >= object->un_pager.vnp.vnp_size)
		bits = VM_PAGE_BITS_ALL;
	else
		bits = vm_page_bits(base, size);
	if (object->ref_count != 0 && vm_page_all_valid(m) && bits != 0)
		pmap_remove_all(m);
	KASSERT((bits == 0 && vm_page_all_valid(m)) ||
	    !pmap_page_is_mapped(m),
	    ("vm_page_set_invalid: page %p is mapped", m));
	if (vm_page_xbusied(m)) {
		m->valid &= ~bits;
		m->dirty &= ~bits;
	} else {
		vm_page_bits_clear(m, &m->valid, bits);
		vm_page_bits_clear(m, &m->dirty, bits);
	}
}