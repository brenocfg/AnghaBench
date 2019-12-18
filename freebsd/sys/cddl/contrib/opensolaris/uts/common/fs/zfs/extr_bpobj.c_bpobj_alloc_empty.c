#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_3__ {scalar_t__ dp_empty_bpobj; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (scalar_t__) ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_EMPTY_BPOBJ ; 
 int /*<<< orphan*/  SPA_FEATURE_EMPTY_BPOBJ ; 
 int SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ bpobj_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_incr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 

uint64_t
bpobj_alloc_empty(objset_t *os, int blocksize, dmu_tx_t *tx)
{
	spa_t *spa = dmu_objset_spa(os);
	dsl_pool_t *dp = dmu_objset_pool(os);

	if (spa_feature_is_enabled(spa, SPA_FEATURE_EMPTY_BPOBJ)) {
		if (!spa_feature_is_active(spa, SPA_FEATURE_EMPTY_BPOBJ)) {
			ASSERT0(dp->dp_empty_bpobj);
			dp->dp_empty_bpobj =
			    bpobj_alloc(os, SPA_OLD_MAXBLOCKSIZE, tx);
			VERIFY(zap_add(os,
			    DMU_POOL_DIRECTORY_OBJECT,
			    DMU_POOL_EMPTY_BPOBJ, sizeof (uint64_t), 1,
			    &dp->dp_empty_bpobj, tx) == 0);
		}
		spa_feature_incr(spa, SPA_FEATURE_EMPTY_BPOBJ, tx);
		ASSERT(dp->dp_empty_bpobj != 0);
		return (dp->dp_empty_bpobj);
	} else {
		return (bpobj_alloc(os, blocksize, tx));
	}
}