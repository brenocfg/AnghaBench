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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct atmel_i2c_cmd {scalar_t__* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t LOCK_CONFIG_IDX ; 
 size_t LOCK_VALUE_IDX ; 
 int /*<<< orphan*/  atmel_i2c_init_read_cmd (struct atmel_i2c_cmd*) ; 
 int atmel_i2c_send_receive (struct i2c_client*,struct atmel_i2c_cmd*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct atmel_i2c_cmd*) ; 
 struct atmel_i2c_cmd* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_sanity_check(struct i2c_client *client)
{
	struct atmel_i2c_cmd *cmd;
	int ret;

	cmd = kmalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	atmel_i2c_init_read_cmd(cmd);

	ret = atmel_i2c_send_receive(client, cmd);
	if (ret)
		goto free_cmd;

	/*
	 * It is vital that the Configuration, Data and OTP zones be locked
	 * prior to release into the field of the system containing the device.
	 * Failure to lock these zones may permit modification of any secret
	 * keys and may lead to other security problems.
	 */
	if (cmd->data[LOCK_CONFIG_IDX] || cmd->data[LOCK_VALUE_IDX]) {
		dev_err(&client->dev, "Configuration or Data and OTP zones are unlocked!\n");
		ret = -ENOTSUPP;
	}

	/* fall through */
free_cmd:
	kfree(cmd);
	return ret;
}