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
typedef  int u_char ;
struct iicoc_softc {int i2cdev_addr; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_EBUSERR ; 
 int IIC_ENOACK ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  OC_COMMAND_START ; 
 int /*<<< orphan*/  OC_COMMAND_STOP ; 
 int /*<<< orphan*/  OC_I2C_CMD_REG ; 
 int /*<<< orphan*/  OC_I2C_STATUS_REG ; 
 int OC_STATUS_AL ; 
 int /*<<< orphan*/  OC_STATUS_BUSY ; 
 struct iicoc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int iicoc_dev_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicoc_dev_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iicoc_wait_on_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iicoc_wr_ack_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
iicoc_start(device_t dev, u_char slave, int timeout)
{
	int error = IIC_EBUSERR;
	struct iicoc_softc *sc;

	sc = device_get_softc(dev);
	mtx_lock(&sc->sc_mtx);
	sc->i2cdev_addr = (slave >> 1);

	/* Verify the bus is idle */
	if (iicoc_wait_on_status(dev, OC_STATUS_BUSY) < 0)
		goto i2c_stx_error;

	/* Write Slave Address */
	if (iicoc_wr_ack_cmd(dev, slave, OC_COMMAND_START)) {
		device_printf(dev, 
		    "I2C write slave address [0x%x] failed.\n", slave);
		error = IIC_ENOACK;
		goto i2c_stx_error;	
	}
	
	/* Verify Arbitration is not Lost */
	if (iicoc_dev_read(dev, OC_I2C_STATUS_REG) & OC_STATUS_AL) {
		device_printf(dev, "I2C Bus Arbitration Lost, Aborting.\n");
		error = IIC_EBUSERR;
		goto i2c_stx_error;
	}
	error = IIC_NOERR;
	mtx_unlock(&sc->sc_mtx);
	return (error);
i2c_stx_error:
	iicoc_dev_write(dev, OC_I2C_CMD_REG, OC_COMMAND_STOP);
	iicoc_wait_on_status(dev, OC_STATUS_BUSY);  /* wait for idle */
	mtx_unlock(&sc->sc_mtx);
	return (error);
}