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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pmc_dev ; 
 int /*<<< orphan*/  pmc_regs ; 
 int /*<<< orphan*/  pmc_suspend_ops ; 
 int /*<<< orphan*/  suspend_set_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmc_probe(struct platform_device *ofdev)
{
	pmc_regs = of_iomap(ofdev->dev.of_node, 0);
	if (!pmc_regs)
		return -ENOMEM;

	pmc_dev = &ofdev->dev;
	suspend_set_ops(&pmc_suspend_ops);
	return 0;
}