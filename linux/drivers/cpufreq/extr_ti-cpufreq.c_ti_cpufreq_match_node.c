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
struct of_device_id {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_path (char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  ti_cpufreq_of_match ; 

__attribute__((used)) static const struct of_device_id *ti_cpufreq_match_node(void)
{
	struct device_node *np;
	const struct of_device_id *match;

	np = of_find_node_by_path("/");
	match = of_match_node(ti_cpufreq_of_match, np);
	of_node_put(np);

	return match;
}