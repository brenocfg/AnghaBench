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
struct cache_info {int /*<<< orphan*/  shared_cpu_map; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_pr_args (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_shared_cpu_map(struct cache_info *this_leaf, char *buf)
{
	cpumask_t shared_cpu_map;

	cpumask_and(&shared_cpu_map,
				&this_leaf->shared_cpu_map, cpu_online_mask);
	return scnprintf(buf, PAGE_SIZE, "%*pb\n",
			 cpumask_pr_args(&shared_cpu_map));
}