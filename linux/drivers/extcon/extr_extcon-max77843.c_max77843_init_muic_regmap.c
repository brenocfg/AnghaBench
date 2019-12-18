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
struct max77693_dev {int /*<<< orphan*/  i2c_muic; TYPE_1__* i2c; int /*<<< orphan*/  irq_data_muic; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap_muic; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_ADDR_MUIC ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_new_dummy_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (int /*<<< orphan*/ ,struct max77693_dev*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max77843_muic_irq_chip ; 
 int /*<<< orphan*/  max77843_muic_regmap_config ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max77843_init_muic_regmap(struct max77693_dev *max77843)
{
	int ret;

	max77843->i2c_muic = i2c_new_dummy_device(max77843->i2c->adapter,
			I2C_ADDR_MUIC);
	if (IS_ERR(max77843->i2c_muic)) {
		dev_err(&max77843->i2c->dev,
				"Cannot allocate I2C device for MUIC\n");
		return PTR_ERR(max77843->i2c_muic);
	}

	i2c_set_clientdata(max77843->i2c_muic, max77843);

	max77843->regmap_muic = devm_regmap_init_i2c(max77843->i2c_muic,
			&max77843_muic_regmap_config);
	if (IS_ERR(max77843->regmap_muic)) {
		ret = PTR_ERR(max77843->regmap_muic);
		goto err_muic_i2c;
	}

	ret = regmap_add_irq_chip(max77843->regmap_muic, max77843->irq,
			IRQF_TRIGGER_LOW | IRQF_ONESHOT | IRQF_SHARED,
			0, &max77843_muic_irq_chip, &max77843->irq_data_muic);
	if (ret < 0) {
		dev_err(&max77843->i2c->dev, "Cannot add MUIC IRQ chip\n");
		goto err_muic_i2c;
	}

	return 0;

err_muic_i2c:
	i2c_unregister_device(max77843->i2c_muic);

	return ret;
}