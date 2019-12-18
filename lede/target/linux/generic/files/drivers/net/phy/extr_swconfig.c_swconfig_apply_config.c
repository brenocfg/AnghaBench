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
struct switch_val {int dummy; } ;
struct switch_dev {TYPE_1__* ops; } ;
struct switch_attr {int dummy; } ;
struct TYPE_2__ {int (* apply_config ) (struct switch_dev*) ;} ;

/* Variables and functions */
 int stub1 (struct switch_dev*) ; 

__attribute__((used)) static int
swconfig_apply_config(struct switch_dev *dev, const struct switch_attr *attr,
			struct switch_val *val)
{
	/* don't complain if not supported by the switch driver */
	if (!dev->ops->apply_config)
		return 0;

	return dev->ops->apply_config(dev);
}