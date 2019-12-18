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
struct device {TYPE_1__* pm_domain; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (struct device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct device*,int) ; 

void dev_pm_domain_detach(struct device *dev, bool power_off)
{
	if (dev->pm_domain && dev->pm_domain->detach)
		dev->pm_domain->detach(dev, power_off);
}