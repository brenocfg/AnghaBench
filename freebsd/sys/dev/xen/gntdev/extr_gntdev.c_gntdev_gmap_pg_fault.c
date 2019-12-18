#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_pindex_t ;
typedef  TYPE_3__* vm_page_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  TYPE_4__* vm_object_t ;
struct gntdev_gmap {size_t count; TYPE_2__* map; TYPE_1__* grant_map_ops; scalar_t__ file_index; } ;
struct TYPE_18__ {struct gntdev_gmap* handle; } ;
struct TYPE_17__ {int flags; } ;
struct TYPE_16__ {scalar_t__ phys_base_addr; } ;
struct TYPE_15__ {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ GNTST_okay ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t OFF_TO_IDX (scalar_t__) ; 
 int PG_FICTITIOUS ; 
 TYPE_3__* PHYS_TO_VM_PAGE (scalar_t__) ; 
 int VM_PAGER_FAIL ; 
 int VM_PAGER_OK ; 
 int /*<<< orphan*/  vm_page_busied (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_busy_acquire (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_insert (TYPE_3__*,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  vm_page_valid (TYPE_3__*) ; 
 int vm_page_wired (TYPE_3__*) ; 

__attribute__((used)) static int
gntdev_gmap_pg_fault(vm_object_t object, vm_ooffset_t offset, int prot,
    vm_page_t *mres)
{
	struct gntdev_gmap *gmap = object->handle;
	vm_pindex_t pidx, ridx;
	vm_page_t page, oldm;
	vm_ooffset_t relative_offset;

	if (gmap->map == NULL)
		return (VM_PAGER_FAIL);

	relative_offset = offset - gmap->file_index;

	pidx = OFF_TO_IDX(offset);
	ridx = OFF_TO_IDX(relative_offset);
	if (ridx >= gmap->count ||
	    gmap->grant_map_ops[ridx].status != GNTST_okay)
		return (VM_PAGER_FAIL);

	page = PHYS_TO_VM_PAGE(gmap->map->phys_base_addr + relative_offset);
	if (page == NULL)
		return (VM_PAGER_FAIL);

	KASSERT((page->flags & PG_FICTITIOUS) != 0,
	    ("not fictitious %p", page));
	KASSERT(vm_page_wired(page), ("page %p is not wired", page));
	KASSERT(!vm_page_busied(page), ("page %p is busy", page));

	if (*mres != NULL) {
		oldm = *mres;
		vm_page_free(oldm);
		*mres = NULL;
	}

	vm_page_busy_acquire(page, 0);
	vm_page_valid(page);
	vm_page_insert(page, object, pidx);
	*mres = page;
	return (VM_PAGER_OK);
}