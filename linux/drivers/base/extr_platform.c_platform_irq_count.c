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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int __platform_get_irq (struct platform_device*,int) ; 

int platform_irq_count(struct platform_device *dev)
{
	int ret, nr = 0;

	while ((ret = __platform_get_irq(dev, nr)) >= 0)
		nr++;

	if (ret == -EPROBE_DEFER)
		return ret;

	return nr;
}