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
struct stm32_timers {int /*<<< orphan*/  max_arr; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int num_counts; struct stm32_timer_cnt* priv; int /*<<< orphan*/  num_signals; int /*<<< orphan*/  signals; int /*<<< orphan*/ * counts; int /*<<< orphan*/ * ops; struct device* parent; int /*<<< orphan*/  name; } ;
struct stm32_timer_cnt {TYPE_1__ counter; int /*<<< orphan*/  ceiling; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct stm32_timers*) ; 
 struct stm32_timers* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_counter_register (struct device*,TYPE_1__*) ; 
 struct stm32_timer_cnt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_counts ; 
 int /*<<< orphan*/  stm32_signals ; 
 int /*<<< orphan*/  stm32_timer_cnt_ops ; 

__attribute__((used)) static int stm32_timer_cnt_probe(struct platform_device *pdev)
{
	struct stm32_timers *ddata = dev_get_drvdata(pdev->dev.parent);
	struct device *dev = &pdev->dev;
	struct stm32_timer_cnt *priv;

	if (IS_ERR_OR_NULL(ddata))
		return -EINVAL;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->ceiling = ddata->max_arr;

	priv->counter.name = dev_name(dev);
	priv->counter.parent = dev;
	priv->counter.ops = &stm32_timer_cnt_ops;
	priv->counter.counts = &stm32_counts;
	priv->counter.num_counts = 1;
	priv->counter.signals = stm32_signals;
	priv->counter.num_signals = ARRAY_SIZE(stm32_signals);
	priv->counter.priv = priv;

	/* Register Counter device */
	return devm_counter_register(dev, &priv->counter);
}