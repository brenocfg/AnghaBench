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
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_attr_group_match ; 
 int /*<<< orphan*/  devm_attr_group_remove ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void devm_device_remove_group(struct device *dev,
			      const struct attribute_group *grp)
{
	WARN_ON(devres_release(dev, devm_attr_group_remove,
			       devm_attr_group_match,
			       /* cast away const */ (void *)grp));
}