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
struct tpm_chip {int /*<<< orphan*/  dev; void* timeout_d; void* timeout_c; void* timeout_b; void* timeout_a; } ;
struct priv_data {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (struct tpm_chip*) ; 
 int PTR_ERR (struct tpm_chip*) ; 
 int /*<<< orphan*/  TPM_I2C_LONG_TIMEOUT ; 
 int /*<<< orphan*/  TPM_I2C_SHORT_TIMEOUT ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct priv_data*) ; 
 struct priv_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_atmel ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int tpm_chip_register (struct tpm_chip*) ; 
 struct tpm_chip* tpmm_chip_alloc (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_atmel_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct tpm_chip *chip;
	struct device *dev = &client->dev;
	struct priv_data *priv;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	chip = tpmm_chip_alloc(dev, &i2c_atmel);
	if (IS_ERR(chip))
		return PTR_ERR(chip);

	priv = devm_kzalloc(dev, sizeof(struct priv_data), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	/* Default timeouts */
	chip->timeout_a = msecs_to_jiffies(TPM_I2C_SHORT_TIMEOUT);
	chip->timeout_b = msecs_to_jiffies(TPM_I2C_LONG_TIMEOUT);
	chip->timeout_c = msecs_to_jiffies(TPM_I2C_SHORT_TIMEOUT);
	chip->timeout_d = msecs_to_jiffies(TPM_I2C_SHORT_TIMEOUT);

	dev_set_drvdata(&chip->dev, priv);

	/* There is no known way to probe for this device, and all version
	 * information seems to be read via TPM commands. Thus we rely on the
	 * TPM startup process in the common code to detect the device. */

	return tpm_chip_register(chip);
}