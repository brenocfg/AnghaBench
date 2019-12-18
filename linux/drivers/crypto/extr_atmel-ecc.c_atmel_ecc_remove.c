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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct atmel_i2c_client_priv {int /*<<< orphan*/  i2c_client_list_node; int /*<<< orphan*/  tfm_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_list_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atmel_ecdh ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_kpp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ driver_data ; 
 struct atmel_i2c_client_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_ecc_remove(struct i2c_client *client)
{
	struct atmel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);

	/* Return EBUSY if i2c client already allocated. */
	if (atomic_read(&i2c_priv->tfm_count)) {
		dev_err(&client->dev, "Device is busy\n");
		return -EBUSY;
	}

	crypto_unregister_kpp(&atmel_ecdh);

	spin_lock(&driver_data.i2c_list_lock);
	list_del(&i2c_priv->i2c_client_list_node);
	spin_unlock(&driver_data.i2c_list_lock);

	return 0;
}