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
struct i2c_softc {int byte_time_sbt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int I2CSR_MAL ; 
 int I2CSR_MIF ; 
 int I2CSR_RXAK ; 
 int /*<<< orphan*/  I2C_STATUS_REG ; 
 int IIC_EBUSERR ; 
 int IIC_ENOACK ; 
 int IIC_ETIMEOUT ; 
 int IIC_NOERR ; 
 int i2c_read_reg (struct i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_sbt (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wait_for_xfer(struct i2c_softc *sc, int checkack)
{
	int retry, sr;

	/*
	 * Sleep for about the time it takes to transfer a byte (with precision
	 * set to tolerate 5% oversleep).  We calculate the approximate byte
	 * transfer time when we set the bus speed divisor.  Slaves are allowed
	 * to do clock-stretching so the actual transfer time can be larger, but
	 * this gets the bulk of the waiting out of the way without tying up the
	 * processor the whole time.
	 */
	pause_sbt("imxi2c", sc->byte_time_sbt, sc->byte_time_sbt / 20, 0);

	retry = 10000;
	while (retry --) {
		sr = i2c_read_reg(sc, I2C_STATUS_REG);
		if (sr & I2CSR_MIF) {
                        if (sr & I2CSR_MAL) 
				return (IIC_EBUSERR);
			else if (checkack && (sr & I2CSR_RXAK))
				return (IIC_ENOACK);
			else
				return (IIC_NOERR);
		}
		DELAY(1);
	}
	return (IIC_ETIMEOUT);
}