#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  spa_meta_objset; void* spa_feat_desc_obj; void* spa_feat_for_write_obj; void* spa_feat_for_read_obj; int /*<<< orphan*/  spa_sync_on; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_8__ {scalar_t__ tx_txg; } ;
typedef  TYPE_2__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_OTN_ZAP_METADATA ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_FEATURES_FOR_READ ; 
 int /*<<< orphan*/  DMU_POOL_FEATURES_FOR_WRITE ; 
 int /*<<< orphan*/  DMU_POOL_FEATURE_DESCRIPTIONS ; 
 scalar_t__ TXG_INITIAL ; 
 scalar_t__ dsl_pool_sync_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (TYPE_1__*) ; 
 void* zap_create_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

void
spa_feature_create_zap_objects(spa_t *spa, dmu_tx_t *tx)
{
	/*
	 * We create feature flags ZAP objects in two instances: during pool
	 * creation and during pool upgrade.
	 */
	ASSERT(dsl_pool_sync_context(spa_get_dsl(spa)) || (!spa->spa_sync_on &&
	    tx->tx_txg == TXG_INITIAL));

	spa->spa_feat_for_read_obj = zap_create_link(spa->spa_meta_objset,
	    DMU_OTN_ZAP_METADATA, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_FEATURES_FOR_READ, tx);
	spa->spa_feat_for_write_obj = zap_create_link(spa->spa_meta_objset,
	    DMU_OTN_ZAP_METADATA, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_FEATURES_FOR_WRITE, tx);
	spa->spa_feat_desc_obj = zap_create_link(spa->spa_meta_objset,
	    DMU_OTN_ZAP_METADATA, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_FEATURE_DESCRIPTIONS, tx);
}