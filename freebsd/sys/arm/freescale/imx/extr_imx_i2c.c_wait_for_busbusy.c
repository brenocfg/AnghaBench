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
struct i2c_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int I2CSR_MBB ; 
 int /*<<< orphan*/  I2C_STATUS_REG ; 
 int IIC_ETIMEOUT ; 
 int IIC_NOERR ; 
 int i2c_read_reg (struct i2c_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wait_for_busbusy(struct i2c_softc *sc, int wantbusy)
{
	int retry, srb;

	retry = 1000;
	while (retry --) {
		srb = i2c_read_reg(sc, I2C_STATUS_REG) & I2CSR_MBB;
		if ((srb && wantbusy) || (!srb && !wantbusy))
			return (IIC_NOERR);
		DELAY(1);
	}
	return (IIC_ETIMEOUT);
}