#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct max14577_muic_irq {int virq; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct max14577_muic_info {int muic_irqs_num; int /*<<< orphan*/  wq_detcable; TYPE_1__* dev; struct max14577* max14577; int /*<<< orphan*/  path_uart; int /*<<< orphan*/  status; int /*<<< orphan*/  path_usb; int /*<<< orphan*/  edev; struct max14577_muic_irq* muic_irqs; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  mutex; } ;
struct max14577 {int dev_type; int /*<<< orphan*/  regmap; int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_DEBOUNCE_TIME_25MS ; 
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CTRL1_SW_UART ; 
 int /*<<< orphan*/  CTRL1_SW_USB ; 
 int /*<<< orphan*/  DELAY_MS_DEFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX14577_CABLE_GROUP_ADC ; 
 int MAX14577_MUIC_ADC_FACTORY_MODE_UART_OFF ; 
 int /*<<< orphan*/  MAX14577_MUIC_REG_STATUS1 ; 
 int /*<<< orphan*/  MAX14577_REG_DEVICEID ; 
#define  MAXIM_DEVICE_TYPE_MAX14577 129 
#define  MAXIM_DEVICE_TYPE_MAX77836 128 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct max14577* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct max14577_muic_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct max14577_muic_info*) ; 
 int max14577_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max14577_extcon_cable ; 
 int /*<<< orphan*/  max14577_muic_detect_cable_wq ; 
 int max14577_muic_get_cable_type (struct max14577_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  max14577_muic_irq_handler ; 
 int /*<<< orphan*/  max14577_muic_irq_work ; 
 void* max14577_muic_irqs ; 
 int /*<<< orphan*/  max14577_muic_set_debounce_time (struct max14577_muic_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max14577_muic_set_path (struct max14577_muic_info*,int /*<<< orphan*/ ,int) ; 
 int max14577_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* max77836_muic_irqs ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max14577_muic_info*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int max14577_muic_probe(struct platform_device *pdev)
{
	struct max14577 *max14577 = dev_get_drvdata(pdev->dev.parent);
	struct max14577_muic_info *info;
	int delay_jiffies;
	int cable_type;
	bool attached;
	int ret;
	int i;
	u8 id;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = &pdev->dev;
	info->max14577 = max14577;

	platform_set_drvdata(pdev, info);
	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, max14577_muic_irq_work);

	switch (max14577->dev_type) {
	case MAXIM_DEVICE_TYPE_MAX77836:
		info->muic_irqs = max77836_muic_irqs;
		info->muic_irqs_num = ARRAY_SIZE(max77836_muic_irqs);
		break;
	case MAXIM_DEVICE_TYPE_MAX14577:
	default:
		info->muic_irqs = max14577_muic_irqs;
		info->muic_irqs_num = ARRAY_SIZE(max14577_muic_irqs);
	}

	/* Support irq domain for max14577 MUIC device */
	for (i = 0; i < info->muic_irqs_num; i++) {
		struct max14577_muic_irq *muic_irq = &info->muic_irqs[i];
		int virq = 0;

		virq = regmap_irq_get_virq(max14577->irq_data, muic_irq->irq);
		if (virq <= 0)
			return -EINVAL;
		muic_irq->virq = virq;

		ret = devm_request_threaded_irq(&pdev->dev, virq, NULL,
				max14577_muic_irq_handler,
				IRQF_NO_SUSPEND,
				muic_irq->name, info);
		if (ret) {
			dev_err(&pdev->dev,
				"failed: irq request (IRQ: %d, error :%d)\n",
				muic_irq->irq, ret);
			return ret;
		}
	}

	/* Initialize extcon device */
	info->edev = devm_extcon_dev_allocate(&pdev->dev,
					      max14577_extcon_cable);
	if (IS_ERR(info->edev)) {
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		return -ENOMEM;
	}

	ret = devm_extcon_dev_register(&pdev->dev, info->edev);
	if (ret) {
		dev_err(&pdev->dev, "failed to register extcon device\n");
		return ret;
	}

	/* Default h/w line path */
	info->path_usb = CTRL1_SW_USB;
	info->path_uart = CTRL1_SW_UART;
	delay_jiffies = msecs_to_jiffies(DELAY_MS_DEFAULT);

	/* Set initial path for UART when JIG is connected to get serial logs */
	ret = max14577_bulk_read(info->max14577->regmap,
			MAX14577_MUIC_REG_STATUS1, info->status, 2);
	if (ret) {
		dev_err(info->dev, "Cannot read STATUS registers\n");
		return ret;
	}
	cable_type = max14577_muic_get_cable_type(info, MAX14577_CABLE_GROUP_ADC,
					 &attached);
	if (attached && cable_type == MAX14577_MUIC_ADC_FACTORY_MODE_UART_OFF)
		max14577_muic_set_path(info, info->path_uart, true);

	/* Check revision number of MUIC device*/
	ret = max14577_read_reg(info->max14577->regmap,
			MAX14577_REG_DEVICEID, &id);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to read revision number\n");
		return ret;
	}
	dev_info(info->dev, "device ID : 0x%x\n", id);

	/* Set ADC debounce time */
	max14577_muic_set_debounce_time(info, ADC_DEBOUNCE_TIME_25MS);

	/*
	 * Detect accessory after completing the initialization of platform
	 *
	 * - Use delayed workqueue to detect cable state and then
	 * notify cable state to notifiee/platform through uevent.
	 * After completing the booting of platform, the extcon provider
	 * driver should notify cable state to upper layer.
	 */
	INIT_DELAYED_WORK(&info->wq_detcable, max14577_muic_detect_cable_wq);
	queue_delayed_work(system_power_efficient_wq, &info->wq_detcable,
			delay_jiffies);

	return ret;
}