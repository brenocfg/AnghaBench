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
struct talitos_private {void** irq; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_driver_string (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (void*) ; 
 void* irq_of_parse_and_map (struct device_node*,int) ; 
 int request_irq (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  talitos1_interrupt_4ch ; 
 int /*<<< orphan*/  talitos2_interrupt_4ch ; 
 int /*<<< orphan*/  talitos2_interrupt_ch0_2 ; 
 int /*<<< orphan*/  talitos2_interrupt_ch1_3 ; 

__attribute__((used)) static int talitos_probe_irq(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct device_node *np = ofdev->dev.of_node;
	struct talitos_private *priv = dev_get_drvdata(dev);
	int err;
	bool is_sec1 = has_ftr_sec1(priv);

	priv->irq[0] = irq_of_parse_and_map(np, 0);
	if (!priv->irq[0]) {
		dev_err(dev, "failed to map irq\n");
		return -EINVAL;
	}
	if (is_sec1) {
		err = request_irq(priv->irq[0], talitos1_interrupt_4ch, 0,
				  dev_driver_string(dev), dev);
		goto primary_out;
	}

	priv->irq[1] = irq_of_parse_and_map(np, 1);

	/* get the primary irq line */
	if (!priv->irq[1]) {
		err = request_irq(priv->irq[0], talitos2_interrupt_4ch, 0,
				  dev_driver_string(dev), dev);
		goto primary_out;
	}

	err = request_irq(priv->irq[0], talitos2_interrupt_ch0_2, 0,
			  dev_driver_string(dev), dev);
	if (err)
		goto primary_out;

	/* get the secondary irq line */
	err = request_irq(priv->irq[1], talitos2_interrupt_ch1_3, 0,
			  dev_driver_string(dev), dev);
	if (err) {
		dev_err(dev, "failed to request secondary irq\n");
		irq_dispose_mapping(priv->irq[1]);
		priv->irq[1] = 0;
	}

	return err;

primary_out:
	if (err) {
		dev_err(dev, "failed to request primary irq\n");
		irq_dispose_mapping(priv->irq[0]);
		priv->irq[0] = 0;
	}

	return err;
}