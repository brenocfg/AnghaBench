#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct i2c_msg {size_t len; int* buf; int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_1__* algo; } ;
struct TYPE_9__ {int* buf; TYPE_2__* client; } ;
struct TYPE_8__ {TYPE_4__* adapter; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  master_xfer; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_LOCK_SEGMENT ; 
 unsigned int SLEEP_DURATION_HI ; 
 unsigned int SLEEP_DURATION_LOW ; 
 size_t TPM_I2C_INFINEON_BUFSIZE ; 
 int __i2c_transfer (TYPE_4__*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  i2c_lock_bus (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unlock_bus (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 TYPE_3__ tpm_dev ; 
 int /*<<< orphan*/  usleep_range (unsigned int,unsigned int) ; 

__attribute__((used)) static int iic_tpm_write_generic(u8 addr, u8 *buffer, size_t len,
				 unsigned int sleep_low,
				 unsigned int sleep_hi, u8 max_count)
{
	int rc = -EIO;
	int count;

	struct i2c_msg msg1 = {
		.addr = tpm_dev.client->addr,
		.len = len + 1,
		.buf = tpm_dev.buf
	};

	if (len > TPM_I2C_INFINEON_BUFSIZE)
		return -EINVAL;

	if (!tpm_dev.client->adapter->algo->master_xfer)
		return -EOPNOTSUPP;
	i2c_lock_bus(tpm_dev.client->adapter, I2C_LOCK_SEGMENT);

	/* prepend the 'register address' to the buffer */
	tpm_dev.buf[0] = addr;
	memcpy(&(tpm_dev.buf[1]), buffer, len);

	/*
	 * NOTE: We have to use these special mechanisms here and unfortunately
	 * cannot rely on the standard behavior of i2c_transfer.
	 * Even for newer chips the smbus functions are not
	 * suitable due to the 32 byte limit of the smbus.
	 */
	for (count = 0; count < max_count; count++) {
		rc = __i2c_transfer(tpm_dev.client->adapter, &msg1, 1);
		if (rc > 0)
			break;
		usleep_range(sleep_low, sleep_hi);
	}

	i2c_unlock_bus(tpm_dev.client->adapter, I2C_LOCK_SEGMENT);
	/* take care of 'guard time' */
	usleep_range(SLEEP_DURATION_LOW, SLEEP_DURATION_HI);

	/* __i2c_transfer returns the number of successfully transferred
	 * messages.
	 * So rc should be greater than 0 here otherwise we have an error.
	 */
	if (rc <= 0)
		return -EIO;

	return 0;
}