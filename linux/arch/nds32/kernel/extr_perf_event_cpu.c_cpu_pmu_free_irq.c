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
struct nds32_pmu {struct platform_device* plat_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct nds32_pmu*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_pmu_free_irq(struct nds32_pmu *cpu_pmu)
{
	int irq;
	struct platform_device *pmu_device = cpu_pmu->plat_device;

	irq = platform_get_irq(pmu_device, 0);
	if (irq >= 0)
		free_irq(irq, cpu_pmu);
}