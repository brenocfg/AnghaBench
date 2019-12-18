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
struct sahara_dev {int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  kthread; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dev_ptr ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 struct sahara_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sahara_unregister_algs (struct sahara_dev*) ; 

__attribute__((used)) static int sahara_remove(struct platform_device *pdev)
{
	struct sahara_dev *dev = platform_get_drvdata(pdev);

	kthread_stop(dev->kthread);

	sahara_unregister_algs(dev);

	clk_disable_unprepare(dev->clk_ipg);
	clk_disable_unprepare(dev->clk_ahb);

	dev_ptr = NULL;

	return 0;
}