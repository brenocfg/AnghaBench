#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  uqn_delta; int /*<<< orphan*/  uqn_id; } ;
typedef  TYPE_1__ userquota_node_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
userquota_update_cache(avl_tree_t *avl, uint64_t id, int64_t delta)
{
	userquota_node_t search = { .uqn_id = id };
	avl_index_t idx;

	userquota_node_t *uqn = avl_find(avl, &search, &idx);
	if (uqn == NULL) {
		uqn = kmem_zalloc(sizeof (*uqn), KM_SLEEP);
		uqn->uqn_id = id;
		avl_insert(avl, uqn, idx);
	}
	uqn->uqn_delta += delta;
}