#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  spa_feat_stats_lock; int /*<<< orphan*/ * spa_feat_stats; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_FEATURE_STATS ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_held (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_stats_from_cache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_stats_from_disk (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_add_feature_stats(spa_t *spa, nvlist_t *config)
{
	nvlist_t *features;

	ASSERT(spa_config_held(spa, SCL_CONFIG, RW_READER));

	mutex_enter(&spa->spa_feat_stats_lock);
	features = spa->spa_feat_stats;

	if (features != NULL) {
		spa_feature_stats_from_cache(spa, features);
	} else {
		VERIFY0(nvlist_alloc(&features, NV_UNIQUE_NAME, KM_SLEEP));
		spa->spa_feat_stats = features;
		spa_feature_stats_from_disk(spa, features);
	}

	VERIFY0(nvlist_add_nvlist(config, ZPOOL_CONFIG_FEATURE_STATS,
	    features));

	mutex_exit(&spa->spa_feat_stats_lock);
}