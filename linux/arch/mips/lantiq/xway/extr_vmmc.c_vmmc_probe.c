#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int CP1_SIZE ; 
 scalar_t__ CPHYSADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OF_GPIO_ACTIVE_LOW ; 
 void* cp1_base ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int) ; 
 scalar_t__ gpio_request (int,char*) ; 
 int of_get_gpio_flags (int /*<<< orphan*/ ,int,int*) ; 
 int of_gpio_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmmc_probe(struct platform_device *pdev)
{
#define CP1_SIZE       (1 << 20)
	int gpio_count;
	dma_addr_t dma;

	cp1_base =
		(void *) CPHYSADDR(dma_alloc_coherent(&pdev->dev, CP1_SIZE,
						    &dma, GFP_KERNEL));

	gpio_count = of_gpio_count(pdev->dev.of_node);
	while (gpio_count > 0) {
		enum of_gpio_flags flags;
		int gpio = of_get_gpio_flags(pdev->dev.of_node,
					     --gpio_count, &flags);
		if (gpio_request(gpio, "vmmc-relay"))
			continue;
		dev_info(&pdev->dev, "requested GPIO %d\n", gpio);
		gpio_direction_output(gpio,
				      (flags & OF_GPIO_ACTIVE_LOW) ? (0) : (1));
	}

	dev_info(&pdev->dev, "reserved %dMB at 0x%p", CP1_SIZE >> 20, cp1_base);

	return 0;
}