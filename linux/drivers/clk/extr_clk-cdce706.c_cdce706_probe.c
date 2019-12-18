#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct cdce706_dev_data {int /*<<< orphan*/  regmap; struct i2c_client* client; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int cdce706_register_clkin (struct cdce706_dev_data*) ; 
 int cdce706_register_clkouts (struct cdce706_dev_data*) ; 
 int cdce706_register_dividers (struct cdce706_dev_data*) ; 
 int cdce706_register_plls (struct cdce706_dev_data*) ; 
 int /*<<< orphan*/  cdce706_regmap_config ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct cdce706_dev_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cdce706_dev_data*) ; 
 int of_clk_add_hw_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cdce706_dev_data*) ; 
 int /*<<< orphan*/  of_clk_cdce_get ; 

__attribute__((used)) static int cdce706_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct cdce706_dev_data *cdce;
	int ret;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	cdce = devm_kzalloc(&client->dev, sizeof(*cdce), GFP_KERNEL);
	if (!cdce)
		return -ENOMEM;

	cdce->client = client;
	cdce->regmap = devm_regmap_init_i2c(client, &cdce706_regmap_config);
	if (IS_ERR(cdce->regmap)) {
		dev_err(&client->dev, "Failed to initialize regmap\n");
		return -EINVAL;
	}

	i2c_set_clientdata(client, cdce);

	ret = cdce706_register_clkin(cdce);
	if (ret < 0)
		return ret;
	ret = cdce706_register_plls(cdce);
	if (ret < 0)
		return ret;
	ret = cdce706_register_dividers(cdce);
	if (ret < 0)
		return ret;
	ret = cdce706_register_clkouts(cdce);
	if (ret < 0)
		return ret;
	return of_clk_add_hw_provider(client->dev.of_node, of_clk_cdce_get,
				      cdce);
}