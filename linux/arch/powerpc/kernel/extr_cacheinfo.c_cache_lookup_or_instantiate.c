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
struct device_node {int dummy; } ;
struct cache {int level; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*,int,int) ; 
 struct cache* cache_do_one_devnode (struct device_node*,int) ; 
 struct cache* cache_lookup_by_node (struct device_node*) ; 

__attribute__((used)) static struct cache *cache_lookup_or_instantiate(struct device_node *node,
						 int level)
{
	struct cache *cache;

	cache = cache_lookup_by_node(node);

	WARN_ONCE(cache && cache->level != level,
		  "cache level mismatch on lookup (got %d, expected %d)\n",
		  cache->level, level);

	if (!cache)
		cache = cache_do_one_devnode(node, level);

	return cache;
}