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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_I2C_DATA ; 
 int /*<<< orphan*/  A_I2C_OP ; 
 int F_I2C_ACK ; 
 int /*<<< orphan*/  F_I2C_BUSY ; 
 int F_I2C_CONT ; 
 int F_I2C_READ ; 
 int /*<<< orphan*/  G_I2C_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_ATTEMPTS ; 
 int /*<<< orphan*/  MDIO_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDIO_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int t3_wait_op_done_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int t3_i2c_read8(adapter_t *adapter, int chained, u8 *valp)
{
	int ret;
	u32 opval;
	MDIO_LOCK(adapter);
	t3_write_reg(adapter, A_I2C_OP,
		     F_I2C_READ | (chained ? F_I2C_CONT : 0));
	ret = t3_wait_op_done_val(adapter, A_I2C_OP, F_I2C_BUSY, 0,
				  I2C_ATTEMPTS, 10, &opval);
	if (ret >= 0) {
		ret = ((opval & F_I2C_ACK) == F_I2C_ACK);
		*valp = G_I2C_DATA(t3_read_reg(adapter, A_I2C_DATA));
	}
	MDIO_UNLOCK(adapter);
	return ret;
}