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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct privcmd_map {int /*<<< orphan*/ * mem; int /*<<< orphan*/ * pseudo_phys_res; scalar_t__ pseudo_phys_res_id; int /*<<< orphan*/  phys_base_addr; int /*<<< orphan*/  size; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_PRIVCMD ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OBJT_MGTDEVICE ; 
 int /*<<< orphan*/  OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cdev_pager_allocate (struct privcmd_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct privcmd_map*,int /*<<< orphan*/ ) ; 
 struct privcmd_map* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  privcmd_dev ; 
 int /*<<< orphan*/  privcmd_pg_ops ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xenmem_alloc (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenmem_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
privcmd_mmap_single(struct cdev *cdev, vm_ooffset_t *offset, vm_size_t size,
    vm_object_t *object, int nprot)
{
	struct privcmd_map *map;

	map = malloc(sizeof(*map), M_PRIVCMD, M_WAITOK | M_ZERO);

	map->size = OFF_TO_IDX(size);
	map->pseudo_phys_res_id = 0;

	map->pseudo_phys_res = xenmem_alloc(privcmd_dev,
	    &map->pseudo_phys_res_id, size);
	if (map->pseudo_phys_res == NULL) {
		free(map, M_PRIVCMD);
		return (ENOMEM);
	}

	map->phys_base_addr = rman_get_start(map->pseudo_phys_res);
	map->mem = cdev_pager_allocate(map, OBJT_MGTDEVICE, &privcmd_pg_ops,
	    size, nprot, *offset, NULL);
	if (map->mem == NULL) {
		xenmem_free(privcmd_dev, map->pseudo_phys_res_id,
		    map->pseudo_phys_res);
		free(map, M_PRIVCMD);
		return (ENOMEM);
	}

	*object = map->mem;

	return (0);
}