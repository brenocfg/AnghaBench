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
typedef  int /*<<< orphan*/  u32 ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct ipmi_smi_powernv {scalar_t__ irq; struct ipmi_smi_powernv* opal_msg; int /*<<< orphan*/  interface_id; int /*<<< orphan*/  msg_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IPMI_MAX_MSG_LENGTH ; 
 int /*<<< orphan*/  IRQ_TYPE_LEVEL_HIGH ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ipmi_smi_powernv*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct ipmi_smi_powernv*) ; 
 struct ipmi_smi_powernv* devm_kmalloc (struct device*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ipmi_smi_powernv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ipmi_smi_powernv*) ; 
 int /*<<< orphan*/  ipmi_opal_event ; 
 int /*<<< orphan*/  ipmi_powernv_smi_handlers ; 
 int ipmi_register_smi (int /*<<< orphan*/ *,struct ipmi_smi_powernv*,struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 scalar_t__ irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ opal_event_request (int /*<<< orphan*/ ) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ipmi_smi_powernv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmi_powernv_probe(struct platform_device *pdev)
{
	struct ipmi_smi_powernv *ipmi;
	struct device *dev;
	u32 prop;
	int rc;

	if (!pdev || !pdev->dev.of_node)
		return -ENODEV;

	dev = &pdev->dev;

	ipmi = devm_kzalloc(dev, sizeof(*ipmi), GFP_KERNEL);
	if (!ipmi)
		return -ENOMEM;

	spin_lock_init(&ipmi->msg_lock);

	rc = of_property_read_u32(dev->of_node, "ibm,ipmi-interface-id",
			&prop);
	if (rc) {
		dev_warn(dev, "No interface ID property\n");
		goto err_free;
	}
	ipmi->interface_id = prop;

	rc = of_property_read_u32(dev->of_node, "interrupts", &prop);
	if (rc) {
		dev_warn(dev, "No interrupts property\n");
		goto err_free;
	}

	ipmi->irq = irq_of_parse_and_map(dev->of_node, 0);
	if (!ipmi->irq) {
		dev_info(dev, "Unable to map irq from device tree\n");
		ipmi->irq = opal_event_request(prop);
	}

	rc = request_irq(ipmi->irq, ipmi_opal_event, IRQ_TYPE_LEVEL_HIGH,
			 "opal-ipmi", ipmi);
	if (rc) {
		dev_warn(dev, "Unable to request irq\n");
		goto err_dispose;
	}

	ipmi->opal_msg = devm_kmalloc(dev,
			sizeof(*ipmi->opal_msg) + IPMI_MAX_MSG_LENGTH,
			GFP_KERNEL);
	if (!ipmi->opal_msg) {
		rc = -ENOMEM;
		goto err_unregister;
	}

	rc = ipmi_register_smi(&ipmi_powernv_smi_handlers, ipmi, dev, 0);
	if (rc) {
		dev_warn(dev, "IPMI SMI registration failed (%d)\n", rc);
		goto err_free_msg;
	}

	dev_set_drvdata(dev, ipmi);
	return 0;

err_free_msg:
	devm_kfree(dev, ipmi->opal_msg);
err_unregister:
	free_irq(ipmi->irq, ipmi);
err_dispose:
	irq_dispose_mapping(ipmi->irq);
err_free:
	devm_kfree(dev, ipmi);
	return rc;
}