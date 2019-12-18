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
struct cache {int dummy; } ;

/* Variables and functions */
 struct cache* cache_do_one_devnode_split (struct device_node*,int) ; 
 struct cache* cache_do_one_devnode_unified (struct device_node*,int) ; 
 scalar_t__ cache_node_is_unified (struct device_node*) ; 

__attribute__((used)) static struct cache *cache_do_one_devnode(struct device_node *node, int level)
{
	struct cache *cache;

	if (cache_node_is_unified(node))
		cache = cache_do_one_devnode_unified(node, level);
	else
		cache = cache_do_one_devnode_split(node, level);

	return cache;
}