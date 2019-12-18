#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_13__ {scalar_t__ ub_checkpoint_txg; scalar_t__ ub_txg; scalar_t__ ub_version; } ;
typedef  TYPE_1__ uberblock_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_14__ {int /*<<< orphan*/ * spa_config_splitting; int /*<<< orphan*/  spa_config; int /*<<< orphan*/  spa_load_info; int /*<<< orphan*/ * spa_label_features; TYPE_1__ spa_uberblock; int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  scalar_t__ spa_import_type_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 scalar_t__ SPA_IMPORT_ASSEMBLE ; 
 scalar_t__ SPA_VERSION_FEATURES ; 
 int /*<<< orphan*/  SPA_VERSION_IS_SUPPORTED (scalar_t__) ; 
 int /*<<< orphan*/  VDEV_AUX_CORRUPT_DATA ; 
 int /*<<< orphan*/  VDEV_AUX_UNSUP_FEAT ; 
 int /*<<< orphan*/  VDEV_AUX_VERSION_NEWER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_FEATURES_FOR_READ ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_UNSUP_FEAT ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_importing_readonly_checkpoint (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_ld_select_uberblock_done (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_try_repair (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int spa_vdev_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_uberblock_load (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfeature_is_supported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_ld_select_uberblock(spa_t *spa, spa_import_type_t type)
{
	vdev_t *rvd = spa->spa_root_vdev;
	nvlist_t *label;
	uberblock_t *ub = &spa->spa_uberblock;

	/*
	 * If we are opening the checkpointed state of the pool by
	 * rewinding to it, at this point we will have written the
	 * checkpointed uberblock to the vdev labels, so searching
	 * the labels will find the right uberblock.  However, if
	 * we are opening the checkpointed state read-only, we have
	 * not modified the labels. Therefore, we must ignore the
	 * labels and continue using the spa_uberblock that was set
	 * by spa_ld_checkpoint_rewind.
	 *
	 * Note that it would be fine to ignore the labels when
	 * rewinding (opening writeable) as well. However, if we
	 * crash just after writing the labels, we will end up
	 * searching the labels. Doing so in the common case means
	 * that this code path gets exercised normally, rather than
	 * just in the edge case.
	 */
	if (ub->ub_checkpoint_txg != 0 &&
	    spa_importing_readonly_checkpoint(spa)) {
		spa_ld_select_uberblock_done(spa, ub);
		return (0);
	}

	/*
	 * Find the best uberblock.
	 */
	vdev_uberblock_load(rvd, ub, &label);

	/*
	 * If we weren't able to find a single valid uberblock, return failure.
	 */
	if (ub->ub_txg == 0) {
		nvlist_free(label);
		spa_load_failed(spa, "no valid uberblock found");
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, ENXIO));
	}

	spa_load_note(spa, "using uberblock with txg=%llu",
	    (u_longlong_t)ub->ub_txg);

	/*
	 * If the pool has an unsupported version we can't open it.
	 */
	if (!SPA_VERSION_IS_SUPPORTED(ub->ub_version)) {
		nvlist_free(label);
		spa_load_failed(spa, "version %llu is not supported",
		    (u_longlong_t)ub->ub_version);
		return (spa_vdev_err(rvd, VDEV_AUX_VERSION_NEWER, ENOTSUP));
	}

	if (ub->ub_version >= SPA_VERSION_FEATURES) {
		nvlist_t *features;

		/*
		 * If we weren't able to find what's necessary for reading the
		 * MOS in the label, return failure.
		 */
		if (label == NULL) {
			spa_load_failed(spa, "label config unavailable");
			return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA,
			    ENXIO));
		}

		if (nvlist_lookup_nvlist(label, ZPOOL_CONFIG_FEATURES_FOR_READ,
		    &features) != 0) {
			nvlist_free(label);
			spa_load_failed(spa, "invalid label: '%s' missing",
			    ZPOOL_CONFIG_FEATURES_FOR_READ);
			return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA,
			    ENXIO));
		}

		/*
		 * Update our in-core representation with the definitive values
		 * from the label.
		 */
		nvlist_free(spa->spa_label_features);
		VERIFY(nvlist_dup(features, &spa->spa_label_features, 0) == 0);
	}

	nvlist_free(label);

	/*
	 * Look through entries in the label nvlist's features_for_read. If
	 * there is a feature listed there which we don't understand then we
	 * cannot open a pool.
	 */
	if (ub->ub_version >= SPA_VERSION_FEATURES) {
		nvlist_t *unsup_feat;

		VERIFY(nvlist_alloc(&unsup_feat, NV_UNIQUE_NAME, KM_SLEEP) ==
		    0);

		for (nvpair_t *nvp = nvlist_next_nvpair(spa->spa_label_features,
		    NULL); nvp != NULL;
		    nvp = nvlist_next_nvpair(spa->spa_label_features, nvp)) {
			if (!zfeature_is_supported(nvpair_name(nvp))) {
				VERIFY(nvlist_add_string(unsup_feat,
				    nvpair_name(nvp), "") == 0);
			}
		}

		if (!nvlist_empty(unsup_feat)) {
			VERIFY(nvlist_add_nvlist(spa->spa_load_info,
			    ZPOOL_CONFIG_UNSUP_FEAT, unsup_feat) == 0);
			nvlist_free(unsup_feat);
			spa_load_failed(spa, "some features are unsupported");
			return (spa_vdev_err(rvd, VDEV_AUX_UNSUP_FEAT,
			    ENOTSUP));
		}

		nvlist_free(unsup_feat);
	}

	if (type != SPA_IMPORT_ASSEMBLE && spa->spa_config_splitting) {
		spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
		spa_try_repair(spa, spa->spa_config);
		spa_config_exit(spa, SCL_ALL, FTAG);
		nvlist_free(spa->spa_config_splitting);
		spa->spa_config_splitting = NULL;
	}

	/*
	 * Initialize internal SPA structures.
	 */
	spa_ld_select_uberblock_done(spa, ub);

	return (0);
}