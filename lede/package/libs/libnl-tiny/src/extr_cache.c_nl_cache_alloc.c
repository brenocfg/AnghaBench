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
struct nl_cache_ops {int dummy; } ;
struct nl_cache {struct nl_cache_ops* c_ops; int /*<<< orphan*/  c_items; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_cache*,int /*<<< orphan*/ ) ; 
 struct nl_cache* calloc (int,int) ; 
 int /*<<< orphan*/  nl_cache_name (struct nl_cache*) ; 
 int /*<<< orphan*/  nl_init_list_head (int /*<<< orphan*/ *) ; 

struct nl_cache *nl_cache_alloc(struct nl_cache_ops *ops)
{
	struct nl_cache *cache;

	cache = calloc(1, sizeof(*cache));
	if (!cache)
		return NULL;

	nl_init_list_head(&cache->c_items);
	cache->c_ops = ops;

	NL_DBG(2, "Allocated cache %p <%s>.\n", cache, nl_cache_name(cache));

	return cache;
}