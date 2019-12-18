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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_TXG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TOP_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  resize_configs (int /*<<< orphan*/ ***,scalar_t__*,scalar_t__) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static void
process_vdev_config(nvlist_t ***configs, uint64_t *count, nvlist_t *cfg,
    const char *name, uint64_t* known_pool_guid)
{
	nvlist_t *vdev_tree;
	uint64_t pool_guid;
	uint64_t vdev_guid, known_guid;
	uint64_t id, txg, known_txg;
	char *pname;
	int i;

	if (nvlist_lookup_string(cfg, ZPOOL_CONFIG_POOL_NAME, &pname) != 0 ||
	    strcmp(pname, name) != 0)
		goto ignore;

	if (nvlist_lookup_uint64(cfg, ZPOOL_CONFIG_POOL_GUID, &pool_guid) != 0)
		goto ignore;

	if (nvlist_lookup_uint64(cfg, ZPOOL_CONFIG_TOP_GUID, &vdev_guid) != 0)
		goto ignore;

	if (nvlist_lookup_nvlist(cfg, ZPOOL_CONFIG_VDEV_TREE, &vdev_tree) != 0)
		goto ignore;

	if (nvlist_lookup_uint64(vdev_tree, ZPOOL_CONFIG_ID, &id) != 0)
		goto ignore;

	VERIFY(nvlist_lookup_uint64(cfg, ZPOOL_CONFIG_POOL_TXG, &txg) == 0);

	if (*known_pool_guid != 0) {
		if (pool_guid != *known_pool_guid)
			goto ignore;
	} else
		*known_pool_guid = pool_guid;

	resize_configs(configs, count, id);

	if ((*configs)[id] != NULL) {
		VERIFY(nvlist_lookup_uint64((*configs)[id],
		    ZPOOL_CONFIG_POOL_TXG, &known_txg) == 0);
		if (txg <= known_txg)
			goto ignore;
		nvlist_free((*configs)[id]);
	}

	(*configs)[id] = cfg;
	return;

ignore:
	nvlist_free(cfg);
}