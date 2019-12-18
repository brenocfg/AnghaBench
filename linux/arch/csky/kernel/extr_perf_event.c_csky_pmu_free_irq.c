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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_events; struct platform_device* plat_device; } ;

/* Variables and functions */
 TYPE_1__ csky_pmu ; 
 int /*<<< orphan*/  free_percpu_irq (int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csky_pmu_free_irq(void)
{
	int irq;
	struct platform_device *pmu_device = csky_pmu.plat_device;

	irq = platform_get_irq(pmu_device, 0);
	if (irq >= 0)
		free_percpu_irq(irq, this_cpu_ptr(csky_pmu.hw_events));
}