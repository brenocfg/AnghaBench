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
struct stratix10_svc_controller {int /*<<< orphan*/  node; scalar_t__ genpool; int /*<<< orphan*/ * task; int /*<<< orphan*/  svc_fifo; } ;
struct stratix10_svc {int /*<<< orphan*/  stratix10_svc_rsu; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct stratix10_svc* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct stratix10_svc_controller* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int stratix10_svc_drv_remove(struct platform_device *pdev)
{
	struct stratix10_svc *svc = dev_get_drvdata(&pdev->dev);
	struct stratix10_svc_controller *ctrl = platform_get_drvdata(pdev);

	platform_device_unregister(svc->stratix10_svc_rsu);

	kfifo_free(&ctrl->svc_fifo);
	if (ctrl->task) {
		kthread_stop(ctrl->task);
		ctrl->task = NULL;
	}
	if (ctrl->genpool)
		gen_pool_destroy(ctrl->genpool);
	list_del(&ctrl->node);

	return 0;
}