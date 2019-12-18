#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  size_t uint32_t ;
struct vm_object {int dummy; } ;
struct per_user_data {int dummy; } ;
struct gntdev_gmap {size_t count; TYPE_1__* map; TYPE_3__* grant_map_ops; } ;
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  flags; scalar_t__ host_addr; } ;
struct TYPE_4__ {struct vm_object* mem; scalar_t__ phys_base_addr; int /*<<< orphan*/ * pseudo_phys_res; scalar_t__ pseudo_phys_res_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GNTMAP_readonly ; 
 scalar_t__ GNTST_bad_page ; 
 scalar_t__ GNTST_eagain ; 
 scalar_t__ GNTST_okay ; 
 int /*<<< orphan*/  GNTTABOP_map_grant_ref ; 
 int HYPERVISOR_grant_table_op (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  M_GNTDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OBJT_MGTDEVICE ; 
 size_t PAGE_SIZE ; 
 int PROT_WRITE ; 
 int SBT_1MS ; 
 struct vm_object* cdev_pager_allocate (struct gntdev_gmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gntdev_dev ; 
 int /*<<< orphan*/  gntdev_gmap_pg_ops ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_deallocate (struct vm_object*) ; 
 int /*<<< orphan*/  vm_object_reference (struct vm_object*) ; 
 int /*<<< orphan*/ * xenmem_alloc (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenmem_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mmap_gmap(struct per_user_data *priv_user, struct gntdev_gmap *gmap_start,
    vm_ooffset_t *offset, vm_size_t size, struct vm_object **object, int nprot)
{
	uint32_t i;
	int error;

	/*
	 * The grant map hypercall might already be done.
	 * If that is the case, increase a reference to the
	 * vm object and return the already allocated object.
	 */
	if (gmap_start->map) {
		vm_object_reference(gmap_start->map->mem);
		*object = gmap_start->map->mem;
		return (0);
	}

	gmap_start->map = malloc(sizeof(*(gmap_start->map)), M_GNTDEV,
	    M_WAITOK | M_ZERO);

	/* Allocate the xen pseudo physical memory resource. */
	gmap_start->map->pseudo_phys_res_id = 0;
	gmap_start->map->pseudo_phys_res = xenmem_alloc(gntdev_dev,
	    &gmap_start->map->pseudo_phys_res_id, size);
	if (gmap_start->map->pseudo_phys_res == NULL) {
		free(gmap_start->map, M_GNTDEV);
		gmap_start->map = NULL;
		return (ENOMEM);
	}
	gmap_start->map->phys_base_addr =
	    rman_get_start(gmap_start->map->pseudo_phys_res);

	/* Allocate the mgtdevice pager. */
	gmap_start->map->mem = cdev_pager_allocate(gmap_start, OBJT_MGTDEVICE,
	    &gntdev_gmap_pg_ops, size, nprot, *offset, NULL);
	if (gmap_start->map->mem == NULL) {
		xenmem_free(gntdev_dev, gmap_start->map->pseudo_phys_res_id,
		    gmap_start->map->pseudo_phys_res);
		free(gmap_start->map, M_GNTDEV);
		gmap_start->map = NULL;
		return (ENOMEM);
	}

	for (i = 0; i < gmap_start->count; i++) {
		gmap_start->grant_map_ops[i].host_addr =
		    gmap_start->map->phys_base_addr + i * PAGE_SIZE;

		if ((nprot & PROT_WRITE) == 0)
			gmap_start->grant_map_ops[i].flags |= GNTMAP_readonly;
	}
	/* Make the MAP hypercall. */
	error = HYPERVISOR_grant_table_op(GNTTABOP_map_grant_ref,
	    gmap_start->grant_map_ops, gmap_start->count);
	if (error != 0) {
		/*
		 * Deallocate pager.
		 * Pager deallocation will automatically take care of
		 * xenmem deallocation, etc.
		 */
		vm_object_deallocate(gmap_start->map->mem);

		return (EINVAL);
	}

	/* Retry EAGAIN maps. */
	for (i = 0; i < gmap_start->count; i++) {
		int delay = 1;
		while (delay < 256 &&
		    gmap_start->grant_map_ops[i].status == GNTST_eagain) {
			HYPERVISOR_grant_table_op( GNTTABOP_map_grant_ref,
			    &gmap_start->grant_map_ops[i], 1);
			pause(("gntmap"), delay * SBT_1MS);
			delay++;
		}
		if (gmap_start->grant_map_ops[i].status == GNTST_eagain)
			gmap_start->grant_map_ops[i].status = GNTST_bad_page;

		if (gmap_start->grant_map_ops[i].status != GNTST_okay) {
			/*
			 * Deallocate pager.
			 * Pager deallocation will automatically take care of
			 * xenmem deallocation, notification, unmap hypercall,
			 * etc.
			 */
			vm_object_deallocate(gmap_start->map->mem);

			return (EINVAL);
		}
	}

	/*
	 * Add a reference to the vm object. We do not want
	 * the vm object to be deleted when all the mmaps are
	 * unmapped, because it may be re-mmapped. Instead,
	 * we want the object to be deleted, when along with
	 * munmaps, we have also processed the unmap-ioctl.
	 */
	vm_object_reference(gmap_start->map->mem);

	*object = gmap_start->map->mem;

	return (0);
}