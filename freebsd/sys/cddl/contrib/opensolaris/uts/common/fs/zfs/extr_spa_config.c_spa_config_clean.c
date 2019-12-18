#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_TYPE_UINT64_ARRAY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SCAN_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 int /*<<< orphan*/  nvlist_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_config_clean(nvlist_t *nvl)
{
	nvlist_t **child;
	nvlist_t *nvroot = NULL;
	uint_t c, children;

	if (nvlist_lookup_nvlist_array(nvl, ZPOOL_CONFIG_CHILDREN, &child,
	    &children) == 0) {
		for (c = 0; c < children; c++)
			spa_config_clean(child[c]);
	}

	if (nvlist_lookup_nvlist(nvl, ZPOOL_CONFIG_VDEV_TREE, &nvroot) == 0)
		spa_config_clean(nvroot);

	nvlist_remove(nvl, ZPOOL_CONFIG_VDEV_STATS, DATA_TYPE_UINT64_ARRAY);
	nvlist_remove(nvl, ZPOOL_CONFIG_SCAN_STATS, DATA_TYPE_UINT64_ARRAY);
}