#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fi_guid; } ;
typedef  TYPE_1__ zfeature_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int SPA_FEATURES ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 scalar_t__ feature_get_refcount (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* spa_feature_table ; 

__attribute__((used)) static void
spa_feature_stats_from_cache(spa_t *spa, nvlist_t *features)
{
	int i;

	for (i = 0; i < SPA_FEATURES; i++) {
		zfeature_info_t feature = spa_feature_table[i];
		uint64_t refcount;

		if (feature_get_refcount(spa, &feature, &refcount) != 0)
			continue;

		VERIFY0(nvlist_add_uint64(features, feature.fi_guid, refcount));
	}
}