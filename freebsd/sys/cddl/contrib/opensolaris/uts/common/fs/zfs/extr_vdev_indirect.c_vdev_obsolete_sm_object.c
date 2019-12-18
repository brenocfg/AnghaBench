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
struct TYPE_4__ {scalar_t__ vdev_top_zap; TYPE_3__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  sm_obj ;
struct TYPE_5__ {int /*<<< orphan*/  spa_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  VDEV_TOP_ZAP_INDIRECT_OBSOLETE_SM ; 
 int /*<<< orphan*/  spa_config_held (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zap_lookup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int*) ; 

int
vdev_obsolete_sm_object(vdev_t *vd)
{
	ASSERT0(spa_config_held(vd->vdev_spa, SCL_ALL, RW_WRITER));
	if (vd->vdev_top_zap == 0) {
		return (0);
	}

	uint64_t sm_obj = 0;
	int err = zap_lookup(vd->vdev_spa->spa_meta_objset, vd->vdev_top_zap,
	    VDEV_TOP_ZAP_INDIRECT_OBSOLETE_SM, sizeof (sm_obj), 1, &sm_obj);

	ASSERT(err == 0 || err == ENOENT);

	return (sm_obj);
}