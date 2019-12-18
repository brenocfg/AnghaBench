#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct netmap_vm_handle_t {struct netmap_priv_d* priv; } ;
struct netmap_priv_d {struct netmap_adapter* np_na; } ;
struct netmap_adapter {int /*<<< orphan*/  nm_mem; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_16__ {int /*<<< orphan*/  memattr; struct netmap_vm_handle_t* handle; } ;
struct TYPE_15__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFF_TO_IDX (scalar_t__) ; 
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 int VM_PAGER_FAIL ; 
 int VM_PAGER_OK ; 
 scalar_t__ netmap_mem_ofstophys (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nm_prdis (char*,TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 TYPE_1__* vm_page_getfake (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_insert (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_updatefake (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_valid (TYPE_1__*) ; 

__attribute__((used)) static int
netmap_dev_pager_fault(vm_object_t object, vm_ooffset_t offset,
	int prot, vm_page_t *mres)
{
	struct netmap_vm_handle_t *vmh = object->handle;
	struct netmap_priv_d *priv = vmh->priv;
	struct netmap_adapter *na = priv->np_na;
	vm_paddr_t paddr;
	vm_page_t page;
	vm_memattr_t memattr;
	vm_pindex_t pidx;

	nm_prdis("object %p offset %jd prot %d mres %p",
			object, (intmax_t)offset, prot, mres);
	memattr = object->memattr;
	pidx = OFF_TO_IDX(offset);
	paddr = netmap_mem_ofstophys(na->nm_mem, offset);
	if (paddr == 0)
		return VM_PAGER_FAIL;

	if (((*mres)->flags & PG_FICTITIOUS) != 0) {
		/*
		 * If the passed in result page is a fake page, update it with
		 * the new physical address.
		 */
		page = *mres;
		vm_page_updatefake(page, paddr, memattr);
	} else {
		/*
		 * Replace the passed in reqpage page with our own fake page and
		 * free up the all of the original pages.
		 */
#ifndef VM_OBJECT_WUNLOCK	/* FreeBSD < 10.x */
#define VM_OBJECT_WUNLOCK VM_OBJECT_UNLOCK
#define VM_OBJECT_WLOCK	VM_OBJECT_LOCK
#endif /* VM_OBJECT_WUNLOCK */

		VM_OBJECT_WUNLOCK(object);
		page = vm_page_getfake(paddr, memattr);
		VM_OBJECT_WLOCK(object);
		vm_page_free(*mres);
		*mres = page;
		vm_page_insert(page, object, pidx);
	}
	vm_page_valid(page);
	return (VM_PAGER_OK);
}