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
struct qce_device {int /*<<< orphan*/  core; int /*<<< orphan*/  iface; int /*<<< orphan*/  bus; int /*<<< orphan*/  dma; int /*<<< orphan*/  done_tasklet; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qce_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qce_dma_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qce_unregister_algs (struct qce_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qce_crypto_remove(struct platform_device *pdev)
{
	struct qce_device *qce = platform_get_drvdata(pdev);

	tasklet_kill(&qce->done_tasklet);
	qce_unregister_algs(qce);
	qce_dma_release(&qce->dma);
	clk_disable_unprepare(qce->bus);
	clk_disable_unprepare(qce->iface);
	clk_disable_unprepare(qce->core);
	return 0;
}