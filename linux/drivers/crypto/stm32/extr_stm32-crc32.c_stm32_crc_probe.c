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
struct stm32_crc {int /*<<< orphan*/  clk; int /*<<< orphan*/  list; struct device* dev; int /*<<< orphan*/  regs; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRC_AUTOSUSPEND_DELAY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  algs ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 TYPE_1__ crc_list ; 
 int crypto_register_shashes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct stm32_crc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_crc*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_crc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct stm32_crc *crc;
	int ret;

	crc = devm_kzalloc(dev, sizeof(*crc), GFP_KERNEL);
	if (!crc)
		return -ENOMEM;

	crc->dev = dev;

	crc->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(crc->regs)) {
		dev_err(dev, "Cannot map CRC IO\n");
		return PTR_ERR(crc->regs);
	}

	crc->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(crc->clk)) {
		dev_err(dev, "Could not get clock\n");
		return PTR_ERR(crc->clk);
	}

	ret = clk_prepare_enable(crc->clk);
	if (ret) {
		dev_err(crc->dev, "Failed to enable clock\n");
		return ret;
	}

	pm_runtime_set_autosuspend_delay(dev, CRC_AUTOSUSPEND_DELAY);
	pm_runtime_use_autosuspend(dev);

	pm_runtime_get_noresume(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	platform_set_drvdata(pdev, crc);

	spin_lock(&crc_list.lock);
	list_add(&crc->list, &crc_list.dev_list);
	spin_unlock(&crc_list.lock);

	ret = crypto_register_shashes(algs, ARRAY_SIZE(algs));
	if (ret) {
		dev_err(dev, "Failed to register\n");
		clk_disable_unprepare(crc->clk);
		return ret;
	}

	dev_info(dev, "Initialized\n");

	pm_runtime_put_sync(dev);

	return 0;
}