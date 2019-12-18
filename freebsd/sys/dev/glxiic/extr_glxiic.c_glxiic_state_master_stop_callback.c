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
struct glxiic_softc {scalar_t__ nmsgs; int error; TYPE_1__* msg; int /*<<< orphan*/  smb_res; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_ASSERT_LOCKED (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_DEBUG_LOG (char*) ; 
 int /*<<< orphan*/  GLXIIC_SMB_CTRL1 ; 
 int GLXIIC_SMB_CTRL1_START_BIT ; 
 int GLXIIC_SMB_STS_BER_BIT ; 
 int GLXIIC_SMB_STS_MASTER_BIT ; 
 int GLXIIC_SMB_STS_NEGACK_BIT ; 
 int /*<<< orphan*/  GLXIIC_STATE_IDLE ; 
 int /*<<< orphan*/  GLXIIC_STATE_MASTER_ADDR ; 
 int /*<<< orphan*/  GLXIIC_WAKEUP (struct glxiic_softc*) ; 
 int IIC_EBUSERR ; 
 int IIC_ENOACK ; 
 int IIC_ESTATUS ; 
 int IIC_M_NOSTOP ; 
 int IIC_NOERR ; 
 int bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glxiic_set_state_locked (struct glxiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxiic_stop_locked (struct glxiic_softc*) ; 

__attribute__((used)) static int
glxiic_state_master_stop_callback(struct glxiic_softc *sc, uint8_t status)
{
	uint8_t ctrl1;

	GLXIIC_ASSERT_LOCKED(sc);

	if ((status & GLXIIC_SMB_STS_BER_BIT) != 0) {
		GLXIIC_DEBUG_LOG("bus error in master stop");
		return (IIC_EBUSERR);
	}

	if ((status & GLXIIC_SMB_STS_MASTER_BIT) == 0) {
		GLXIIC_DEBUG_LOG("not bus master in master stop");
		return (IIC_ESTATUS);
	}

	if ((status & GLXIIC_SMB_STS_NEGACK_BIT) != 0) {
		GLXIIC_DEBUG_LOG("slave nack in master stop");
		return (IIC_ENOACK);
	}

	if (--sc->nmsgs > 0) {
		/* Start transfer of next message. */
		if ((sc->msg->flags & IIC_M_NOSTOP) == 0) {
			glxiic_stop_locked(sc);
		}

		ctrl1 = bus_read_1(sc->smb_res, GLXIIC_SMB_CTRL1);
		bus_write_1(sc->smb_res, GLXIIC_SMB_CTRL1,
		    ctrl1 | GLXIIC_SMB_CTRL1_START_BIT);

		glxiic_set_state_locked(sc, GLXIIC_STATE_MASTER_ADDR);
		sc->msg++;
	} else {
		/* Last message. */
		glxiic_stop_locked(sc);
		glxiic_set_state_locked(sc, GLXIIC_STATE_IDLE);
		sc->error = IIC_NOERR;
		GLXIIC_WAKEUP(sc);
	}

	return (IIC_NOERR);
}