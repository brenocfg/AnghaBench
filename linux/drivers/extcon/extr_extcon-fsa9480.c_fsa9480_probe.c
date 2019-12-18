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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct fsa9480_usbsw {int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int CON_MASK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSA9480_REG_CTRL ; 
 int /*<<< orphan*/  FSA9480_REG_INT1_MASK ; 
 int /*<<< orphan*/  FSA9480_REG_INT2_MASK ; 
 int /*<<< orphan*/  FSA9480_REG_TIMING1 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT1_MASK ; 
 int INT2_MASK ; 
 int INT_ATTACH ; 
 int INT_DETACH ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TIMING1_ADC_500MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fsa9480_usbsw* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  fsa9480_detect_dev (struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  fsa9480_extcon_cable ; 
 int /*<<< orphan*/  fsa9480_irq_handler ; 
 int /*<<< orphan*/  fsa9480_regmap_config ; 
 int /*<<< orphan*/  fsa9480_write_reg (struct fsa9480_usbsw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct fsa9480_usbsw*) ; 

__attribute__((used)) static int fsa9480_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct fsa9480_usbsw *info;
	int ret;

	if (!client->irq) {
		dev_err(&client->dev, "no interrupt provided\n");
		return -EINVAL;
	}

	info = devm_kzalloc(&client->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	info->dev = &client->dev;

	i2c_set_clientdata(client, info);

	/* External connector */
	info->edev = devm_extcon_dev_allocate(info->dev,
					      fsa9480_extcon_cable);
	if (IS_ERR(info->edev)) {
		dev_err(info->dev, "failed to allocate memory for extcon\n");
		ret = -ENOMEM;
		return ret;
	}

	ret = devm_extcon_dev_register(info->dev, info->edev);
	if (ret) {
		dev_err(info->dev, "failed to register extcon device\n");
		return ret;
	}

	info->regmap = devm_regmap_init_i2c(client, &fsa9480_regmap_config);
	if (IS_ERR(info->regmap)) {
		ret = PTR_ERR(info->regmap);
		dev_err(info->dev, "failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	/* ADC Detect Time: 500ms */
	fsa9480_write_reg(info, FSA9480_REG_TIMING1, TIMING1_ADC_500MS);

	/* configure automatic switching */
	fsa9480_write_reg(info, FSA9480_REG_CTRL, CON_MASK);

	/* unmask interrupt (attach/detach only) */
	fsa9480_write_reg(info, FSA9480_REG_INT1_MASK,
			  INT1_MASK & ~(INT_ATTACH | INT_DETACH));
	fsa9480_write_reg(info, FSA9480_REG_INT2_MASK, INT2_MASK);

	ret = devm_request_threaded_irq(info->dev, client->irq, NULL,
					fsa9480_irq_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"fsa9480", info);
	if (ret) {
		dev_err(info->dev, "failed to request IRQ\n");
		return ret;
	}

	device_init_wakeup(info->dev, true);
	fsa9480_detect_dev(info);

	return 0;
}