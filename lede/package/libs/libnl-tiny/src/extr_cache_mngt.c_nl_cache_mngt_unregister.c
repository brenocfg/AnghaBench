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
struct nl_cache_ops {struct nl_cache_ops* co_next; int /*<<< orphan*/  co_name; } ;

/* Variables and functions */
 int NLE_NOCACHE ; 
 int /*<<< orphan*/  NL_DBG (int,char*,int /*<<< orphan*/ ) ; 
 struct nl_cache_ops* cache_ops ; 

int nl_cache_mngt_unregister(struct nl_cache_ops *ops)
{
	struct nl_cache_ops *t, **tp;

	for (tp = &cache_ops; (t=*tp) != NULL; tp = &t->co_next)
		if (t == ops)
			break;

	if (!t)
		return -NLE_NOCACHE;

	NL_DBG(1, "Unregistered cache operations %s\n", ops->co_name);

	*tp = t->co_next;
	return 0;
}