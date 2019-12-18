#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int base; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  label; int /*<<< orphan*/  of_node; } ;
struct mcs814x_gpio_chip {TYPE_1__ chip; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  be32_to_cpup (unsigned int const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int gpiochip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct mcs814x_gpio_chip*) ; 
 struct mcs814x_gpio_chip* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs814x_gpio_direction_input ; 
 int /*<<< orphan*/  mcs814x_gpio_direction_output ; 
 int /*<<< orphan*/  mcs814x_gpio_get ; 
 int /*<<< orphan*/  mcs814x_gpio_set ; 
 unsigned int* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mcs814x_gpio_chip*) ; 

__attribute__((used)) static int mcs814x_gpio_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct mcs814x_gpio_chip *mcs814x_chip;
	int ret;
	const unsigned int *num_gpios;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	num_gpios = of_get_property(pdev->dev.of_node, "num-gpios", NULL);
	if (!num_gpios)
		dev_err(&pdev->dev, "FIXME: no num-gpios property\n");

	mcs814x_chip = kzalloc(sizeof(*mcs814x_chip), GFP_KERNEL);
	if (!mcs814x_chip)
		return -ENOMEM;

	mcs814x_chip->regs = devm_ioremap_resource(&pdev->dev, res);
	if (!mcs814x_chip->regs) {
		ret = -ENOMEM;
		goto out;
	}

	platform_set_drvdata(pdev, mcs814x_chip);

#ifdef CONFIG_OF_GPIO
	mcs814x_chip->chip.of_node = pdev->dev.of_node;
#endif

	mcs814x_chip->chip.label = pdev->name;
	mcs814x_chip->chip.get = mcs814x_gpio_get;
	mcs814x_chip->chip.set = mcs814x_gpio_set;
	mcs814x_chip->chip.direction_input = mcs814x_gpio_direction_input;
	mcs814x_chip->chip.direction_output = mcs814x_gpio_direction_output;
	mcs814x_chip->chip.ngpio = be32_to_cpup(num_gpios);
	/* we want dynamic base allocation */
	mcs814x_chip->chip.base = -1;

	ret = gpiochip_add(&mcs814x_chip->chip);
	if (ret) {
		dev_err(&pdev->dev, "failed to register gpiochip\n");
		goto out;
	}

	return 0;

out:
	platform_set_drvdata(pdev, NULL);
	kfree(mcs814x_chip);
	return ret;
}