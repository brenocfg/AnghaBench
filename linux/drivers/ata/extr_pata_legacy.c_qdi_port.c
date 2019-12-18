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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct legacy_probe {int /*<<< orphan*/  private; } ;
struct legacy_data {int /*<<< orphan*/  timing; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/ * devm_request_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int qdi_port(struct platform_device *dev,
			struct legacy_probe *lp, struct legacy_data *ld)
{
	if (devm_request_region(&dev->dev, lp->private, 4, "qdi") == NULL)
		return -EBUSY;
	ld->timing = lp->private;
	return 0;
}