#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
struct xen_remove_from_physmap {scalar_t__ gpfn; int /*<<< orphan*/  domid; } ;
struct privcmd_map {int mapped; scalar_t__ size; int /*<<< orphan*/  pseudo_phys_res; int /*<<< orphan*/  pseudo_phys_res_id; struct privcmd_map* err; int /*<<< orphan*/  phys_base_addr; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_remove_from_physmap*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_PRIVCMD ; 
 int /*<<< orphan*/  VM_ALLOC_WAITFAIL ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XENMEM_remove_from_physmap ; 
 scalar_t__ atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_pager_free_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct privcmd_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  privcmd_dev ; 
 scalar_t__ vm_page_busy_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_page_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 int xenmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
privcmd_pg_dtor(void *handle)
{
	struct xen_remove_from_physmap rm = { .domid = DOMID_SELF };
	struct privcmd_map *map = handle;
	int error;
	vm_size_t i;
	vm_page_t m;

	/*
	 * Remove the mappings from the used pages. This will remove the
	 * underlying p2m bindings in Xen second stage translation.
	 */
	if (map->mapped == true) {
		VM_OBJECT_WLOCK(map->mem);
retry:
		for (i = 0; i < map->size; i++) {
			m = vm_page_lookup(map->mem, i);
			if (m == NULL)
				continue;
			if (vm_page_busy_acquire(m, VM_ALLOC_WAITFAIL) == 0)
				goto retry;
			cdev_pager_free_page(map->mem, m);
		}
		VM_OBJECT_WUNLOCK(map->mem);

		for (i = 0; i < map->size; i++) {
			rm.gpfn = atop(map->phys_base_addr) + i;
			HYPERVISOR_memory_op(XENMEM_remove_from_physmap, &rm);
		}
		free(map->err, M_PRIVCMD);
	}

	error = xenmem_free(privcmd_dev, map->pseudo_phys_res_id,
	    map->pseudo_phys_res);
	KASSERT(error == 0, ("Unable to release memory resource: %d", error));

	free(map, M_PRIVCMD);
}