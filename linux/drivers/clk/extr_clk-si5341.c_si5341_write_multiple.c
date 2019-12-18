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
struct si5341_reg_default {int /*<<< orphan*/  value; int /*<<< orphan*/  address; } ;
struct clk_si5341 {TYPE_1__* i2c_client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si5341_write_multiple(struct clk_si5341 *data,
	const struct si5341_reg_default *values, unsigned int num_values)
{
	unsigned int i;
	int res;

	for (i = 0; i < num_values; ++i) {
		res = regmap_write(data->regmap,
			values[i].address, values[i].value);
		if (res < 0) {
			dev_err(&data->i2c_client->dev,
				"Failed to write %#x:%#x\n",
				values[i].address, values[i].value);
			return res;
		}
	}

	return 0;
}