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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct axp288_extcon_info {int* irq; int /*<<< orphan*/  role_work; scalar_t__ role_sw; TYPE_1__ id_nb; scalar_t__ id_extcon; int /*<<< orphan*/  regmap_irqc; scalar_t__ edev; int /*<<< orphan*/  vbus_attach; int /*<<< orphan*/  previous_cable; int /*<<< orphan*/  regmap; struct device* dev; } ;
struct axp20x_dev {int /*<<< orphan*/  regmap_irqc; int /*<<< orphan*/  regmap; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int EXTCON_IRQ_END ; 
 int /*<<< orphan*/  EXTCON_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 struct acpi_device* acpi_dev_get_first_match_dev (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acpi_dev_name (struct acpi_device*) ; 
 int /*<<< orphan*/  axp288_extcon_cables ; 
 int /*<<< orphan*/  axp288_extcon_enable (struct axp288_extcon_info*) ; 
 int /*<<< orphan*/  axp288_extcon_id_evt ; 
 int /*<<< orphan*/  axp288_extcon_isr ; 
 int /*<<< orphan*/  axp288_extcon_log_rsi (struct axp288_extcon_info*) ; 
 int /*<<< orphan*/  axp288_get_vbus_attach (struct axp288_extcon_info*) ; 
 int /*<<< orphan*/  axp288_put_role_sw ; 
 int /*<<< orphan*/  axp288_usb_role_work ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct axp20x_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct axp288_extcon_info*) ; 
 scalar_t__ devm_extcon_dev_allocate (struct device*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (struct device*,scalar_t__) ; 
 int devm_extcon_register_notifier_all (struct device*,scalar_t__,TYPE_1__*) ; 
 struct axp288_extcon_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct axp288_extcon_info*) ; 
 scalar_t__ extcon_get_extcon_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct axp288_extcon_info*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_long_wq ; 
 scalar_t__ usb_role_switch_get (struct device*) ; 

__attribute__((used)) static int axp288_extcon_probe(struct platform_device *pdev)
{
	struct axp288_extcon_info *info;
	struct axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	struct device *dev = &pdev->dev;
	struct acpi_device *adev;
	int ret, i, pirq;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = &pdev->dev;
	info->regmap = axp20x->regmap;
	info->regmap_irqc = axp20x->regmap_irqc;
	info->previous_cable = EXTCON_NONE;
	INIT_WORK(&info->role_work, axp288_usb_role_work);
	info->id_nb.notifier_call = axp288_extcon_id_evt;

	platform_set_drvdata(pdev, info);

	info->role_sw = usb_role_switch_get(dev);
	if (IS_ERR(info->role_sw))
		return PTR_ERR(info->role_sw);
	if (info->role_sw) {
		ret = devm_add_action_or_reset(dev, axp288_put_role_sw, info);
		if (ret)
			return ret;

		adev = acpi_dev_get_first_match_dev("INT3496", NULL, -1);
		if (adev) {
			info->id_extcon = extcon_get_extcon_dev(acpi_dev_name(adev));
			put_device(&adev->dev);
			if (!info->id_extcon)
				return -EPROBE_DEFER;

			dev_info(dev, "controlling USB role\n");
		} else {
			dev_info(dev, "controlling USB role based on Vbus presence\n");
		}
	}

	info->vbus_attach = axp288_get_vbus_attach(info);

	axp288_extcon_log_rsi(info);

	/* Initialize extcon device */
	info->edev = devm_extcon_dev_allocate(&pdev->dev,
					      axp288_extcon_cables);
	if (IS_ERR(info->edev)) {
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		return PTR_ERR(info->edev);
	}

	/* Register extcon device */
	ret = devm_extcon_dev_register(&pdev->dev, info->edev);
	if (ret) {
		dev_err(&pdev->dev, "failed to register extcon device\n");
		return ret;
	}

	for (i = 0; i < EXTCON_IRQ_END; i++) {
		pirq = platform_get_irq(pdev, i);
		if (pirq < 0)
			return pirq;

		info->irq[i] = regmap_irq_get_virq(info->regmap_irqc, pirq);
		if (info->irq[i] < 0) {
			dev_err(&pdev->dev,
				"failed to get virtual interrupt=%d\n", pirq);
			ret = info->irq[i];
			return ret;
		}

		ret = devm_request_threaded_irq(&pdev->dev, info->irq[i],
				NULL, axp288_extcon_isr,
				IRQF_ONESHOT | IRQF_NO_SUSPEND,
				pdev->name, info);
		if (ret) {
			dev_err(&pdev->dev, "failed to request interrupt=%d\n",
							info->irq[i]);
			return ret;
		}
	}

	if (info->id_extcon) {
		ret = devm_extcon_register_notifier_all(dev, info->id_extcon,
							&info->id_nb);
		if (ret)
			return ret;
	}

	/* Make sure the role-sw is set correctly before doing BC detection */
	if (info->role_sw) {
		queue_work(system_long_wq, &info->role_work);
		flush_work(&info->role_work);
	}

	/* Start charger cable type detection */
	axp288_extcon_enable(info);

	return 0;
}