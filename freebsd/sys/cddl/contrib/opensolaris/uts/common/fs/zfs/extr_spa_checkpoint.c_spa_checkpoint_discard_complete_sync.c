#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sci_timestamp; } ;
struct TYPE_6__ {TYPE_1__ spa_checkpoint_info; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  spa_feature_decr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_2__*,char*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
spa_checkpoint_discard_complete_sync(void *arg, dmu_tx_t *tx)
{
	spa_t *spa = arg;

	spa->spa_checkpoint_info.sci_timestamp = 0;

	spa_feature_decr(spa, SPA_FEATURE_POOL_CHECKPOINT, tx);

	spa_history_log_internal(spa, "spa discard checkpoint", tx,
	    "finished discarding checkpointed state from the pool");
}