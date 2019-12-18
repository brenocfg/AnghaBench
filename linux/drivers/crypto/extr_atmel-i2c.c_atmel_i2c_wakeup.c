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
struct atmel_i2c_client_priv {int /*<<< orphan*/  wake_token_sz; int /*<<< orphan*/  wake_token; } ;

/* Variables and functions */
 int STATUS_RSP_SIZE ; 
 int /*<<< orphan*/  STATUS_SIZE ; 
 int /*<<< orphan*/  TWHI_MAX ; 
 int /*<<< orphan*/  TWHI_MIN ; 
 int atmel_i2c_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct atmel_i2c_client_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_send (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_i2c_wakeup(struct i2c_client *client)
{
	struct atmel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);
	u8 status[STATUS_RSP_SIZE];
	int ret;

	/*
	 * The device ignores any levels or transitions on the SCL pin when the
	 * device is idle, asleep or during waking up. Don't check for error
	 * when waking up the device.
	 */
	i2c_master_send(client, i2c_priv->wake_token, i2c_priv->wake_token_sz);

	/*
	 * Wait to wake the device. Typical execution times for ecdh and genkey
	 * are around tens of milliseconds. Delta is chosen to 50 microseconds.
	 */
	usleep_range(TWHI_MIN, TWHI_MAX);

	ret = i2c_master_recv(client, status, STATUS_SIZE);
	if (ret < 0)
		return ret;

	return atmel_i2c_status(&client->dev, status);
}