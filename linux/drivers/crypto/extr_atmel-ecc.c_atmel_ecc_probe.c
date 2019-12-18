#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct atmel_i2c_client_priv {int /*<<< orphan*/  i2c_client_list_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  i2c_list_lock; int /*<<< orphan*/  i2c_client_list; } ;

/* Variables and functions */
 TYPE_3__ atmel_ecdh ; 
 int atmel_i2c_probe (struct i2c_client*,struct i2c_device_id const*) ; 
 int crypto_register_kpp (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ driver_data ; 
 struct atmel_i2c_client_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_ecc_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct atmel_i2c_client_priv *i2c_priv;
	int ret;

	ret = atmel_i2c_probe(client, id);
	if (ret)
		return ret;

	i2c_priv = i2c_get_clientdata(client);

	spin_lock(&driver_data.i2c_list_lock);
	list_add_tail(&i2c_priv->i2c_client_list_node,
		      &driver_data.i2c_client_list);
	spin_unlock(&driver_data.i2c_list_lock);

	ret = crypto_register_kpp(&atmel_ecdh);
	if (ret) {
		spin_lock(&driver_data.i2c_list_lock);
		list_del(&i2c_priv->i2c_client_list_node);
		spin_unlock(&driver_data.i2c_list_lock);

		dev_err(&client->dev, "%s alg registration failed\n",
			atmel_ecdh.base.cra_driver_name);
	} else {
		dev_info(&client->dev, "atmel ecc algorithms registered in /proc/crypto\n");
	}

	return ret;
}