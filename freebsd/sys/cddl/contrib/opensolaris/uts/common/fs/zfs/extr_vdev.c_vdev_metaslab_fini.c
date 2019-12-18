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
struct TYPE_3__ {size_t vdev_ms_count; int /*<<< orphan*/ ** vdev_ms; int /*<<< orphan*/  vdev_mg; int /*<<< orphan*/ * vdev_checkpoint_sm; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (size_t) ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  metaslab_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_group_passivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  space_map_close (int /*<<< orphan*/ *) ; 

void
vdev_metaslab_fini(vdev_t *vd)
{
	if (vd->vdev_checkpoint_sm != NULL) {
		ASSERT(spa_feature_is_active(vd->vdev_spa,
		    SPA_FEATURE_POOL_CHECKPOINT));
		space_map_close(vd->vdev_checkpoint_sm);
		/*
		 * Even though we close the space map, we need to set its
		 * pointer to NULL. The reason is that vdev_metaslab_fini()
		 * may be called multiple times for certain operations
		 * (i.e. when destroying a pool) so we need to ensure that
		 * this clause never executes twice. This logic is similar
		 * to the one used for the vdev_ms clause below.
		 */
		vd->vdev_checkpoint_sm = NULL;
	}

	if (vd->vdev_ms != NULL) {
		uint64_t count = vd->vdev_ms_count;

		metaslab_group_passivate(vd->vdev_mg);
		for (uint64_t m = 0; m < count; m++) {
			metaslab_t *msp = vd->vdev_ms[m];

			if (msp != NULL)
				metaslab_fini(msp);
		}
		kmem_free(vd->vdev_ms, count * sizeof (metaslab_t *));
		vd->vdev_ms = NULL;

		vd->vdev_ms_count = 0;
	}
	ASSERT0(vd->vdev_ms_count);
}