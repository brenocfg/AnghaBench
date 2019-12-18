#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_label_features; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_6__ {scalar_t__ tx_txg; } ;
typedef  TYPE_2__ dmu_tx_t ;

/* Variables and functions */
 scalar_t__ TXG_INITIAL ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vdev_config_dirty (int /*<<< orphan*/ ) ; 

void
spa_activate_mos_feature(spa_t *spa, const char *feature, dmu_tx_t *tx)
{
	if (!nvlist_exists(spa->spa_label_features, feature)) {
		fnvlist_add_boolean(spa->spa_label_features, feature);
		/*
		 * When we are creating the pool (tx_txg==TXG_INITIAL), we can't
		 * dirty the vdev config because lock SCL_CONFIG is not held.
		 * Thankfully, in this case we don't need to dirty the config
		 * because it will be written out anyway when we finish
		 * creating the pool.
		 */
		if (tx->tx_txg != TXG_INITIAL)
			vdev_config_dirty(spa->spa_root_vdev);
	}
}