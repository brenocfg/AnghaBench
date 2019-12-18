#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sm5502_muic_info {int num_muic_irqs; int /*<<< orphan*/  wq_detcable; TYPE_1__* dev; int /*<<< orphan*/  edev; int /*<<< orphan*/  irq_data; struct muic_irq* muic_irqs; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  mutex; void* num_reg_data; void* reg_data; struct i2c_client* i2c; } ;
struct muic_irq {int virq; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  DELAY_MS_DEFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct sm5502_muic_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sm5502_muic_info*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sm5502_muic_info*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm5502_extcon_cable ; 
 int /*<<< orphan*/  sm5502_init_dev_type (struct sm5502_muic_info*) ; 
 int /*<<< orphan*/  sm5502_muic_detect_cable_wq ; 
 int /*<<< orphan*/  sm5502_muic_irq_chip ; 
 int /*<<< orphan*/  sm5502_muic_irq_handler ; 
 int /*<<< orphan*/  sm5502_muic_irq_work ; 
 void* sm5502_muic_irqs ; 
 int /*<<< orphan*/  sm5502_muic_regmap_config ; 
 void* sm5502_reg_data ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int sm5022_muic_i2c_probe(struct i2c_client *i2c,
				 const struct i2c_device_id *id)
{
	struct device_node *np = i2c->dev.of_node;
	struct sm5502_muic_info *info;
	int i, ret, irq_flags;

	if (!np)
		return -EINVAL;

	info = devm_kzalloc(&i2c->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	i2c_set_clientdata(i2c, info);

	info->dev = &i2c->dev;
	info->i2c = i2c;
	info->irq = i2c->irq;
	info->muic_irqs = sm5502_muic_irqs;
	info->num_muic_irqs = ARRAY_SIZE(sm5502_muic_irqs);
	info->reg_data = sm5502_reg_data;
	info->num_reg_data = ARRAY_SIZE(sm5502_reg_data);

	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, sm5502_muic_irq_work);

	info->regmap = devm_regmap_init_i2c(i2c, &sm5502_muic_regmap_config);
	if (IS_ERR(info->regmap)) {
		ret = PTR_ERR(info->regmap);
		dev_err(info->dev, "failed to allocate register map: %d\n",
				   ret);
		return ret;
	}

	/* Support irq domain for SM5502 MUIC device */
	irq_flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT | IRQF_SHARED;
	ret = regmap_add_irq_chip(info->regmap, info->irq, irq_flags, 0,
				  &sm5502_muic_irq_chip, &info->irq_data);
	if (ret != 0) {
		dev_err(info->dev, "failed to request IRQ %d: %d\n",
				    info->irq, ret);
		return ret;
	}

	for (i = 0; i < info->num_muic_irqs; i++) {
		struct muic_irq *muic_irq = &info->muic_irqs[i];
		int virq = 0;

		virq = regmap_irq_get_virq(info->irq_data, muic_irq->irq);
		if (virq <= 0)
			return -EINVAL;
		muic_irq->virq = virq;

		ret = devm_request_threaded_irq(info->dev, virq, NULL,
						sm5502_muic_irq_handler,
						IRQF_NO_SUSPEND | IRQF_ONESHOT,
						muic_irq->name, info);
		if (ret) {
			dev_err(info->dev,
				"failed: irq request (IRQ: %d, error :%d)\n",
				muic_irq->irq, ret);
			return ret;
		}
	}

	/* Allocate extcon device */
	info->edev = devm_extcon_dev_allocate(info->dev, sm5502_extcon_cable);
	if (IS_ERR(info->edev)) {
		dev_err(info->dev, "failed to allocate memory for extcon\n");
		return -ENOMEM;
	}

	/* Register extcon device */
	ret = devm_extcon_dev_register(info->dev, info->edev);
	if (ret) {
		dev_err(info->dev, "failed to register extcon device\n");
		return ret;
	}

	/*
	 * Detect accessory after completing the initialization of platform
	 *
	 * - Use delayed workqueue to detect cable state and then
	 * notify cable state to notifiee/platform through uevent.
	 * After completing the booting of platform, the extcon provider
	 * driver should notify cable state to upper layer.
	 */
	INIT_DELAYED_WORK(&info->wq_detcable, sm5502_muic_detect_cable_wq);
	queue_delayed_work(system_power_efficient_wq, &info->wq_detcable,
			msecs_to_jiffies(DELAY_MS_DEFAULT));

	/* Initialize SM5502 device and print vendor id and version id */
	sm5502_init_dev_type(info);

	return 0;
}