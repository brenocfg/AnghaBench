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
struct regmap_config {int val_bits; int reg_bits; } ;
struct regmap_bus {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUPP ; 
 struct regmap_bus const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
#define  REGMAP_ENDIAN_BIG 129 
#define  REGMAP_ENDIAN_LITTLE 128 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_get_val_endian (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct regmap_config const*) ; 
 struct regmap_bus const regmap_i2c ; 
 struct regmap_bus const regmap_i2c_smbus_i2c_block ; 
 struct regmap_bus const regmap_smbus_byte ; 
 struct regmap_bus const regmap_smbus_word ; 
 struct regmap_bus const regmap_smbus_word_swapped ; 

__attribute__((used)) static const struct regmap_bus *regmap_get_i2c_bus(struct i2c_client *i2c,
					const struct regmap_config *config)
{
	if (i2c_check_functionality(i2c->adapter, I2C_FUNC_I2C))
		return &regmap_i2c;
	else if (config->val_bits == 8 && config->reg_bits == 8 &&
		 i2c_check_functionality(i2c->adapter,
					 I2C_FUNC_SMBUS_I2C_BLOCK))
		return &regmap_i2c_smbus_i2c_block;
	else if (config->val_bits == 16 && config->reg_bits == 8 &&
		 i2c_check_functionality(i2c->adapter,
					 I2C_FUNC_SMBUS_WORD_DATA))
		switch (regmap_get_val_endian(&i2c->dev, NULL, config)) {
		case REGMAP_ENDIAN_LITTLE:
			return &regmap_smbus_word;
		case REGMAP_ENDIAN_BIG:
			return &regmap_smbus_word_swapped;
		default:		/* everything else is not supported */
			break;
		}
	else if (config->val_bits == 8 && config->reg_bits == 8 &&
		 i2c_check_functionality(i2c->adapter,
					 I2C_FUNC_SMBUS_BYTE_DATA))
		return &regmap_smbus_byte;

	return ERR_PTR(-ENOTSUPP);
}