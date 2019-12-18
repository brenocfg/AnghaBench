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
typedef  long u32 ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {TYPE_1__* adapter; struct device dev; } ;
struct atmel_i2c_client_priv {int /*<<< orphan*/  tfm_count; int /*<<< orphan*/  wake_token; int /*<<< orphan*/  wake_token_sz; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  atmel_i2c_wake_token_sz (long) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int device_property_read_u32 (int /*<<< orphan*/ *,char*,long*) ; 
 int device_sanity_check (struct i2c_client*) ; 
 struct atmel_i2c_client_priv* devm_kmalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 long i2c_acpi_find_bus_speed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct atmel_i2c_client_priv*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int atmel_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct atmel_i2c_client_priv *i2c_priv;
	struct device *dev = &client->dev;
	int ret;
	u32 bus_clk_rate;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(dev, "I2C_FUNC_I2C not supported\n");
		return -ENODEV;
	}

	bus_clk_rate = i2c_acpi_find_bus_speed(&client->adapter->dev);
	if (!bus_clk_rate) {
		ret = device_property_read_u32(&client->adapter->dev,
					       "clock-frequency", &bus_clk_rate);
		if (ret) {
			dev_err(dev, "failed to read clock-frequency property\n");
			return ret;
		}
	}

	if (bus_clk_rate > 1000000L) {
		dev_err(dev, "%d exceeds maximum supported clock frequency (1MHz)\n",
			bus_clk_rate);
		return -EINVAL;
	}

	i2c_priv = devm_kmalloc(dev, sizeof(*i2c_priv), GFP_KERNEL);
	if (!i2c_priv)
		return -ENOMEM;

	i2c_priv->client = client;
	mutex_init(&i2c_priv->lock);

	/*
	 * WAKE_TOKEN_MAX_SIZE was calculated for the maximum bus_clk_rate -
	 * 1MHz. The previous bus_clk_rate check ensures us that wake_token_sz
	 * will always be smaller than or equal to WAKE_TOKEN_MAX_SIZE.
	 */
	i2c_priv->wake_token_sz = atmel_i2c_wake_token_sz(bus_clk_rate);

	memset(i2c_priv->wake_token, 0, sizeof(i2c_priv->wake_token));

	atomic_set(&i2c_priv->tfm_count, 0);

	i2c_set_clientdata(client, i2c_priv);

	ret = device_sanity_check(client);
	if (ret)
		return ret;

	return 0;
}