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
struct cache {int type; int level; int /*<<< orphan*/  list; int /*<<< orphan*/  ofnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_list ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 

__attribute__((used)) static void cache_init(struct cache *cache, int type, int level,
		       struct device_node *ofnode)
{
	cache->type = type;
	cache->level = level;
	cache->ofnode = of_node_get(ofnode);
	INIT_LIST_HEAD(&cache->list);
	list_add(&cache->list, &cache_list);
}