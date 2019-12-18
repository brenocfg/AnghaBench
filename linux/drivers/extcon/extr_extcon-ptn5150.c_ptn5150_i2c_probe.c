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
struct ptn5150_info {scalar_t__ irq; struct device* dev; void* edev; void* int_gpiod; void* regmap; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  mutex; void* vbus_gpiod; struct i2c_client* i2c; } ;
struct i2c_device_id {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_extcon_dev_allocate (struct device*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (struct device*,void*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ptn5150_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ptn5150_info*) ; 
 int gpiod_direction_output (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_to_irq (void*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ptn5150_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptn5150_extcon_cable ; 
 int ptn5150_init_dev_type (struct ptn5150_info*) ; 
 int /*<<< orphan*/  ptn5150_irq_handler ; 
 int /*<<< orphan*/  ptn5150_irq_work ; 
 int /*<<< orphan*/  ptn5150_regmap_config ; 

__attribute__((used)) static int ptn5150_i2c_probe(struct i2c_client *i2c,
				 const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct device_node *np = i2c->dev.of_node;
	struct ptn5150_info *info;
	int ret;

	if (!np)
		return -EINVAL;

	info = devm_kzalloc(&i2c->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	i2c_set_clientdata(i2c, info);

	info->dev = &i2c->dev;
	info->i2c = i2c;
	info->int_gpiod = devm_gpiod_get(&i2c->dev, "int", GPIOD_IN);
	if (IS_ERR(info->int_gpiod)) {
		dev_err(dev, "failed to get INT GPIO\n");
		return PTR_ERR(info->int_gpiod);
	}
	info->vbus_gpiod = devm_gpiod_get(&i2c->dev, "vbus", GPIOD_IN);
	if (IS_ERR(info->vbus_gpiod)) {
		dev_err(dev, "failed to get VBUS GPIO\n");
		return PTR_ERR(info->vbus_gpiod);
	}
	ret = gpiod_direction_output(info->vbus_gpiod, 0);
	if (ret) {
		dev_err(dev, "failed to set VBUS GPIO direction\n");
		return -EINVAL;
	}

	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, ptn5150_irq_work);

	info->regmap = devm_regmap_init_i2c(i2c, &ptn5150_regmap_config);
	if (IS_ERR(info->regmap)) {
		ret = PTR_ERR(info->regmap);
		dev_err(info->dev, "failed to allocate register map: %d\n",
				   ret);
		return ret;
	}

	if (info->int_gpiod) {
		info->irq = gpiod_to_irq(info->int_gpiod);
		if (info->irq < 0) {
			dev_err(dev, "failed to get INTB IRQ\n");
			return info->irq;
		}

		ret = devm_request_threaded_irq(dev, info->irq, NULL,
						ptn5150_irq_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						i2c->name, info);
		if (ret < 0) {
			dev_err(dev, "failed to request handler for INTB IRQ\n");
			return ret;
		}
	}

	/* Allocate extcon device */
	info->edev = devm_extcon_dev_allocate(info->dev, ptn5150_extcon_cable);
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

	/* Initialize PTN5150 device and print vendor id and version id */
	ret = ptn5150_init_dev_type(info);
	if (ret)
		return -EINVAL;

	return 0;
}