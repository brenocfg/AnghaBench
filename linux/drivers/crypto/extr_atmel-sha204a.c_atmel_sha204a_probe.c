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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int quality; int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct atmel_i2c_client_priv {TYPE_1__ hwrng; } ;

/* Variables and functions */
 int atmel_i2c_probe (struct i2c_client*,struct i2c_device_id const*) ; 
 int /*<<< orphan*/  atmel_sha204a_rng_read ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int devm_hwrng_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct atmel_i2c_client_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atmel_sha204a_probe(struct i2c_client *client,
			       const struct i2c_device_id *id)
{
	struct atmel_i2c_client_priv *i2c_priv;
	int ret;

	ret = atmel_i2c_probe(client, id);
	if (ret)
		return ret;

	i2c_priv = i2c_get_clientdata(client);

	memset(&i2c_priv->hwrng, 0, sizeof(i2c_priv->hwrng));

	i2c_priv->hwrng.name = dev_name(&client->dev);
	i2c_priv->hwrng.read = atmel_sha204a_rng_read;
	i2c_priv->hwrng.quality = 1024;

	ret = devm_hwrng_register(&client->dev, &i2c_priv->hwrng);
	if (ret)
		dev_warn(&client->dev, "failed to register RNG (%d)\n", ret);

	return ret;
}