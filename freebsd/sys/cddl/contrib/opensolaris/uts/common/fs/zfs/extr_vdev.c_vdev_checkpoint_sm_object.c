#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ vdev_top_zap; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  VDEV_TOP_ZAP_POOL_CHECKPOINT_SM ; 
 int /*<<< orphan*/  spa_config_held (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_meta_objset (int /*<<< orphan*/ ) ; 
 int zap_lookup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int*) ; 

int
vdev_checkpoint_sm_object(vdev_t *vd)
{
	ASSERT0(spa_config_held(vd->vdev_spa, SCL_ALL, RW_WRITER));
	if (vd->vdev_top_zap == 0) {
		return (0);
	}

	uint64_t sm_obj = 0;
	int err = zap_lookup(spa_meta_objset(vd->vdev_spa), vd->vdev_top_zap,
	    VDEV_TOP_ZAP_POOL_CHECKPOINT_SM, sizeof (uint64_t), 1, &sm_obj);

	ASSERT(err == 0 || err == ENOENT);

	return (sm_obj);
}