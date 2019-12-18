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
typedef  int uint32_t ;
struct tegra_i2c_softc {int done; int /*<<< orphan*/  dev; TYPE_1__* msg; void* bus_err; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int I2C_ERROR_MASK ; 
 int /*<<< orphan*/  I2C_INTERRUPT_MASK_REGISTER ; 
 int /*<<< orphan*/  I2C_INTERRUPT_SOURCE_REGISTER ; 
 int /*<<< orphan*/  I2C_INTERRUPT_STATUS_REGISTER ; 
 int I2C_INT_ARB_LOST ; 
 int I2C_INT_NOACK ; 
 int I2C_INT_PACKET_XFER_COMPLETE ; 
 int I2C_INT_RFIFO_DATA_REQ ; 
 int I2C_INT_RFIFO_UNF ; 
 int I2C_INT_TFIFO_DATA_REQ ; 
 int I2C_INT_TFIFO_OVR ; 
 void* IIC_EBUSERR ; 
 void* IIC_ENOACK ; 
 int IIC_M_RD ; 
 int /*<<< orphan*/  LOCK (struct tegra_i2c_softc*) ; 
 int RD4 (struct tegra_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (struct tegra_i2c_softc*) ; 
 int /*<<< orphan*/  WR4 (struct tegra_i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int tegra_i2c_rx (struct tegra_i2c_softc*) ; 
 int tegra_i2c_tx (struct tegra_i2c_softc*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
tegra_i2c_intr(void *arg)
{
	struct tegra_i2c_softc *sc;
	uint32_t status, reg;
	int rv;

	sc = (struct tegra_i2c_softc *)arg;

	LOCK(sc);
	status = RD4(sc, I2C_INTERRUPT_SOURCE_REGISTER);
	if (sc->msg == NULL) {
		/* Unexpected interrupt - disable FIFOs, clear reset. */
		reg = RD4(sc, I2C_INTERRUPT_MASK_REGISTER);
		reg &= ~I2C_INT_TFIFO_DATA_REQ;
		reg &= ~I2C_INT_RFIFO_DATA_REQ;
		WR4(sc, I2C_INTERRUPT_MASK_REGISTER, 0);
		WR4(sc, I2C_INTERRUPT_STATUS_REGISTER, status);
		UNLOCK(sc);
		return;
	}

	if ((status & I2C_ERROR_MASK) != 0) {
		if (status & I2C_INT_NOACK)
			sc->bus_err = IIC_ENOACK;
		if (status & I2C_INT_ARB_LOST)
			sc->bus_err = IIC_EBUSERR;
		if ((status & I2C_INT_TFIFO_OVR) ||
		    (status & I2C_INT_RFIFO_UNF))
			sc->bus_err = IIC_EBUSERR;
		sc->done = 1;
	} else if ((status & I2C_INT_RFIFO_DATA_REQ) &&
	    (sc->msg != NULL) && (sc->msg->flags & IIC_M_RD)) {
		rv = tegra_i2c_rx(sc);
		if (rv == 0) {
			reg = RD4(sc, I2C_INTERRUPT_MASK_REGISTER);
			reg &= ~I2C_INT_RFIFO_DATA_REQ;
			WR4(sc, I2C_INTERRUPT_MASK_REGISTER, reg);
		}
	} else if ((status & I2C_INT_TFIFO_DATA_REQ) &&
	    (sc->msg != NULL) && !(sc->msg->flags & IIC_M_RD)) {
		rv = tegra_i2c_tx(sc);
		if (rv == 0) {
			reg = RD4(sc, I2C_INTERRUPT_MASK_REGISTER);
			reg &= ~I2C_INT_TFIFO_DATA_REQ;
			WR4(sc, I2C_INTERRUPT_MASK_REGISTER, reg);
		}
	} else if ((status & I2C_INT_RFIFO_DATA_REQ) ||
		    (status & I2C_INT_TFIFO_DATA_REQ)) {
		device_printf(sc->dev, "Unexpected data interrupt: 0x%08X\n",
		    status);
		reg = RD4(sc, I2C_INTERRUPT_MASK_REGISTER);
		reg &= ~I2C_INT_TFIFO_DATA_REQ;
		reg &= ~I2C_INT_RFIFO_DATA_REQ;
		WR4(sc, I2C_INTERRUPT_MASK_REGISTER, reg);
	}
	if (status & I2C_INT_PACKET_XFER_COMPLETE)
		sc->done = 1;
	WR4(sc, I2C_INTERRUPT_STATUS_REGISTER, status);
	if (sc->done) {
		WR4(sc, I2C_INTERRUPT_MASK_REGISTER, 0);
		wakeup(&(sc->done));
	}
	UNLOCK(sc);
}