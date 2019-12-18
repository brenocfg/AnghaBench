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
struct object_id {int dummy; } ;
struct index_state {TYPE_1__* cache_tree; } ;
struct TYPE_3__ {struct object_id oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* cache_tree () ; 
 int /*<<< orphan*/  cache_tree_fully_valid (TYPE_1__*) ; 
 scalar_t__ cache_tree_update (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct object_id *get_cache_tree_oid(struct index_state *istate)
{
	if (!istate->cache_tree)
		istate->cache_tree = cache_tree();

	if (!cache_tree_fully_valid(istate->cache_tree))
		if (cache_tree_update(istate, 0)) {
			error(_("unable to update cache tree"));
			return NULL;
		}

	return &istate->cache_tree->oid;
}