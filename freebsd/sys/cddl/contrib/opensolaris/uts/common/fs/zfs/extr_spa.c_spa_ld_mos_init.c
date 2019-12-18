#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ spa_config_source; int /*<<< orphan*/  spa_trust_config; } ;
typedef  TYPE_1__ spa_t ;
typedef  scalar_t__ spa_import_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ SPA_CONFIG_SRC_NONE ; 
 scalar_t__ SPA_IMPORT_ASSEMBLE ; 
 int spa_ld_open_rootbp (TYPE_1__*) ; 
 int spa_ld_open_vdevs (TYPE_1__*) ; 
 int spa_ld_parse_config (TYPE_1__*,scalar_t__) ; 
 int spa_ld_select_uberblock (TYPE_1__*,scalar_t__) ; 
 int spa_ld_validate_vdevs (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 

__attribute__((used)) static int
spa_ld_mos_init(spa_t *spa, spa_import_type_t type)
{
	int error = 0;

	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	ASSERT(spa->spa_config_source != SPA_CONFIG_SRC_NONE);

	/*
	 * Never trust the config that is provided unless we are assembling
	 * a pool following a split.
	 * This means don't trust blkptrs and the vdev tree in general. This
	 * also effectively puts the spa in read-only mode since
	 * spa_writeable() checks for spa_trust_config to be true.
	 * We will later load a trusted config from the MOS.
	 */
	if (type != SPA_IMPORT_ASSEMBLE)
		spa->spa_trust_config = B_FALSE;

	/*
	 * Parse the config provided to create a vdev tree.
	 */
	error = spa_ld_parse_config(spa, type);
	if (error != 0)
		return (error);

	/*
	 * Now that we have the vdev tree, try to open each vdev. This involves
	 * opening the underlying physical device, retrieving its geometry and
	 * probing the vdev with a dummy I/O. The state of each vdev will be set
	 * based on the success of those operations. After this we'll be ready
	 * to read from the vdevs.
	 */
	error = spa_ld_open_vdevs(spa);
	if (error != 0)
		return (error);

	/*
	 * Read the label of each vdev and make sure that the GUIDs stored
	 * there match the GUIDs in the config provided.
	 * If we're assembling a new pool that's been split off from an
	 * existing pool, the labels haven't yet been updated so we skip
	 * validation for now.
	 */
	if (type != SPA_IMPORT_ASSEMBLE) {
		error = spa_ld_validate_vdevs(spa);
		if (error != 0)
			return (error);
	}

	/*
	 * Read all vdev labels to find the best uberblock (i.e. latest,
	 * unless spa_load_max_txg is set) and store it in spa_uberblock. We
	 * get the list of features required to read blkptrs in the MOS from
	 * the vdev label with the best uberblock and verify that our version
	 * of zfs supports them all.
	 */
	error = spa_ld_select_uberblock(spa, type);
	if (error != 0)
		return (error);

	/*
	 * Pass that uberblock to the dsl_pool layer which will open the root
	 * blkptr. This blkptr points to the latest version of the MOS and will
	 * allow us to read its contents.
	 */
	error = spa_ld_open_rootbp(spa);
	if (error != 0)
		return (error);

	return (0);
}