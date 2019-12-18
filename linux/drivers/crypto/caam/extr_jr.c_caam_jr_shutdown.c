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
struct device {int dummy; } ;
struct caam_drv_private_jr {int /*<<< orphan*/  irqtask; } ;

/* Variables and functions */
 int caam_reset_hw_jr (struct device*) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int caam_jr_shutdown(struct device *dev)
{
	struct caam_drv_private_jr *jrp = dev_get_drvdata(dev);
	int ret;

	ret = caam_reset_hw_jr(dev);

	tasklet_kill(&jrp->irqtask);

	return ret;
}