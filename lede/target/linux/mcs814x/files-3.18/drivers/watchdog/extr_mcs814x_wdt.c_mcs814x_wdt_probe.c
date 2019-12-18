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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int min_timeout; int max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct mcs814x_wdt {TYPE_1__ wdt_dev; int /*<<< orphan*/  regs; struct clk* clk; int /*<<< orphan*/  lock; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR_OR_NULL (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int WDT_MAX_VALUE ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcs814x_wdt*) ; 
 struct mcs814x_wdt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs814x_wdt_ident ; 
 int /*<<< orphan*/  mcs814x_wdt_ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mcs814x_wdt*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct mcs814x_wdt*) ; 

__attribute__((used)) static int mcs814x_wdt_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct mcs814x_wdt *wdt;
	int ret;
	struct clk *clk;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	clk = clk_get(NULL, "wdt");
	if (IS_ERR_OR_NULL(clk)) {
		dev_err(&pdev->dev, "failed to get watchdog clock\n");
		return PTR_ERR(clk);
	}

	wdt = kzalloc(sizeof(*wdt), GFP_KERNEL);
	if (!wdt) {
		ret = -ENOMEM;
		goto out_clk;
	}

	spin_lock_init(&wdt->lock);
	wdt->clk = clk;
	wdt->wdt_dev.info = &mcs814x_wdt_ident;
	wdt->wdt_dev.ops = &mcs814x_wdt_ops;
	wdt->wdt_dev.min_timeout = 1;
	/* approximately 10995 secs */
	wdt->wdt_dev.max_timeout = (WDT_MAX_VALUE / clk_get_rate(clk));

	platform_set_drvdata(pdev, wdt);

	/* only ioremap registers, because the register is shared */
	wdt->regs = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!wdt->regs) {
		ret = -ENOMEM;
		goto out;
	}

	watchdog_set_drvdata(&wdt->wdt_dev, wdt);

	ret = watchdog_register_device(&wdt->wdt_dev);
	if (ret) {
		dev_err(&pdev->dev, "cannot register watchdog: %d\n", ret);
		goto out;
	}

	dev_info(&pdev->dev, "registered\n");
	return 0;

out:
	platform_set_drvdata(pdev, NULL);
	kfree(wdt);
out_clk:
	clk_put(clk);
	return ret;
}