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
struct nl_cache_ops {int /*<<< orphan*/  co_name; struct nl_cache_ops* co_next; } ;

/* Variables and functions */
 struct nl_cache_ops* cache_ops ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct nl_cache_ops *nl_cache_ops_lookup(const char *name)
{
	struct nl_cache_ops *ops;

	for (ops = cache_ops; ops; ops = ops->co_next)
		if (!strcmp(ops->co_name, name))
			return ops;

	return NULL;
}