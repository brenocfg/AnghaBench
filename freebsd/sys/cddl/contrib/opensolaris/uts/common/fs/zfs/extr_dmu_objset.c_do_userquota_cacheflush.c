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
struct TYPE_9__ {int /*<<< orphan*/  uqn_delta; int /*<<< orphan*/  uqn_id; } ;
typedef  TYPE_1__ userquota_node_t ;
struct TYPE_10__ {int /*<<< orphan*/  uqc_group_deltas; int /*<<< orphan*/  uqc_user_deltas; } ;
typedef  TYPE_2__ userquota_cache_t ;
struct TYPE_11__ {int /*<<< orphan*/  os_userused_lock; } ;
typedef  TYPE_3__ objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_GROUPUSED_OBJECT ; 
 int /*<<< orphan*/  DMU_USERUSED_OBJECT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_increment_int (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_userquota_cacheflush(objset_t *os, userquota_cache_t *cache, dmu_tx_t *tx)
{
	void *cookie;
	userquota_node_t *uqn;

	ASSERT(dmu_tx_is_syncing(tx));

	cookie = NULL;
	while ((uqn = avl_destroy_nodes(&cache->uqc_user_deltas,
	    &cookie)) != NULL) {
		/*
		 * os_userused_lock protects against concurrent calls to
		 * zap_increment_int().  It's needed because zap_increment_int()
		 * is not thread-safe (i.e. not atomic).
		 */
		mutex_enter(&os->os_userused_lock);
		VERIFY0(zap_increment_int(os, DMU_USERUSED_OBJECT,
		    uqn->uqn_id, uqn->uqn_delta, tx));
		mutex_exit(&os->os_userused_lock);
		kmem_free(uqn, sizeof (*uqn));
	}
	avl_destroy(&cache->uqc_user_deltas);

	cookie = NULL;
	while ((uqn = avl_destroy_nodes(&cache->uqc_group_deltas,
	    &cookie)) != NULL) {
		mutex_enter(&os->os_userused_lock);
		VERIFY0(zap_increment_int(os, DMU_GROUPUSED_OBJECT,
		    uqn->uqn_id, uqn->uqn_delta, tx));
		mutex_exit(&os->os_userused_lock);
		kmem_free(uqn, sizeof (*uqn));
	}
	avl_destroy(&cache->uqc_group_deltas);
}