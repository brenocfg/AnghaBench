#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vdev_children; scalar_t__ vdev_ishole; struct TYPE_4__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint_t ;
typedef  size_t uint64_t ;
struct TYPE_5__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HOLE_ARRAY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_CHILDREN ; 
 size_t* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (size_t*,int) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ nvlist_add_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,size_t) ; 

void
vdev_top_config_generate(spa_t *spa, nvlist_t *config)
{
	vdev_t *rvd = spa->spa_root_vdev;
	uint64_t *array;
	uint_t c, idx;

	array = kmem_alloc(rvd->vdev_children * sizeof (uint64_t), KM_SLEEP);

	for (c = 0, idx = 0; c < rvd->vdev_children; c++) {
		vdev_t *tvd = rvd->vdev_child[c];

		if (tvd->vdev_ishole) {
			array[idx++] = c;
		}
	}

	if (idx) {
		VERIFY(nvlist_add_uint64_array(config, ZPOOL_CONFIG_HOLE_ARRAY,
		    array, idx) == 0);
	}

	VERIFY(nvlist_add_uint64(config, ZPOOL_CONFIG_VDEV_CHILDREN,
	    rvd->vdev_children) == 0);

	kmem_free(array, rvd->vdev_children * sizeof (uint64_t));
}