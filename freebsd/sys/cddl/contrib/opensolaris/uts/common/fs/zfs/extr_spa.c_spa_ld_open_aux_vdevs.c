#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_14__ {void* sav_sync; int /*<<< orphan*/  sav_config; int /*<<< orphan*/  sav_object; } ;
struct TYPE_13__ {void* sav_sync; int /*<<< orphan*/  sav_config; int /*<<< orphan*/  sav_object; } ;
struct TYPE_15__ {TYPE_2__ spa_l2cache; TYPE_1__ spa_spares; int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
typedef  scalar_t__ spa_import_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  DMU_POOL_L2CACHE ; 
 int /*<<< orphan*/  DMU_POOL_SPARES ; 
 int /*<<< orphan*/  EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 scalar_t__ SPA_IMPORT_ASSEMBLE ; 
 scalar_t__ SPA_VERSION_L2CACHE ; 
 scalar_t__ SPA_VERSION_SPARES ; 
 int /*<<< orphan*/  VDEV_AUX_CORRUPT_DATA ; 
 scalar_t__ load_nvlist (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_dir_prop (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  spa_load_l2cache (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_load_spares (TYPE_3__*) ; 
 int spa_vdev_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (TYPE_3__*) ; 

__attribute__((used)) static int
spa_ld_open_aux_vdevs(spa_t *spa, spa_import_type_t type)
{
	int error = 0;
	vdev_t *rvd = spa->spa_root_vdev;

	/*
	 * If we're assembling the pool from the split-off vdevs of
	 * an existing pool, we don't want to attach the spares & cache
	 * devices.
	 */

	/*
	 * Load any hot spares for this pool.
	 */
	error = spa_dir_prop(spa, DMU_POOL_SPARES, &spa->spa_spares.sav_object,
	    B_FALSE);
	if (error != 0 && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
	if (error == 0 && type != SPA_IMPORT_ASSEMBLE) {
		ASSERT(spa_version(spa) >= SPA_VERSION_SPARES);
		if (load_nvlist(spa, spa->spa_spares.sav_object,
		    &spa->spa_spares.sav_config) != 0) {
			spa_load_failed(spa, "error loading spares nvlist");
			return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
		}

		spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
		spa_load_spares(spa);
		spa_config_exit(spa, SCL_ALL, FTAG);
	} else if (error == 0) {
		spa->spa_spares.sav_sync = B_TRUE;
	}

	/*
	 * Load any level 2 ARC devices for this pool.
	 */
	error = spa_dir_prop(spa, DMU_POOL_L2CACHE,
	    &spa->spa_l2cache.sav_object, B_FALSE);
	if (error != 0 && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
	if (error == 0 && type != SPA_IMPORT_ASSEMBLE) {
		ASSERT(spa_version(spa) >= SPA_VERSION_L2CACHE);
		if (load_nvlist(spa, spa->spa_l2cache.sav_object,
		    &spa->spa_l2cache.sav_config) != 0) {
			spa_load_failed(spa, "error loading l2cache nvlist");
			return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
		}

		spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
		spa_load_l2cache(spa);
		spa_config_exit(spa, SCL_ALL, FTAG);
	} else if (error == 0) {
		spa->spa_l2cache.sav_sync = B_TRUE;
	}

	return (0);
}