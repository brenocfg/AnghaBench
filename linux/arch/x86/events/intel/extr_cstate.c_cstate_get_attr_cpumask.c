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
struct pmu {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpumap_print_to_pagebuf (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstate_core_cpu_mask ; 
 struct pmu cstate_core_pmu ; 
 int /*<<< orphan*/  cstate_pkg_cpu_mask ; 
 struct pmu cstate_pkg_pmu ; 
 struct pmu* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static ssize_t cstate_get_attr_cpumask(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct pmu *pmu = dev_get_drvdata(dev);

	if (pmu == &cstate_core_pmu)
		return cpumap_print_to_pagebuf(true, buf, &cstate_core_cpu_mask);
	else if (pmu == &cstate_pkg_pmu)
		return cpumap_print_to_pagebuf(true, buf, &cstate_pkg_cpu_mask);
	else
		return 0;
}