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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLEEP_TOKEN ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int atmel_i2c_sleep(struct i2c_client *client)
{
	u8 sleep = SLEEP_TOKEN;

	return i2c_master_send(client, &sleep, 1);
}