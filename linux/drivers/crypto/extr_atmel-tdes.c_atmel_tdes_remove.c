#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ has_dma; } ;
struct atmel_tdes_dev {TYPE_1__ caps; int /*<<< orphan*/  queue_task; int /*<<< orphan*/  done_task; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ atmel_tdes ; 
 int /*<<< orphan*/  atmel_tdes_buff_cleanup (struct atmel_tdes_dev*) ; 
 int /*<<< orphan*/  atmel_tdes_dma_cleanup (struct atmel_tdes_dev*) ; 
 int /*<<< orphan*/  atmel_tdes_unregister_algs (struct atmel_tdes_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct atmel_tdes_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_tdes_remove(struct platform_device *pdev)
{
	struct atmel_tdes_dev *tdes_dd;

	tdes_dd = platform_get_drvdata(pdev);
	if (!tdes_dd)
		return -ENODEV;
	spin_lock(&atmel_tdes.lock);
	list_del(&tdes_dd->list);
	spin_unlock(&atmel_tdes.lock);

	atmel_tdes_unregister_algs(tdes_dd);

	tasklet_kill(&tdes_dd->done_task);
	tasklet_kill(&tdes_dd->queue_task);

	if (tdes_dd->caps.has_dma)
		atmel_tdes_dma_cleanup(tdes_dd);

	atmel_tdes_buff_cleanup(tdes_dd);

	return 0;
}