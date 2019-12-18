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
typedef  int uint32_t ;
typedef  int u_char ;
struct twsi_softc {int /*<<< orphan*/  reg_status; int /*<<< orphan*/  reg_data; int /*<<< orphan*/  reg_control; int /*<<< orphan*/  mutex; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IIC_ENOACK ; 
 int IIC_ESTATUS ; 
 int IIC_ETIMEOUT ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int TWSI_CONTROL_IFLG ; 
 int /*<<< orphan*/  TWSI_CONTROL_START ; 
 int TWSI_READ (struct twsi_softc*,int /*<<< orphan*/ ) ; 
 int TWSI_STATUS_ADDR_R_ACK ; 
 int TWSI_STATUS_ADDR_W_ACK ; 
 int TWSI_STATUS_RPTD_START ; 
 int TWSI_STATUS_START ; 
 int /*<<< orphan*/  TWSI_WRITE (struct twsi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twsi_clear_iflg (struct twsi_softc*) ; 
 int /*<<< orphan*/  twsi_control_set (struct twsi_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ twsi_poll_ctrl (struct twsi_softc*,int,int) ; 

__attribute__((used)) static int
twsi_locked_start(device_t dev, struct twsi_softc *sc, int32_t mask,
    u_char slave, int timeout)
{
	int read_access, iflg_set = 0;
	uint32_t status;

	mtx_assert(&sc->mutex, MA_OWNED);

	if (mask == TWSI_STATUS_RPTD_START)
		/* read IFLG to know if it should be cleared later; from NBSD */
		iflg_set = TWSI_READ(sc, sc->reg_control) & TWSI_CONTROL_IFLG;

	debugf(dev, "send start\n");
	twsi_control_set(sc, TWSI_CONTROL_START);

	if (mask == TWSI_STATUS_RPTD_START && iflg_set) {
		debugf(dev, "IFLG set, clearing (mask=%x)\n", mask);
		twsi_clear_iflg(sc);
	}

	/*
	 * Without this delay we timeout checking IFLG if the timeout is 0.
	 * NBSD driver always waits here too.
	 */
	DELAY(1000);

	if (twsi_poll_ctrl(sc, timeout, TWSI_CONTROL_IFLG)) {
		debugf(dev, "timeout sending %sSTART condition\n",
		    mask == TWSI_STATUS_START ? "" : "repeated ");
		return (IIC_ETIMEOUT);
	}

	status = TWSI_READ(sc, sc->reg_status);
	debugf(dev, "status=%x\n", status);

	if (status != mask) {
		debugf(dev, "wrong status (%02x) after sending %sSTART condition\n",
		    status, mask == TWSI_STATUS_START ? "" : "repeated ");
		return (IIC_ESTATUS);
	}

	TWSI_WRITE(sc, sc->reg_data, slave);
	twsi_clear_iflg(sc);
	DELAY(1000);

	if (twsi_poll_ctrl(sc, timeout, TWSI_CONTROL_IFLG)) {
		debugf(dev, "timeout sending slave address (timeout=%d)\n", timeout);
		return (IIC_ETIMEOUT);
	}

	read_access = (slave & 0x1) ? 1 : 0;
	status = TWSI_READ(sc, sc->reg_status);
	if (status != (read_access ?
	    TWSI_STATUS_ADDR_R_ACK : TWSI_STATUS_ADDR_W_ACK)) {
		debugf(dev, "no ACK (status: %02x) after sending slave address\n",
		    status);
		return (IIC_ENOACK);
	}

	return (IIC_NOERR);
}