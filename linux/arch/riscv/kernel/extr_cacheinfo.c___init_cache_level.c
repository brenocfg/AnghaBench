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
struct cpu_cacheinfo {int num_levels; int num_leaves; } ;

/* Variables and functions */
 struct cpu_cacheinfo* get_cpu_cacheinfo (unsigned int) ; 
 struct device_node* of_cpu_device_node_get (unsigned int) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_find_next_cache_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int __init_cache_level(unsigned int cpu)
{
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	struct device_node *np = of_cpu_device_node_get(cpu);
	struct device_node *prev = NULL;
	int levels = 0, leaves = 0, level;

	if (of_property_read_bool(np, "cache-size"))
		++leaves;
	if (of_property_read_bool(np, "i-cache-size"))
		++leaves;
	if (of_property_read_bool(np, "d-cache-size"))
		++leaves;
	if (leaves > 0)
		levels = 1;

	prev = np;
	while ((np = of_find_next_cache_node(np))) {
		of_node_put(prev);
		prev = np;
		if (!of_device_is_compatible(np, "cache"))
			break;
		if (of_property_read_u32(np, "cache-level", &level))
			break;
		if (level <= levels)
			break;
		if (of_property_read_bool(np, "cache-size"))
			++leaves;
		if (of_property_read_bool(np, "i-cache-size"))
			++leaves;
		if (of_property_read_bool(np, "d-cache-size"))
			++leaves;
		levels = level;
	}

	of_node_put(np);
	this_cpu_ci->num_levels = levels;
	this_cpu_ci->num_leaves = leaves;

	return 0;
}