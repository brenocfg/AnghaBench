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
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_5__ {TYPE_1__* dn_phys; int /*<<< orphan*/  dn_objset; } ;
typedef  TYPE_2__ dnode_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_4__ {scalar_t__ dn_nlevels; int dn_nblkptr; int /*<<< orphan*/ * dn_blkptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 int /*<<< orphan*/  SPA_FEATURE_DEVICE_REMOVAL ; 
 int /*<<< orphan*/ * dmu_objset_spa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_remap_blkptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

boolean_t
dnode_needs_remap(const dnode_t *dn)
{
	spa_t *spa = dmu_objset_spa(dn->dn_objset);
	boolean_t ret = B_FALSE;

	if (dn->dn_phys->dn_nlevels == 0) {
		return (B_FALSE);
	}

	ASSERT(spa_feature_is_active(spa, SPA_FEATURE_DEVICE_REMOVAL));

	spa_config_enter(spa, SCL_VDEV, FTAG, RW_READER);
	for (int j = 0; j < dn->dn_phys->dn_nblkptr; j++) {
		blkptr_t bp_copy = dn->dn_phys->dn_blkptr[j];
		if (spa_remap_blkptr(spa, &bp_copy, NULL, NULL)) {
			ret = B_TRUE;
			break;
		}
	}
	spa_config_exit(spa, SCL_VDEV, FTAG);

	return (ret);
}