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
struct device {int dummy; } ;
struct cpumask {int dummy; } ;
struct cacheinfo {struct cpumask shared_cpu_map; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpumap_print_to_pagebuf (int,char*,struct cpumask const*) ; 
 struct cacheinfo* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static ssize_t shared_cpumap_show_func(struct device *dev, bool list, char *buf)
{
	struct cacheinfo *this_leaf = dev_get_drvdata(dev);
	const struct cpumask *mask = &this_leaf->shared_cpu_map;

	return cpumap_print_to_pagebuf(list, buf, mask);
}