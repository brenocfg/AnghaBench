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
struct glxiic_softc {int addr; int /*<<< orphan*/  iicbus; int /*<<< orphan*/  smb_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_ASSERT_LOCKED (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_DEBUG_LOG (char*) ; 
 int /*<<< orphan*/  GLXIIC_SMB_CTRL_STS ; 
 int GLXIIC_SMB_CTRL_STS_GCMTCH_BIT ; 
 int GLXIIC_SMB_CTRL_STS_MATCH_BIT ; 
 int GLXIIC_SMB_STS_XMIT_BIT ; 
 int /*<<< orphan*/  GLXIIC_STATE_SLAVE_RX ; 
 int /*<<< orphan*/  GLXIIC_STATE_SLAVE_TX ; 
 int IIC_ESTATUS ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  INTR_GENERAL ; 
 int /*<<< orphan*/  INTR_START ; 
 int LSB ; 
 int bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxiic_set_state_locked (struct glxiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
glxiic_handle_slave_match_locked(struct glxiic_softc *sc, uint8_t status)
{
	uint8_t ctrl_sts, addr;

	GLXIIC_ASSERT_LOCKED(sc);

	ctrl_sts = bus_read_1(sc->smb_res, GLXIIC_SMB_CTRL_STS);

	if ((ctrl_sts & GLXIIC_SMB_CTRL_STS_MATCH_BIT) != 0) {
		if ((status & GLXIIC_SMB_STS_XMIT_BIT) != 0) {
			addr = sc->addr | LSB;
			glxiic_set_state_locked(sc,
			    GLXIIC_STATE_SLAVE_TX);
		} else {
			addr = sc->addr & ~LSB;
			glxiic_set_state_locked(sc,
			    GLXIIC_STATE_SLAVE_RX);
		}
		iicbus_intr(sc->iicbus, INTR_START, &addr);
	} else if ((ctrl_sts & GLXIIC_SMB_CTRL_STS_GCMTCH_BIT) != 0) {
		addr = 0;
		glxiic_set_state_locked(sc, GLXIIC_STATE_SLAVE_RX);
		iicbus_intr(sc->iicbus, INTR_GENERAL, &addr);
	} else {
		GLXIIC_DEBUG_LOG("unknown slave match");
		return (IIC_ESTATUS);
	}

	return (IIC_NOERR);
}