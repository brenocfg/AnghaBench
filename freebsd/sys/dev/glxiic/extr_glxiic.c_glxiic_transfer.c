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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct iic_msg {int dummy; } ;
struct glxiic_softc {scalar_t__ state; int error; int /*<<< orphan*/  smb_res; int /*<<< orphan*/  nmsgs; struct iic_msg* msg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_LOCK (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_SLEEP (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_SMB_CTRL1 ; 
 int GLXIIC_SMB_CTRL1_START_BIT ; 
 scalar_t__ GLXIIC_STATE_IDLE ; 
 int /*<<< orphan*/  GLXIIC_STATE_MASTER_ADDR ; 
 int /*<<< orphan*/  GLXIIC_UNLOCK (struct glxiic_softc*) ; 
 int IIC_EBUSBSY ; 
 int bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct glxiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxiic_set_state_locked (struct glxiic_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
glxiic_transfer(device_t dev, struct iic_msg *msgs, uint32_t nmsgs)
{
	struct glxiic_softc *sc;
	int error;
	uint8_t ctrl1;

	sc = device_get_softc(dev);

	GLXIIC_LOCK(sc);

	if (sc->state != GLXIIC_STATE_IDLE) {
		error = IIC_EBUSBSY;
		goto out;
	}

	sc->msg = msgs;
	sc->nmsgs = nmsgs;
	glxiic_set_state_locked(sc, GLXIIC_STATE_MASTER_ADDR);

	/* Set start bit and let glxiic_intr() handle the transfer. */
	ctrl1 = bus_read_1(sc->smb_res, GLXIIC_SMB_CTRL1);
	bus_write_1(sc->smb_res, GLXIIC_SMB_CTRL1,
	    ctrl1 | GLXIIC_SMB_CTRL1_START_BIT);

	GLXIIC_SLEEP(sc);
	error = sc->error;
out:
	GLXIIC_UNLOCK(sc);

	return (error);
}