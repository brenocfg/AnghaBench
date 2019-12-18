#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  int vm_offset_t ;
typedef  TYPE_1__* vm_object_t ;
typedef  TYPE_2__* vm_map_t ;
struct TYPE_17__ {int flags; int anon_loc; } ;
struct TYPE_16__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_INVALID_ADDRESS ; 
 int KERN_NO_SPACE ; 
 int KERN_SUCCESS ; 
 scalar_t__ MAP_32BIT_MAX_ADDR ; 
 int MAP_ASLR ; 
 int MAP_ASLR_IGNSTART ; 
 int MAP_INHERIT_SHARE ; 
 int MAP_IS_SUB_MAP ; 
 int MAP_REMAP ; 
 int MAP_STACK_GROWS_DOWN ; 
 int MAP_STACK_GROWS_UP ; 
 int MAXPAGESIZES ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int OBJ_COLORED ; 
 int /*<<< orphan*/  PROT_NONE ; 
 int VMFS_ANY_SPACE ; 
 int VMFS_NO_SPACE ; 
 int VMFS_OPTIMAL_SPACE ; 
 int VMFS_SUPER_SPACE ; 
 int arc4random () ; 
 int* aslr_pages_rnd_32 ; 
 int* aslr_pages_rnd_64 ; 
 int /*<<< orphan*/  aslr_restarts ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 scalar_t__ clustering_anon_allowed (int) ; 
 int* pagesizes ; 
 int /*<<< orphan*/  sgrowsiz ; 
 int vm_map_alignspace (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int*,int,int,int) ; 
 int /*<<< orphan*/  vm_map_delete (TYPE_2__*,int,int) ; 
 int vm_map_findspace (TYPE_2__*,int,int) ; 
 int vm_map_insert (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_2__*) ; 
 int vm_map_max (TYPE_2__*) ; 
 int vm_map_min (TYPE_2__*) ; 
 int vm_map_stack_locked (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_2__*) ; 

int
vm_map_find(vm_map_t map, vm_object_t object, vm_ooffset_t offset,
	    vm_offset_t *addr,	/* IN/OUT */
	    vm_size_t length, vm_offset_t max_addr, int find_space,
	    vm_prot_t prot, vm_prot_t max, int cow)
{
	vm_offset_t alignment, curr_min_addr, min_addr;
	int gap, pidx, rv, try;
	bool cluster, en_aslr, update_anon;

	KASSERT((cow & (MAP_STACK_GROWS_DOWN | MAP_STACK_GROWS_UP)) == 0 ||
	    object == NULL,
	    ("vm_map_find: non-NULL backing object for stack"));
	MPASS((cow & MAP_REMAP) == 0 || (find_space == VMFS_NO_SPACE &&
	    (cow & (MAP_STACK_GROWS_DOWN | MAP_STACK_GROWS_UP)) == 0));
	if (find_space == VMFS_OPTIMAL_SPACE && (object == NULL ||
	    (object->flags & OBJ_COLORED) == 0))
		find_space = VMFS_ANY_SPACE;
	if (find_space >> 8 != 0) {
		KASSERT((find_space & 0xff) == 0, ("bad VMFS flags"));
		alignment = (vm_offset_t)1 << (find_space >> 8);
	} else
		alignment = 0;
	en_aslr = (map->flags & MAP_ASLR) != 0;
	update_anon = cluster = clustering_anon_allowed(*addr) &&
	    (map->flags & MAP_IS_SUB_MAP) == 0 && max_addr == 0 &&
	    find_space != VMFS_NO_SPACE && object == NULL &&
	    (cow & (MAP_INHERIT_SHARE | MAP_STACK_GROWS_UP |
	    MAP_STACK_GROWS_DOWN)) == 0 && prot != PROT_NONE;
	curr_min_addr = min_addr = *addr;
	if (en_aslr && min_addr == 0 && !cluster &&
	    find_space != VMFS_NO_SPACE &&
	    (map->flags & MAP_ASLR_IGNSTART) != 0)
		curr_min_addr = min_addr = vm_map_min(map);
	try = 0;
	vm_map_lock(map);
	if (cluster) {
		curr_min_addr = map->anon_loc;
		if (curr_min_addr == 0)
			cluster = false;
	}
	if (find_space != VMFS_NO_SPACE) {
		KASSERT(find_space == VMFS_ANY_SPACE ||
		    find_space == VMFS_OPTIMAL_SPACE ||
		    find_space == VMFS_SUPER_SPACE ||
		    alignment != 0, ("unexpected VMFS flag"));
again:
		/*
		 * When creating an anonymous mapping, try clustering
		 * with an existing anonymous mapping first.
		 *
		 * We make up to two attempts to find address space
		 * for a given find_space value. The first attempt may
		 * apply randomization or may cluster with an existing
		 * anonymous mapping. If this first attempt fails,
		 * perform a first-fit search of the available address
		 * space.
		 *
		 * If all tries failed, and find_space is
		 * VMFS_OPTIMAL_SPACE, fallback to VMFS_ANY_SPACE.
		 * Again enable clustering and randomization.
		 */
		try++;
		MPASS(try <= 2);

		if (try == 2) {
			/*
			 * Second try: we failed either to find a
			 * suitable region for randomizing the
			 * allocation, or to cluster with an existing
			 * mapping.  Retry with free run.
			 */
			curr_min_addr = (map->flags & MAP_ASLR_IGNSTART) != 0 ?
			    vm_map_min(map) : min_addr;
			atomic_add_long(&aslr_restarts, 1);
		}

		if (try == 1 && en_aslr && !cluster) {
			/*
			 * Find space for allocation, including
			 * gap needed for later randomization.
			 */
			pidx = MAXPAGESIZES > 1 && pagesizes[1] != 0 &&
			    (find_space == VMFS_SUPER_SPACE || find_space ==
			    VMFS_OPTIMAL_SPACE) ? 1 : 0;
			gap = vm_map_max(map) > MAP_32BIT_MAX_ADDR &&
			    (max_addr == 0 || max_addr > MAP_32BIT_MAX_ADDR) ?
			    aslr_pages_rnd_64[pidx] : aslr_pages_rnd_32[pidx];
			*addr = vm_map_findspace(map, curr_min_addr,
			    length + gap * pagesizes[pidx]);
			if (*addr + length + gap * pagesizes[pidx] >
			    vm_map_max(map))
				goto again;
			/* And randomize the start address. */
			*addr += (arc4random() % gap) * pagesizes[pidx];
			if (max_addr != 0 && *addr + length > max_addr)
				goto again;
		} else {
			*addr = vm_map_findspace(map, curr_min_addr, length);
			if (*addr + length > vm_map_max(map) ||
			    (max_addr != 0 && *addr + length > max_addr)) {
				if (cluster) {
					cluster = false;
					MPASS(try == 1);
					goto again;
				}
				rv = KERN_NO_SPACE;
				goto done;
			}
		}

		if (find_space != VMFS_ANY_SPACE &&
		    (rv = vm_map_alignspace(map, object, offset, addr, length,
		    max_addr, alignment)) != KERN_SUCCESS) {
			if (find_space == VMFS_OPTIMAL_SPACE) {
				find_space = VMFS_ANY_SPACE;
				curr_min_addr = min_addr;
				cluster = update_anon;
				try = 0;
				goto again;
			}
			goto done;
		}
	} else if ((cow & MAP_REMAP) != 0) {
		if (*addr < vm_map_min(map) ||
		    *addr + length > vm_map_max(map) ||
		    *addr + length <= length) {
			rv = KERN_INVALID_ADDRESS;
			goto done;
		}
		vm_map_delete(map, *addr, *addr + length);
	}
	if ((cow & (MAP_STACK_GROWS_DOWN | MAP_STACK_GROWS_UP)) != 0) {
		rv = vm_map_stack_locked(map, *addr, length, sgrowsiz, prot,
		    max, cow);
	} else {
		rv = vm_map_insert(map, object, offset, *addr, *addr + length,
		    prot, max, cow);
	}
	if (rv == KERN_SUCCESS && update_anon)
		map->anon_loc = *addr + length;
done:
	vm_map_unlock(map);
	return (rv);
}