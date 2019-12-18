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
struct platform_device {int dummy; } ;
struct img_hash_dev {int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  hash_clk; int /*<<< orphan*/  dma_lch; int /*<<< orphan*/  dma_task; int /*<<< orphan*/  done_task; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 TYPE_1__ img_hash ; 
 int /*<<< orphan*/  img_unregister_algs (struct img_hash_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct img_hash_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_hash_remove(struct platform_device *pdev)
{
	struct img_hash_dev *hdev;

	hdev = platform_get_drvdata(pdev);
	spin_lock(&img_hash.lock);
	list_del(&hdev->list);
	spin_unlock(&img_hash.lock);

	img_unregister_algs(hdev);

	tasklet_kill(&hdev->done_task);
	tasklet_kill(&hdev->dma_task);

	dma_release_channel(hdev->dma_lch);

	clk_disable_unprepare(hdev->hash_clk);
	clk_disable_unprepare(hdev->sys_clk);

	return 0;
}