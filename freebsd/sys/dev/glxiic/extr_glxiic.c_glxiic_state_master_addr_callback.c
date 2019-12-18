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
typedef  int uint8_t ;
struct glxiic_softc {int ndata; int /*<<< orphan*/  smb_res; TYPE_1__* msg; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int flags; int slave; int len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_ASSERT_LOCKED (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_DEBUG_LOG (char*) ; 
 int /*<<< orphan*/  GLXIIC_SMB_CTRL1 ; 
 int GLXIIC_SMB_CTRL1_ACK_BIT ; 
 int /*<<< orphan*/  GLXIIC_SMB_SDA ; 
 int GLXIIC_SMB_STS_BER_BIT ; 
 int GLXIIC_SMB_STS_MASTER_BIT ; 
 int GLXIIC_SMB_STS_SDAST_BIT ; 
 int /*<<< orphan*/  GLXIIC_STATE_MASTER_RX ; 
 int /*<<< orphan*/  GLXIIC_STATE_MASTER_STOP ; 
 int /*<<< orphan*/  GLXIIC_STATE_MASTER_TX ; 
 int IIC_EBUSERR ; 
 int IIC_ESTATUS ; 
 int IIC_M_RD ; 
 int IIC_NOERR ; 
 int LSB ; 
 int bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glxiic_set_state_locked (struct glxiic_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
glxiic_state_master_addr_callback(struct glxiic_softc *sc, uint8_t status)
{
	uint8_t slave;
	uint8_t ctrl1;

	GLXIIC_ASSERT_LOCKED(sc);

	if ((status & GLXIIC_SMB_STS_BER_BIT) != 0) {
		GLXIIC_DEBUG_LOG("bus error after master start");
		return (IIC_EBUSERR);
	}

	if ((status & GLXIIC_SMB_STS_MASTER_BIT) == 0) {
		GLXIIC_DEBUG_LOG("not bus master after master start");
		return (IIC_ESTATUS);
	}

	if ((status & GLXIIC_SMB_STS_SDAST_BIT) == 0) {
		GLXIIC_DEBUG_LOG("not awaiting address in master addr");
		return (IIC_ESTATUS);
	}

	if ((sc->msg->flags & IIC_M_RD) != 0) {
		slave = sc->msg->slave | LSB;
		glxiic_set_state_locked(sc, GLXIIC_STATE_MASTER_RX);
	} else {
		slave = sc->msg->slave & ~LSB;
		glxiic_set_state_locked(sc, GLXIIC_STATE_MASTER_TX);
	}

	sc->data = sc->msg->buf;
	sc->ndata = sc->msg->len;

	/* Handle address-only transfer. */
	if (sc->ndata == 0)
		glxiic_set_state_locked(sc, GLXIIC_STATE_MASTER_STOP);

	bus_write_1(sc->smb_res, GLXIIC_SMB_SDA, slave);

	if ((sc->msg->flags & IIC_M_RD) != 0 && sc->ndata == 1) {
		/* Last byte from slave, set NACK. */
		ctrl1 = bus_read_1(sc->smb_res, GLXIIC_SMB_CTRL1);
		bus_write_1(sc->smb_res, GLXIIC_SMB_CTRL1,
		    ctrl1 | GLXIIC_SMB_CTRL1_ACK_BIT);
	}

	return (IIC_NOERR);
}