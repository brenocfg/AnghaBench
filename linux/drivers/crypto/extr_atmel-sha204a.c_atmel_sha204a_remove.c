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
struct TYPE_2__ {scalar_t__ priv; } ;
struct atmel_i2c_client_priv {TYPE_1__ hwrng; int /*<<< orphan*/  tfm_count; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct atmel_i2c_client_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static int atmel_sha204a_remove(struct i2c_client *client)
{
	struct atmel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);

	if (atomic_read(&i2c_priv->tfm_count)) {
		dev_err(&client->dev, "Device is busy\n");
		return -EBUSY;
	}

	if (i2c_priv->hwrng.priv)
		kfree((void *)i2c_priv->hwrng.priv);

	return 0;
}