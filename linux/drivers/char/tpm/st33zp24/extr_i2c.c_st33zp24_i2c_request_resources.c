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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct st33zp24_platform_data {int /*<<< orphan*/  io_lpcpd; } ;
struct st33zp24_i2c_phy {int /*<<< orphan*/  io_lpcpd; } ;
struct st33zp24_dev {struct st33zp24_i2c_phy* phy_id; } ;
struct TYPE_3__ {struct st33zp24_platform_data* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct st33zp24_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int devm_gpio_request_one (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct tpm_chip* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int st33zp24_i2c_request_resources(struct i2c_client *client)
{
	struct tpm_chip *chip = i2c_get_clientdata(client);
	struct st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	struct st33zp24_i2c_phy *phy = tpm_dev->phy_id;
	struct st33zp24_platform_data *pdata;
	int ret;

	pdata = client->dev.platform_data;
	if (!pdata) {
		dev_err(&client->dev, "No platform data\n");
		return -ENODEV;
	}

	/* store for late use */
	phy->io_lpcpd = pdata->io_lpcpd;

	if (gpio_is_valid(pdata->io_lpcpd)) {
		ret = devm_gpio_request_one(&client->dev,
				pdata->io_lpcpd, GPIOF_OUT_INIT_HIGH,
				"TPM IO_LPCPD");
		if (ret) {
			dev_err(&client->dev, "Failed to request lpcpd pin\n");
			return ret;
		}
	}

	return 0;
}