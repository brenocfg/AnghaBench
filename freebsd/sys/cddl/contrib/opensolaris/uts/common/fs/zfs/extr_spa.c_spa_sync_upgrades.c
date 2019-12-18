#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  zcs_bytes; } ;
struct TYPE_15__ {scalar_t__ ub_version; } ;
struct TYPE_14__ {scalar_t__ ub_version; } ;
struct TYPE_17__ {int spa_sync_pass; int spa_minref; TYPE_3__ spa_cksum_salt; int /*<<< orphan*/  spa_meta_objset; TYPE_2__ spa_uberblock; TYPE_1__ spa_ubsync; TYPE_5__* spa_dsl_pool; } ;
typedef  TYPE_4__ spa_t ;
struct TYPE_18__ {int /*<<< orphan*/  dp_config_rwlock; } ;
typedef  TYPE_5__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_POOL_CHECKSUM_SALT ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SPA_FEATURE_LZ4_COMPRESS ; 
 scalar_t__ SPA_VERSION_DIR_CLONES ; 
 scalar_t__ SPA_VERSION_FEATURES ; 
 scalar_t__ SPA_VERSION_NEXT_CLONES ; 
 scalar_t__ SPA_VERSION_ORIGIN ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_create_origin (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_upgrade_clones (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_upgrade_dir_clones (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_create_zap_objects (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_incr (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_feature_is_active (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_feature_is_enabled (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_sync_upgrades(spa_t *spa, dmu_tx_t *tx)
{
	dsl_pool_t *dp = spa->spa_dsl_pool;

	ASSERT(spa->spa_sync_pass == 1);

	rrw_enter(&dp->dp_config_rwlock, RW_WRITER, FTAG);

	if (spa->spa_ubsync.ub_version < SPA_VERSION_ORIGIN &&
	    spa->spa_uberblock.ub_version >= SPA_VERSION_ORIGIN) {
		dsl_pool_create_origin(dp, tx);

		/* Keeping the origin open increases spa_minref */
		spa->spa_minref += 3;
	}

	if (spa->spa_ubsync.ub_version < SPA_VERSION_NEXT_CLONES &&
	    spa->spa_uberblock.ub_version >= SPA_VERSION_NEXT_CLONES) {
		dsl_pool_upgrade_clones(dp, tx);
	}

	if (spa->spa_ubsync.ub_version < SPA_VERSION_DIR_CLONES &&
	    spa->spa_uberblock.ub_version >= SPA_VERSION_DIR_CLONES) {
		dsl_pool_upgrade_dir_clones(dp, tx);

		/* Keeping the freedir open increases spa_minref */
		spa->spa_minref += 3;
	}

	if (spa->spa_ubsync.ub_version < SPA_VERSION_FEATURES &&
	    spa->spa_uberblock.ub_version >= SPA_VERSION_FEATURES) {
		spa_feature_create_zap_objects(spa, tx);
	}

	/*
	 * LZ4_COMPRESS feature's behaviour was changed to activate_on_enable
	 * when possibility to use lz4 compression for metadata was added
	 * Old pools that have this feature enabled must be upgraded to have
	 * this feature active
	 */
	if (spa->spa_uberblock.ub_version >= SPA_VERSION_FEATURES) {
		boolean_t lz4_en = spa_feature_is_enabled(spa,
		    SPA_FEATURE_LZ4_COMPRESS);
		boolean_t lz4_ac = spa_feature_is_active(spa,
		    SPA_FEATURE_LZ4_COMPRESS);

		if (lz4_en && !lz4_ac)
			spa_feature_incr(spa, SPA_FEATURE_LZ4_COMPRESS, tx);
	}

	/*
	 * If we haven't written the salt, do so now.  Note that the
	 * feature may not be activated yet, but that's fine since
	 * the presence of this ZAP entry is backwards compatible.
	 */
	if (zap_contains(spa->spa_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_CHECKSUM_SALT) == ENOENT) {
		VERIFY0(zap_add(spa->spa_meta_objset,
		    DMU_POOL_DIRECTORY_OBJECT, DMU_POOL_CHECKSUM_SALT, 1,
		    sizeof (spa->spa_cksum_salt.zcs_bytes),
		    spa->spa_cksum_salt.zcs_bytes, tx));
	}

	rrw_exit(&dp->dp_config_rwlock, FTAG);
}