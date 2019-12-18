#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_13__ {scalar_t__ za_first_integer; } ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_12__ {scalar_t__ ub_version; } ;
struct TYPE_11__ {scalar_t__ ub_version; } ;
struct TYPE_14__ {scalar_t__ spa_avz_action; scalar_t__ spa_all_vdev_zaps; int /*<<< orphan*/  spa_config_object; int /*<<< orphan*/ * spa_config_syncing; TYPE_2__ spa_uberblock; TYPE_1__ spa_ubsync; int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_meta_objset; int /*<<< orphan*/  spa_config_dirty_list; } ;
typedef  TYPE_4__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  new_avz ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ AVZ_ACTION_DESTROY ; 
 scalar_t__ AVZ_ACTION_INITIALIZE ; 
 scalar_t__ AVZ_ACTION_NONE ; 
 scalar_t__ AVZ_ACTION_REBUILD ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DMU_OTN_ZAP_METADATA ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_VDEV_ZAP_MAP ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int /*<<< orphan*/  dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_avz_build (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spa_config_generate (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_sync_nvlist (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_construct_zaps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_create_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zap_destroy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_lookup_int (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_sync_config_object(spa_t *spa, dmu_tx_t *tx)
{
	nvlist_t *config;

	/*
	 * If the pool is being imported from a pre-per-vdev-ZAP version of ZFS,
	 * its config may not be dirty but we still need to build per-vdev ZAPs.
	 * Similarly, if the pool is being assembled (e.g. after a split), we
	 * need to rebuild the AVZ although the config may not be dirty.
	 */
	if (list_is_empty(&spa->spa_config_dirty_list) &&
	    spa->spa_avz_action == AVZ_ACTION_NONE)
		return;

	spa_config_enter(spa, SCL_STATE, FTAG, RW_READER);

	ASSERT(spa->spa_avz_action == AVZ_ACTION_NONE ||
	    spa->spa_avz_action == AVZ_ACTION_INITIALIZE ||
	    spa->spa_all_vdev_zaps != 0);

	if (spa->spa_avz_action == AVZ_ACTION_REBUILD) {
		/* Make and build the new AVZ */
		uint64_t new_avz = zap_create(spa->spa_meta_objset,
		    DMU_OTN_ZAP_METADATA, DMU_OT_NONE, 0, tx);
		spa_avz_build(spa->spa_root_vdev, new_avz, tx);

		/* Diff old AVZ with new one */
		zap_cursor_t zc;
		zap_attribute_t za;

		for (zap_cursor_init(&zc, spa->spa_meta_objset,
		    spa->spa_all_vdev_zaps);
		    zap_cursor_retrieve(&zc, &za) == 0;
		    zap_cursor_advance(&zc)) {
			uint64_t vdzap = za.za_first_integer;
			if (zap_lookup_int(spa->spa_meta_objset, new_avz,
			    vdzap) == ENOENT) {
				/*
				 * ZAP is listed in old AVZ but not in new one;
				 * destroy it
				 */
				VERIFY0(zap_destroy(spa->spa_meta_objset, vdzap,
				    tx));
			}
		}

		zap_cursor_fini(&zc);

		/* Destroy the old AVZ */
		VERIFY0(zap_destroy(spa->spa_meta_objset,
		    spa->spa_all_vdev_zaps, tx));

		/* Replace the old AVZ in the dir obj with the new one */
		VERIFY0(zap_update(spa->spa_meta_objset,
		    DMU_POOL_DIRECTORY_OBJECT, DMU_POOL_VDEV_ZAP_MAP,
		    sizeof (new_avz), 1, &new_avz, tx));

		spa->spa_all_vdev_zaps = new_avz;
	} else if (spa->spa_avz_action == AVZ_ACTION_DESTROY) {
		zap_cursor_t zc;
		zap_attribute_t za;

		/* Walk through the AVZ and destroy all listed ZAPs */
		for (zap_cursor_init(&zc, spa->spa_meta_objset,
		    spa->spa_all_vdev_zaps);
		    zap_cursor_retrieve(&zc, &za) == 0;
		    zap_cursor_advance(&zc)) {
			uint64_t zap = za.za_first_integer;
			VERIFY0(zap_destroy(spa->spa_meta_objset, zap, tx));
		}

		zap_cursor_fini(&zc);

		/* Destroy and unlink the AVZ itself */
		VERIFY0(zap_destroy(spa->spa_meta_objset,
		    spa->spa_all_vdev_zaps, tx));
		VERIFY0(zap_remove(spa->spa_meta_objset,
		    DMU_POOL_DIRECTORY_OBJECT, DMU_POOL_VDEV_ZAP_MAP, tx));
		spa->spa_all_vdev_zaps = 0;
	}

	if (spa->spa_all_vdev_zaps == 0) {
		spa->spa_all_vdev_zaps = zap_create_link(spa->spa_meta_objset,
		    DMU_OTN_ZAP_METADATA, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_VDEV_ZAP_MAP, tx);
	}
	spa->spa_avz_action = AVZ_ACTION_NONE;

	/* Create ZAPs for vdevs that don't have them. */
	vdev_construct_zaps(spa->spa_root_vdev, tx);

	config = spa_config_generate(spa, spa->spa_root_vdev,
	    dmu_tx_get_txg(tx), B_FALSE);

	/*
	 * If we're upgrading the spa version then make sure that
	 * the config object gets updated with the correct version.
	 */
	if (spa->spa_ubsync.ub_version < spa->spa_uberblock.ub_version)
		fnvlist_add_uint64(config, ZPOOL_CONFIG_VERSION,
		    spa->spa_uberblock.ub_version);

	spa_config_exit(spa, SCL_STATE, FTAG);

	nvlist_free(spa->spa_config_syncing);
	spa->spa_config_syncing = config;

	spa_sync_nvlist(spa, spa->spa_config_object, config, tx);
}