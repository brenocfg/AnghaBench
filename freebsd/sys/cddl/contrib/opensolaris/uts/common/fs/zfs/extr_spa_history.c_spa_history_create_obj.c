#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_history; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_10__ {int sh_phys_max_off; } ;
typedef  TYPE_2__ spa_history_phys_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_11__ {int db_size; TYPE_2__* db_data; } ;
typedef  TYPE_3__ dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_OT_SPA_HISTORY ; 
 int /*<<< orphan*/  DMU_OT_SPA_HISTORY_OFFSETS ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_HISTORY ; 
 int /*<<< orphan*/  FTAG ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ dmu_bonus_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int metaslab_class_get_dspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_normal_class (TYPE_1__*) ; 
 scalar_t__ zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
spa_history_create_obj(spa_t *spa, dmu_tx_t *tx)
{
	dmu_buf_t *dbp;
	spa_history_phys_t *shpp;
	objset_t *mos = spa->spa_meta_objset;

	ASSERT(spa->spa_history == 0);
	spa->spa_history = dmu_object_alloc(mos, DMU_OT_SPA_HISTORY,
	    SPA_OLD_MAXBLOCKSIZE, DMU_OT_SPA_HISTORY_OFFSETS,
	    sizeof (spa_history_phys_t), tx);

	VERIFY(zap_add(mos, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_HISTORY, sizeof (uint64_t), 1,
	    &spa->spa_history, tx) == 0);

	VERIFY(0 == dmu_bonus_hold(mos, spa->spa_history, FTAG, &dbp));
	ASSERT(dbp->db_size >= sizeof (spa_history_phys_t));

	shpp = dbp->db_data;
	dmu_buf_will_dirty(dbp, tx);

	/*
	 * Figure out maximum size of history log.  We set it at
	 * 0.1% of pool size, with a max of 1G and min of 128KB.
	 */
	shpp->sh_phys_max_off =
	    metaslab_class_get_dspace(spa_normal_class(spa)) / 1000;
	shpp->sh_phys_max_off = MIN(shpp->sh_phys_max_off, 1<<30);
	shpp->sh_phys_max_off = MAX(shpp->sh_phys_max_off, 128<<10);

	dmu_buf_rele(dbp, FTAG);
}