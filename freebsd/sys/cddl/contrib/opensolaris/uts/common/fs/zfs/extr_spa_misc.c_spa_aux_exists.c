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
typedef  unsigned long long uint64_t ;
struct TYPE_4__ {unsigned long long aux_guid; unsigned long long aux_pool; int aux_count; } ;
typedef  TYPE_1__ spa_aux_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

boolean_t
spa_aux_exists(uint64_t guid, uint64_t *pool, int *refcnt, avl_tree_t *avl)
{
	spa_aux_t search, *found;

	search.aux_guid = guid;
	found = avl_find(avl, &search, NULL);

	if (pool) {
		if (found)
			*pool = found->aux_pool;
		else
			*pool = 0ULL;
	}

	if (refcnt) {
		if (found)
			*refcnt = found->aux_count;
		else
			*refcnt = 0;
	}

	return (found != NULL);
}