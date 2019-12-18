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
struct stm32_hash_dev {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; scalar_t__ dma_lch; int /*<<< orphan*/  list; int /*<<< orphan*/  engine; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_engine_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct stm32_hash_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ stm32_hash ; 
 int /*<<< orphan*/  stm32_hash_unregister_algs (struct stm32_hash_dev*) ; 

__attribute__((used)) static int stm32_hash_remove(struct platform_device *pdev)
{
	struct stm32_hash_dev *hdev;
	int ret;

	hdev = platform_get_drvdata(pdev);
	if (!hdev)
		return -ENODEV;

	ret = pm_runtime_get_sync(hdev->dev);
	if (ret < 0)
		return ret;

	stm32_hash_unregister_algs(hdev);

	crypto_engine_exit(hdev->engine);

	spin_lock(&stm32_hash.lock);
	list_del(&hdev->list);
	spin_unlock(&stm32_hash.lock);

	if (hdev->dma_lch)
		dma_release_channel(hdev->dma_lch);

	pm_runtime_disable(hdev->dev);
	pm_runtime_put_noidle(hdev->dev);

	clk_disable_unprepare(hdev->clk);

	return 0;
}