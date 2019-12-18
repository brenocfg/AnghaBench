#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nl_cache_ops {int /*<<< orphan*/  co_name; struct nl_cache_ops* co_next; int /*<<< orphan*/  co_obj_ops; } ;

/* Variables and functions */
 int NLE_EXIST ; 
 int NLE_INVAL ; 
 int /*<<< orphan*/  NL_DBG (int,char*,int /*<<< orphan*/ ) ; 
 struct nl_cache_ops* cache_ops ; 
 scalar_t__ nl_cache_ops_lookup (int /*<<< orphan*/ ) ; 

int nl_cache_mngt_register(struct nl_cache_ops *ops)
{
	if (!ops->co_name || !ops->co_obj_ops)
		return -NLE_INVAL;

	if (nl_cache_ops_lookup(ops->co_name))
		return -NLE_EXIST;

	ops->co_next = cache_ops;
	cache_ops = ops;

	NL_DBG(1, "Registered cache operations %s\n", ops->co_name);

	return 0;
}