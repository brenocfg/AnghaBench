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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  size_t spa_feature_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 int ENOTSUP ; 
 scalar_t__ SPA_VERSION_FEATURES ; 
 int VALID_FEATURE_FID (size_t) ; 
 int feature_get_enabled_txg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spa_feature_table ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 

boolean_t
spa_feature_enabled_txg(spa_t *spa, spa_feature_t fid, uint64_t *txg)
{
	int err;

	ASSERT(VALID_FEATURE_FID(fid));
	if (spa_version(spa) < SPA_VERSION_FEATURES)
		return (B_FALSE);

	err = feature_get_enabled_txg(spa, &spa_feature_table[fid], txg);
	ASSERT(err == 0 || err == ENOTSUP);

	return (err == 0);
}