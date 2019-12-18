#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAVAIL ; 
 int ENOENT ; 
 int /*<<< orphan*/  GPTU_ID ; 
 int GPTU_MAGIC ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  TIMER1A ; 
 int /*<<< orphan*/  TIMER1B ; 
 int /*<<< orphan*/  TIMER2A ; 
 int /*<<< orphan*/  TIMER2B ; 
 int /*<<< orphan*/  TIMER3A ; 
 int /*<<< orphan*/  TIMER3B ; 
 int /*<<< orphan*/  clk_disable (struct clk*) ; 
 int /*<<< orphan*/  clk_enable (struct clk*) ; 
 struct clk* clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clkdev_add_gptu (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 struct clk* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/  gptu_hwexit () ; 
 int /*<<< orphan*/  gptu_hwinit () ; 
 struct clk* gptu_membase ; 
 int gptu_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqres ; 
 int of_irq_to_resource_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gptu_probe(struct platform_device *pdev)
{
	struct clk *clk;
	struct resource *res;

	if (of_irq_to_resource_table(pdev->dev.of_node, irqres, 6) != 6) {
		dev_err(&pdev->dev, "Failed to get IRQ list\n");
		return -EINVAL;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	/* remap gptu register range */
	gptu_membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gptu_membase))
		return PTR_ERR(gptu_membase);

	/* enable our clock */
	clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk)) {
		dev_err(&pdev->dev, "Failed to get clock\n");
		return -ENOENT;
	}
	clk_enable(clk);

	/* power up the core */
	gptu_hwinit();

	/* the gptu has a ID register */
	if (((gptu_r32(GPTU_ID) >> 8) & 0xff) != GPTU_MAGIC) {
		dev_err(&pdev->dev, "Failed to find magic\n");
		gptu_hwexit();
		clk_disable(clk);
		clk_put(clk);
		return -ENAVAIL;
	}

	/* register the clocks */
	clkdev_add_gptu(&pdev->dev, "timer1a", TIMER1A);
	clkdev_add_gptu(&pdev->dev, "timer1b", TIMER1B);
	clkdev_add_gptu(&pdev->dev, "timer2a", TIMER2A);
	clkdev_add_gptu(&pdev->dev, "timer2b", TIMER2B);
	clkdev_add_gptu(&pdev->dev, "timer3a", TIMER3A);
	clkdev_add_gptu(&pdev->dev, "timer3b", TIMER3B);

	dev_info(&pdev->dev, "gptu: 6 timers loaded\n");

	return 0;
}