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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,unsigned int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int regmap_smbus_word_read_swapped(void *context, unsigned int reg,
					  unsigned int *val)
{
	struct device *dev = context;
	struct i2c_client *i2c = to_i2c_client(dev);
	int ret;

	if (reg > 0xff)
		return -EINVAL;

	ret = i2c_smbus_read_word_swapped(i2c, reg);
	if (ret < 0)
		return ret;

	*val = ret;

	return 0;
}