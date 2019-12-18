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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct caam_drv_private_jr {int /*<<< orphan*/  list_node; int /*<<< orphan*/  tfm_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  jr_alloc_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int caam_jr_shutdown (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 
 TYPE_1__ driver_data ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_algs () ; 

__attribute__((used)) static int caam_jr_remove(struct platform_device *pdev)
{
	int ret;
	struct device *jrdev;
	struct caam_drv_private_jr *jrpriv;

	jrdev = &pdev->dev;
	jrpriv = dev_get_drvdata(jrdev);

	/*
	 * Return EBUSY if job ring already allocated.
	 */
	if (atomic_read(&jrpriv->tfm_count)) {
		dev_err(jrdev, "Device is busy\n");
		return -EBUSY;
	}

	/* Unregister JR-based RNG & crypto algorithms */
	unregister_algs();

	/* Remove the node from Physical JobR list maintained by driver */
	spin_lock(&driver_data.jr_alloc_lock);
	list_del(&jrpriv->list_node);
	spin_unlock(&driver_data.jr_alloc_lock);

	/* Release ring */
	ret = caam_jr_shutdown(jrdev);
	if (ret)
		dev_err(jrdev, "Failed to shut down job ring\n");

	return ret;
}