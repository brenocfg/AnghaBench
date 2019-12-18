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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct adnp {TYPE_1__ gpio; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adnp_read(struct adnp *adnp, unsigned offset, uint8_t *value)
{
	int err;

	err = i2c_smbus_read_byte_data(adnp->client, offset);
	if (err < 0) {
		dev_err(adnp->gpio.parent, "%s failed: %d\n",
			"i2c_smbus_read_byte_data()", err);
		return err;
	}

	*value = err;
	return 0;
}