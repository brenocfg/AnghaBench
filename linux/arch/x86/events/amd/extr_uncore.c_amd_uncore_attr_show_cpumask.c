#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmu {scalar_t__ type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_llc_active_mask ; 
 TYPE_2__ amd_llc_pmu ; 
 int /*<<< orphan*/  amd_nb_active_mask ; 
 TYPE_1__ amd_nb_pmu ; 
 int /*<<< orphan*/  cpumap_print_to_pagebuf (int,char*,int /*<<< orphan*/ *) ; 
 struct pmu* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static ssize_t amd_uncore_attr_show_cpumask(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	cpumask_t *active_mask;
	struct pmu *pmu = dev_get_drvdata(dev);

	if (pmu->type == amd_nb_pmu.type)
		active_mask = &amd_nb_active_mask;
	else if (pmu->type == amd_llc_pmu.type)
		active_mask = &amd_llc_active_mask;
	else
		return 0;

	return cpumap_print_to_pagebuf(true, buf, active_mask);
}