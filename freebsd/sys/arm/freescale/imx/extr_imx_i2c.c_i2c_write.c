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
struct i2c_softc {int /*<<< orphan*/  slave; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (struct i2c_softc*,int,char*,...) ; 
 int /*<<< orphan*/  DEVICE_DEBUGF (struct i2c_softc*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I2C_DATA_REG ; 
 int /*<<< orphan*/  I2C_STATUS_REG ; 
 int IIC_NOERR ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int i2c_error_handler (struct i2c_softc*,int) ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int wait_for_xfer (struct i2c_softc*,int) ; 

__attribute__((used)) static int
i2c_write(device_t dev, const char *buf, int len, int *sent, int timeout)
{
	struct i2c_softc *sc;
	int error;

	sc = device_get_softc(dev);

	error = 0;
	*sent = 0;
	DEVICE_DEBUGF(sc, 1, "write  0x%02x len %d: ", sc->slave, len);
	while (*sent < len) {
		DEBUGF(sc, 1, "0x%02x ", *buf);
		i2c_write_reg(sc, I2C_STATUS_REG, 0x0);
		i2c_write_reg(sc, I2C_DATA_REG, *buf++);
		if ((error = wait_for_xfer(sc, true)) != IIC_NOERR)
			break;
		(*sent)++;
	}
	DEBUGF(sc, 1, "\n");
	return (i2c_error_handler(sc, error));
}