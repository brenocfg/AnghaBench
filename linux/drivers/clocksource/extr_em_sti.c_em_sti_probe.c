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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct em_sti_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  rate; struct platform_device* pdev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_IRQPOLL ; 
 int IRQF_NOBALANCING ; 
 int IRQF_TIMER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct em_sti_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct em_sti_priv*) ; 
 int /*<<< orphan*/  em_sti_interrupt ; 
 int /*<<< orphan*/  em_sti_register_clockevent (struct em_sti_priv*) ; 
 int /*<<< orphan*/  em_sti_register_clocksource (struct em_sti_priv*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct em_sti_priv*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em_sti_probe(struct platform_device *pdev)
{
	struct em_sti_priv *p;
	struct resource *res;
	int irq;
	int ret;

	p = devm_kzalloc(&pdev->dev, sizeof(*p), GFP_KERNEL);
	if (p == NULL)
		return -ENOMEM;

	p->pdev = pdev;
	platform_set_drvdata(pdev, p);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	/* map memory, let base point to the STI instance */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	p->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(p->base))
		return PTR_ERR(p->base);

	ret = devm_request_irq(&pdev->dev, irq, em_sti_interrupt,
			       IRQF_TIMER | IRQF_IRQPOLL | IRQF_NOBALANCING,
			       dev_name(&pdev->dev), p);
	if (ret) {
		dev_err(&pdev->dev, "failed to request low IRQ\n");
		return ret;
	}

	/* get hold of clock */
	p->clk = devm_clk_get(&pdev->dev, "sclk");
	if (IS_ERR(p->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return PTR_ERR(p->clk);
	}

	ret = clk_prepare(p->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot prepare clock\n");
		return ret;
	}

	ret = clk_enable(p->clk);
	if (ret < 0) {
		dev_err(&p->pdev->dev, "cannot enable clock\n");
		clk_unprepare(p->clk);
		return ret;
	}
	p->rate = clk_get_rate(p->clk);
	clk_disable(p->clk);

	raw_spin_lock_init(&p->lock);
	em_sti_register_clockevent(p);
	em_sti_register_clocksource(p);
	return 0;
}