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
struct glxiic_softc {size_t state; int error; int /*<<< orphan*/  iicbus; } ;
struct TYPE_2__ {int (* callback ) (struct glxiic_softc*,int) ;scalar_t__ master; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_LOCK (struct glxiic_softc*) ; 
 int GLXIIC_SMB_STS_MASTER_BIT ; 
 int GLXIIC_SMB_STS_XMIT_BIT ; 
 int /*<<< orphan*/  GLXIIC_STATE_IDLE ; 
 int /*<<< orphan*/  GLXIIC_UNLOCK (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_WAKEUP (struct glxiic_softc*) ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  INTR_ERROR ; 
 int glxiic_read_status_locked (struct glxiic_softc*) ; 
 int /*<<< orphan*/  glxiic_set_state_locked (struct glxiic_softc*,int /*<<< orphan*/ ) ; 
 TYPE_1__* glxiic_state_table ; 
 int /*<<< orphan*/  glxiic_stop_locked (struct glxiic_softc*) ; 
 int /*<<< orphan*/  iicbus_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub1 (struct glxiic_softc*,int) ; 

__attribute__((used)) static void
glxiic_intr(void *arg)
{
	struct glxiic_softc *sc;
	int error;
	uint8_t status, data;

	sc = (struct glxiic_softc *)arg;

	GLXIIC_LOCK(sc);

	status = glxiic_read_status_locked(sc);

	/* Check if this interrupt originated from the SMBus. */
	if ((status &
		~(GLXIIC_SMB_STS_MASTER_BIT | GLXIIC_SMB_STS_XMIT_BIT)) != 0) {

		error = glxiic_state_table[sc->state].callback(sc, status);

		if (error != IIC_NOERR) {
			if (glxiic_state_table[sc->state].master) {
				glxiic_stop_locked(sc);
				glxiic_set_state_locked(sc, GLXIIC_STATE_IDLE);
				sc->error = error;
				GLXIIC_WAKEUP(sc);
			} else {
				data = error & 0xff;
				iicbus_intr(sc->iicbus, INTR_ERROR, &data);
				glxiic_set_state_locked(sc, GLXIIC_STATE_IDLE);
			}
		}
	}

	GLXIIC_UNLOCK(sc);
}