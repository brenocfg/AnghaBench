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
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_2__ {struct i2c_client* client; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ tpm_dev ; 
 int tpm_tis_i2c_init (struct device*) ; 

__attribute__((used)) static int tpm_tis_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	int rc;
	struct device *dev = &(client->dev);

	if (tpm_dev.client != NULL) {
		dev_err(dev, "This driver only supports one client at a time\n");
		return -EBUSY;	/* We only support one client */
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(dev, "no algorithms associated to the i2c bus\n");
		return -ENODEV;
	}

	tpm_dev.client = client;
	rc = tpm_tis_i2c_init(&client->dev);
	if (rc != 0) {
		tpm_dev.client = NULL;
		rc = -ENODEV;
	}
	return rc;
}