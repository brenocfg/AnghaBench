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
struct resource {scalar_t__ start; } ;
struct pmc_type {scalar_t__ has_deep_sleep; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct pmc_type* data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IMMR_SYSCR_OFFSET ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 void* clock_regs ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct platform_device*) ; 
 scalar_t__ get_immrbase () ; 
 scalar_t__ has_deep_sleep ; 
 scalar_t__ immrbase ; 
 void* ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_pci_agent ; 
 scalar_t__ mpc83xx_is_pci_agent () ; 
 int /*<<< orphan*/  mpc83xx_set_agent () ; 
 int /*<<< orphan*/  mpc83xx_suspend_ops ; 
 int of_address_to_resource (struct device_node*,int,struct resource*) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct platform_device* pmc_dev ; 
 scalar_t__ pmc_irq ; 
 int /*<<< orphan*/  pmc_irq_handler ; 
 int /*<<< orphan*/  pmc_match ; 
 void* pmc_regs ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct platform_device*) ; 
 int /*<<< orphan*/  suspend_set_ops (int /*<<< orphan*/ *) ; 
 void* syscr_regs ; 

__attribute__((used)) static int pmc_probe(struct platform_device *ofdev)
{
	const struct of_device_id *match;
	struct device_node *np = ofdev->dev.of_node;
	struct resource res;
	const struct pmc_type *type;
	int ret = 0;

	match = of_match_device(pmc_match, &ofdev->dev);
	if (!match)
		return -EINVAL;

	type = match->data;

	if (!of_device_is_available(np))
		return -ENODEV;

	has_deep_sleep = type->has_deep_sleep;
	immrbase = get_immrbase();
	pmc_dev = ofdev;

	is_pci_agent = mpc83xx_is_pci_agent();
	if (is_pci_agent < 0)
		return is_pci_agent;

	ret = of_address_to_resource(np, 0, &res);
	if (ret)
		return -ENODEV;

	pmc_irq = irq_of_parse_and_map(np, 0);
	if (pmc_irq) {
		ret = request_irq(pmc_irq, pmc_irq_handler, IRQF_SHARED,
		                  "pmc", ofdev);

		if (ret)
			return -EBUSY;
	}

	pmc_regs = ioremap(res.start, sizeof(*pmc_regs));

	if (!pmc_regs) {
		ret = -ENOMEM;
		goto out;
	}

	ret = of_address_to_resource(np, 1, &res);
	if (ret) {
		ret = -ENODEV;
		goto out_pmc;
	}

	clock_regs = ioremap(res.start, sizeof(*clock_regs));

	if (!clock_regs) {
		ret = -ENOMEM;
		goto out_pmc;
	}

	if (has_deep_sleep) {
		syscr_regs = ioremap(immrbase + IMMR_SYSCR_OFFSET,
				     sizeof(*syscr_regs));
		if (!syscr_regs) {
			ret = -ENOMEM;
			goto out_syscr;
		}
	}

	if (is_pci_agent)
		mpc83xx_set_agent();

	suspend_set_ops(&mpc83xx_suspend_ops);
	return 0;

out_syscr:
	iounmap(clock_regs);
out_pmc:
	iounmap(pmc_regs);
out:
	if (pmc_irq)
		free_irq(pmc_irq, ofdev);

	return ret;
}