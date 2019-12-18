#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct max8997_platform_data {struct max8997_muic_platform_data* muic_pdata; } ;
struct max8997_muic_platform_data {int num_init_data; scalar_t__ detcable_delay_ms; void* path_usb; void* path_uart; TYPE_1__* init_data; } ;
struct max8997_muic_irq {unsigned int virq; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct max8997_muic_info {int /*<<< orphan*/  wq_detcable; void* path_uart; TYPE_2__* dev; int /*<<< orphan*/  status; int /*<<< orphan*/  muic; void* path_usb; int /*<<< orphan*/  edev; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  mutex; } ;
struct max8997_dev {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  muic; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_DEBOUNCE_TIME_25MS ; 
 int ARRAY_SIZE (struct max8997_muic_irq*) ; 
 void* CONTROL1_SW_UART ; 
 void* CONTROL1_SW_USB ; 
 scalar_t__ DELAY_MS_DEFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX8997_CABLE_GROUP_ADC ; 
 int MAX8997_MUIC_ADC_FACTORY_MODE_UART_OFF ; 
 int /*<<< orphan*/  MAX8997_MUIC_REG_STATUS1 ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct max8997_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct max8997_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct max8997_muic_info* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct max8997_muic_info*) ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max8997_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8997_extcon_cable ; 
 int /*<<< orphan*/  max8997_muic_detect_cable_wq ; 
 int max8997_muic_get_cable_type (struct max8997_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  max8997_muic_irq_handler ; 
 int /*<<< orphan*/  max8997_muic_irq_work ; 
 int /*<<< orphan*/  max8997_muic_set_debounce_time (struct max8997_muic_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8997_muic_set_path (struct max8997_muic_info*,void*,int) ; 
 int /*<<< orphan*/  max8997_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msecs_to_jiffies (scalar_t__) ; 
 struct max8997_muic_irq* muic_irqs ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8997_muic_info*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int request_threaded_irq (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct max8997_muic_info*) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int max8997_muic_probe(struct platform_device *pdev)
{
	struct max8997_dev *max8997 = dev_get_drvdata(pdev->dev.parent);
	struct max8997_platform_data *pdata = dev_get_platdata(max8997->dev);
	struct max8997_muic_info *info;
	int delay_jiffies;
	int cable_type;
	bool attached;
	int ret, i;

	info = devm_kzalloc(&pdev->dev, sizeof(struct max8997_muic_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = &pdev->dev;
	info->muic = max8997->muic;

	platform_set_drvdata(pdev, info);
	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, max8997_muic_irq_work);

	for (i = 0; i < ARRAY_SIZE(muic_irqs); i++) {
		struct max8997_muic_irq *muic_irq = &muic_irqs[i];
		unsigned int virq = 0;

		virq = irq_create_mapping(max8997->irq_domain, muic_irq->irq);
		if (!virq) {
			ret = -EINVAL;
			goto err_irq;
		}
		muic_irq->virq = virq;

		ret = request_threaded_irq(virq, NULL,
				max8997_muic_irq_handler,
				IRQF_NO_SUSPEND,
				muic_irq->name, info);
		if (ret) {
			dev_err(&pdev->dev,
				"failed: irq request (IRQ: %d, error :%d)\n",
				muic_irq->irq, ret);
			goto err_irq;
		}
	}

	/* External connector */
	info->edev = devm_extcon_dev_allocate(&pdev->dev, max8997_extcon_cable);
	if (IS_ERR(info->edev)) {
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		ret = -ENOMEM;
		goto err_irq;
	}

	ret = devm_extcon_dev_register(&pdev->dev, info->edev);
	if (ret) {
		dev_err(&pdev->dev, "failed to register extcon device\n");
		goto err_irq;
	}

	if (pdata && pdata->muic_pdata) {
		struct max8997_muic_platform_data *muic_pdata
			= pdata->muic_pdata;

		/* Initialize registers according to platform data */
		for (i = 0; i < muic_pdata->num_init_data; i++) {
			max8997_write_reg(info->muic,
					muic_pdata->init_data[i].addr,
					muic_pdata->init_data[i].data);
		}

		/*
		 * Default usb/uart path whether UART/USB or AUX_UART/AUX_USB
		 * h/w path of COMP2/COMN1 on CONTROL1 register.
		 */
		if (muic_pdata->path_uart)
			info->path_uart = muic_pdata->path_uart;
		else
			info->path_uart = CONTROL1_SW_UART;

		if (muic_pdata->path_usb)
			info->path_usb = muic_pdata->path_usb;
		else
			info->path_usb = CONTROL1_SW_USB;

		/*
		 * Default delay time for detecting cable state
		 * after certain time.
		 */
		if (muic_pdata->detcable_delay_ms)
			delay_jiffies =
				msecs_to_jiffies(muic_pdata->detcable_delay_ms);
		else
			delay_jiffies = msecs_to_jiffies(DELAY_MS_DEFAULT);
	} else {
		info->path_uart = CONTROL1_SW_UART;
		info->path_usb = CONTROL1_SW_USB;
		delay_jiffies = msecs_to_jiffies(DELAY_MS_DEFAULT);
	}

	/* Set initial path for UART when JIG is connected to get serial logs */
	ret = max8997_bulk_read(info->muic, MAX8997_MUIC_REG_STATUS1,
				2, info->status);
	if (ret) {
		dev_err(info->dev, "failed to read MUIC register\n");
		return ret;
	}
	cable_type = max8997_muic_get_cable_type(info,
					   MAX8997_CABLE_GROUP_ADC, &attached);
	if (attached && cable_type == MAX8997_MUIC_ADC_FACTORY_MODE_UART_OFF)
		max8997_muic_set_path(info, info->path_uart, true);

	/* Set ADC debounce time */
	max8997_muic_set_debounce_time(info, ADC_DEBOUNCE_TIME_25MS);

	/*
	 * Detect accessory after completing the initialization of platform
	 *
	 * - Use delayed workqueue to detect cable state and then
	 * notify cable state to notifiee/platform through uevent.
	 * After completing the booting of platform, the extcon provider
	 * driver should notify cable state to upper layer.
	 */
	INIT_DELAYED_WORK(&info->wq_detcable, max8997_muic_detect_cable_wq);
	queue_delayed_work(system_power_efficient_wq, &info->wq_detcable,
			delay_jiffies);

	return 0;

err_irq:
	while (--i >= 0)
		free_irq(muic_irqs[i].virq, info);
	return ret;
}