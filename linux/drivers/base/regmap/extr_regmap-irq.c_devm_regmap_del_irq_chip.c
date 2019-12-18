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
struct regmap_irq_chip_data {int irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_regmap_irq_chip_match ; 
 int /*<<< orphan*/  devm_regmap_irq_chip_release ; 
 int devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regmap_irq_chip_data*) ; 

void devm_regmap_del_irq_chip(struct device *dev, int irq,
			      struct regmap_irq_chip_data *data)
{
	int rc;

	WARN_ON(irq != data->irq);
	rc = devres_release(dev, devm_regmap_irq_chip_release,
			    devm_regmap_irq_chip_match, data);

	if (rc != 0)
		WARN_ON(rc);
}