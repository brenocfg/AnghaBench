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
struct TYPE_7__ {int vdev_asize; int vdev_ms_shift; int vdev_ms_count; int /*<<< orphan*/  vdev_spa; struct TYPE_7__* vdev_top; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_1__*) ; 
 int vdev_is_concrete (TYPE_1__*) ; 
 scalar_t__ vdev_metaslab_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_set_deflate_ratio (TYPE_1__*) ; 

void
vdev_expand(vdev_t *vd, uint64_t txg)
{
	ASSERT(vd->vdev_top == vd);
	ASSERT(spa_config_held(vd->vdev_spa, SCL_ALL, RW_WRITER) == SCL_ALL);
	ASSERT(vdev_is_concrete(vd));

	vdev_set_deflate_ratio(vd);

	if ((vd->vdev_asize >> vd->vdev_ms_shift) > vd->vdev_ms_count) {
		VERIFY(vdev_metaslab_init(vd, txg) == 0);
		vdev_config_dirty(vd);
	}
}