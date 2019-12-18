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
struct ipmb_dev {int /*<<< orphan*/  miscdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct ipmb_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_slave_unregister (struct i2c_client*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmb_remove(struct i2c_client *client)
{
	struct ipmb_dev *ipmb_dev = i2c_get_clientdata(client);

	i2c_slave_unregister(client);
	misc_deregister(&ipmb_dev->miscdev);

	return 0;
}