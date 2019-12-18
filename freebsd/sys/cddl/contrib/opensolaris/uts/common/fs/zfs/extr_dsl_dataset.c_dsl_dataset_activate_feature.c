#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zero ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dp_meta_objset; int /*<<< orphan*/ * dp_spa; } ;
struct TYPE_3__ {int fi_flags; int /*<<< orphan*/  fi_guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_OT_DSL_DATASET ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZFEATURE_FLAG_PER_DATASET ; 
 int /*<<< orphan*/  dmu_object_zapify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_incr (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 TYPE_1__* spa_feature_table ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_dataset_activate_feature(uint64_t dsobj, spa_feature_t f, dmu_tx_t *tx)
{
	spa_t *spa = dmu_tx_pool(tx)->dp_spa;
	objset_t *mos = dmu_tx_pool(tx)->dp_meta_objset;
	uint64_t zero = 0;

	VERIFY(spa_feature_table[f].fi_flags & ZFEATURE_FLAG_PER_DATASET);

	spa_feature_incr(spa, f, tx);
	dmu_object_zapify(mos, dsobj, DMU_OT_DSL_DATASET, tx);

	VERIFY0(zap_add(mos, dsobj, spa_feature_table[f].fi_guid,
	    sizeof (zero), 1, &zero, tx));
}