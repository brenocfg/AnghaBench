#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_5__* vm_object_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  TYPE_6__* vm_map_entry_t ;
struct thread {TYPE_2__* td_proc; } ;
struct ioctl_gntdev_get_offset_for_vaddr {int count; int /*<<< orphan*/  offset; int /*<<< orphan*/  vaddr; } ;
struct gntdev_gmap {int count; int /*<<< orphan*/  file_index; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_15__ {int end; int start; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_13__ {TYPE_3__ devp; } ;
struct TYPE_14__ {scalar_t__ type; struct gntdev_gmap* handle; TYPE_4__ un_pager; } ;
struct TYPE_11__ {TYPE_1__* p_vmspace; } ;
struct TYPE_10__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int KERN_SUCCESS ; 
 scalar_t__ OBJT_MGTDEVICE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int /*<<< orphan*/  gntdev_gmap_pg_ops ; 
 int vm_map_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__**,TYPE_5__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_lookup_done (int /*<<< orphan*/ *,TYPE_6__*) ; 

__attribute__((used)) static int
gntdev_get_offset_for_vaddr(struct ioctl_gntdev_get_offset_for_vaddr *arg,
	struct thread *td)
{
	int error;
	vm_map_t map;
	vm_map_entry_t entry;
	vm_object_t mem;
	vm_pindex_t pindex;
	vm_prot_t prot;
	boolean_t wired;
	struct gntdev_gmap *gmap;
	int rc;

	map = &td->td_proc->p_vmspace->vm_map;
	error = vm_map_lookup(&map, arg->vaddr, VM_PROT_NONE, &entry,
		    &mem, &pindex, &prot, &wired);
	if (error != KERN_SUCCESS)
		return (EINVAL);

	if ((mem->type != OBJT_MGTDEVICE) ||
	    (mem->un_pager.devp.ops != &gntdev_gmap_pg_ops)) {
		rc = EINVAL;
		goto out;
	}

	gmap = mem->handle;
	if (gmap == NULL ||
	    (entry->end - entry->start) != (gmap->count * PAGE_SIZE)) {
		rc = EINVAL;
		goto out;
	}

	arg->count = gmap->count;
	arg->offset = gmap->file_index;
	rc = 0;

out:
	vm_map_lookup_done(map, entry);
	return (rc);
}