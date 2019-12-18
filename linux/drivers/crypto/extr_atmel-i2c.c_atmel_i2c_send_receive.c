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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct atmel_i2c_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  rxsize; int /*<<< orphan*/  msecs; scalar_t__ count; } ;
struct atmel_i2c_client_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ WORD_ADDR_SIZE ; 
 int atmel_i2c_sleep (struct i2c_client*) ; 
 int atmel_i2c_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atmel_i2c_wakeup (struct i2c_client*) ; 
 struct atmel_i2c_client_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int atmel_i2c_send_receive(struct i2c_client *client, struct atmel_i2c_cmd *cmd)
{
	struct atmel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&i2c_priv->lock);

	ret = atmel_i2c_wakeup(client);
	if (ret)
		goto err;

	/* send the command */
	ret = i2c_master_send(client, (u8 *)cmd, cmd->count + WORD_ADDR_SIZE);
	if (ret < 0)
		goto err;

	/* delay the appropriate amount of time for command to execute */
	msleep(cmd->msecs);

	/* receive the response */
	ret = i2c_master_recv(client, cmd->data, cmd->rxsize);
	if (ret < 0)
		goto err;

	/* put the device into low-power mode */
	ret = atmel_i2c_sleep(client);
	if (ret < 0)
		goto err;

	mutex_unlock(&i2c_priv->lock);
	return atmel_i2c_status(&client->dev, cmd->data);
err:
	mutex_unlock(&i2c_priv->lock);
	return ret;
}