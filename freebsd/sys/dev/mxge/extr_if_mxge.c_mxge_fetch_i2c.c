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
typedef  int uint32_t ;
struct ifi2creq {int dev_addr; int len; int offset; int* data; } ;
typedef  int /*<<< orphan*/  mxge_softc_t ;
struct TYPE_3__ {int data0; int data1; } ;
typedef  TYPE_1__ mxge_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  MXGEFW_CMD_I2C_BYTE ; 
 int /*<<< orphan*/  MXGEFW_CMD_I2C_READ ; 
 int MXGEFW_CMD_OK ; 
 int mxge_send_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
mxge_fetch_i2c(mxge_softc_t *sc, struct ifi2creq *i2c)
{
	mxge_cmd_t cmd;
	uint32_t i2c_args;
	int i, ms, err;


	if (i2c->dev_addr != 0xA0 &&
	    i2c->dev_addr != 0xA2)
		return (EINVAL);
	if (i2c->len > sizeof(i2c->data))
		return (EINVAL);

	for (i = 0; i < i2c->len; i++) {
		i2c_args = i2c->dev_addr << 0x8;
		i2c_args |= i2c->offset + i;
		cmd.data0 = 0;	 /* just fetch 1 byte, not all 256 */
		cmd.data1 = i2c_args;
		err = mxge_send_cmd(sc, MXGEFW_CMD_I2C_READ, &cmd);

		if (err != MXGEFW_CMD_OK)
			return (EIO);
		/* now we wait for the data to be cached */
		cmd.data0 = i2c_args & 0xff;
		err = mxge_send_cmd(sc, MXGEFW_CMD_I2C_BYTE, &cmd);
		for (ms = 0; (err == EBUSY) && (ms < 50); ms++) {
			cmd.data0 = i2c_args & 0xff;
			err = mxge_send_cmd(sc, MXGEFW_CMD_I2C_BYTE, &cmd);
			if (err == EBUSY)
				DELAY(1000);
		}
		if (err != MXGEFW_CMD_OK)
			return (EIO);
		i2c->data[i] = cmd.data0;
	}
	return (0);
}