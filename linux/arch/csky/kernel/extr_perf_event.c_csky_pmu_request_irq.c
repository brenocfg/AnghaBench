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
struct platform_device {int /*<<< orphan*/  num_resources; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_2__ {int /*<<< orphan*/  hw_events; struct platform_device* plat_device; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__ csky_pmu ; 
 scalar_t__ csky_pmu_irq ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_possible_cpus () ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int request_percpu_irq (scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csky_pmu_request_irq(irq_handler_t handler)
{
	int err, irqs;
	struct platform_device *pmu_device = csky_pmu.plat_device;

	if (!pmu_device)
		return -ENODEV;

	irqs = min(pmu_device->num_resources, num_possible_cpus());
	if (irqs < 1) {
		pr_err("no irqs for PMUs defined\n");
		return -ENODEV;
	}

	csky_pmu_irq = platform_get_irq(pmu_device, 0);
	if (csky_pmu_irq < 0)
		return -ENODEV;
	err = request_percpu_irq(csky_pmu_irq, handler, "csky-pmu",
				 this_cpu_ptr(csky_pmu.hw_events));
	if (err) {
		pr_err("unable to request IRQ%d for CSKY PMU counters\n",
		       csky_pmu_irq);
		return err;
	}

	return 0;
}