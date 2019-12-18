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
struct atmel_aes_dev {int /*<<< orphan*/  iclk; int /*<<< orphan*/  queue_task; int /*<<< orphan*/  done_task; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__ atmel_aes ; 
 int /*<<< orphan*/  atmel_aes_buff_cleanup (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_dma_cleanup (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_unregister_algs (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct atmel_aes_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_aes_remove(struct platform_device *pdev)
{
	struct atmel_aes_dev *aes_dd;

	aes_dd = platform_get_drvdata(pdev);
	if (!aes_dd)
		return -ENODEV;
	spin_lock(&atmel_aes.lock);
	list_del(&aes_dd->list);
	spin_unlock(&atmel_aes.lock);

	atmel_aes_unregister_algs(aes_dd);

	tasklet_kill(&aes_dd->done_task);
	tasklet_kill(&aes_dd->queue_task);

	atmel_aes_dma_cleanup(aes_dd);
	atmel_aes_buff_cleanup(aes_dd);

	clk_unprepare(aes_dd->iclk);

	return 0;
}