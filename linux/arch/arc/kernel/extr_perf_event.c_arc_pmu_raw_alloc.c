#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_2__ {void* raw_entry; scalar_t__ n_events; void* attrs; void* attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 TYPE_1__* arc_pmu ; 
 void* devm_kmalloc_array (struct device*,scalar_t__,int,int) ; 

__attribute__((used)) static int arc_pmu_raw_alloc(struct device *dev)
{
	arc_pmu->attr = devm_kmalloc_array(dev, arc_pmu->n_events + 1,
		sizeof(*arc_pmu->attr), GFP_KERNEL | __GFP_ZERO);
	if (!arc_pmu->attr)
		return -ENOMEM;

	arc_pmu->attrs = devm_kmalloc_array(dev, arc_pmu->n_events + 1,
		sizeof(*arc_pmu->attrs), GFP_KERNEL | __GFP_ZERO);
	if (!arc_pmu->attrs)
		return -ENOMEM;

	arc_pmu->raw_entry = devm_kmalloc_array(dev, arc_pmu->n_events,
		sizeof(*arc_pmu->raw_entry), GFP_KERNEL | __GFP_ZERO);
	if (!arc_pmu->raw_entry)
		return -ENOMEM;

	return 0;
}