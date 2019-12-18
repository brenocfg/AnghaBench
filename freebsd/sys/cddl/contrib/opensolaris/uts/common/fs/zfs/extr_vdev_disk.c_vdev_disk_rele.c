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
struct TYPE_4__ {int /*<<< orphan*/ * vdev_devid_vp; TYPE_3__* vdev_spa; int /*<<< orphan*/ * vdev_name_vp; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_5__ {int /*<<< orphan*/  spa_dsl_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 int /*<<< orphan*/  VN_RELE_ASYNC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_vnrele_taskq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_held (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_disk_rele(vdev_t *vd)
{
	ASSERT(spa_config_held(vd->vdev_spa, SCL_STATE, RW_WRITER));

	if (vd->vdev_name_vp) {
		VN_RELE_ASYNC(vd->vdev_name_vp,
		    dsl_pool_vnrele_taskq(vd->vdev_spa->spa_dsl_pool));
		vd->vdev_name_vp = NULL;
	}
	if (vd->vdev_devid_vp) {
		VN_RELE_ASYNC(vd->vdev_devid_vp,
		    dsl_pool_vnrele_taskq(vd->vdev_spa->spa_dsl_pool));
		vd->vdev_devid_vp = NULL;
	}
}