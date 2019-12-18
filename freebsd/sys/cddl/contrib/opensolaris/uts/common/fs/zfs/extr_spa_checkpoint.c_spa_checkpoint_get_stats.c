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
struct TYPE_9__ {int /*<<< orphan*/  sci_timestamp; int /*<<< orphan*/  sci_dspace; } ;
struct TYPE_10__ {TYPE_1__ spa_checkpoint_info; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_11__ {int /*<<< orphan*/  pcs_start_time; int /*<<< orphan*/  pcs_space; int /*<<< orphan*/  pcs_state; } ;
typedef  TYPE_3__ pool_checkpoint_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CS_CHECKPOINT_DISCARDING ; 
 int /*<<< orphan*/  CS_CHECKPOINT_EXISTS ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_ZPOOL_CHECKPOINT ; 
 int ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  ZFS_ERR_NO_CHECKPOINT ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  spa_feature_is_active (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_meta_objset (TYPE_2__*) ; 
 int zap_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
spa_checkpoint_get_stats(spa_t *spa, pool_checkpoint_stat_t *pcs)
{
	if (!spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT))
		return (SET_ERROR(ZFS_ERR_NO_CHECKPOINT));

	bzero(pcs, sizeof (pool_checkpoint_stat_t));

	int error = zap_contains(spa_meta_objset(spa),
	    DMU_POOL_DIRECTORY_OBJECT, DMU_POOL_ZPOOL_CHECKPOINT);
	ASSERT(error == 0 || error == ENOENT);

	if (error == ENOENT)
		pcs->pcs_state = CS_CHECKPOINT_DISCARDING;
	else
		pcs->pcs_state = CS_CHECKPOINT_EXISTS;

	pcs->pcs_space = spa->spa_checkpoint_info.sci_dspace;
	pcs->pcs_start_time = spa->spa_checkpoint_info.sci_timestamp;

	return (0);
}