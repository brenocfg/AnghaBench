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
typedef  void* uint8_t ;
struct glxiic_softc {size_t state; int /*<<< orphan*/  addr; int /*<<< orphan*/  iicbus; void* error; } ;
struct TYPE_2__ {scalar_t__ master; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_DEBUG_LOG (char*,size_t) ; 
 int /*<<< orphan*/  GLXIIC_STATE_IDLE ; 
 int /*<<< orphan*/  GLXIIC_WAKEUP (struct glxiic_softc*) ; 
 void* IIC_ETIMEOUT ; 
 int /*<<< orphan*/  IIC_UNKNOWN ; 
 int /*<<< orphan*/  INTR_ERROR ; 
 int /*<<< orphan*/  glxiic_set_state_locked (struct glxiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxiic_smb_disable (struct glxiic_softc*) ; 
 int /*<<< orphan*/  glxiic_smb_enable (struct glxiic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* glxiic_state_table ; 
 int /*<<< orphan*/  iicbus_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void
glxiic_timeout(void *arg)
{
	struct glxiic_softc *sc;
	uint8_t error;

	sc = (struct glxiic_softc *)arg;

	GLXIIC_DEBUG_LOG("timeout in state %d", sc->state);

	if (glxiic_state_table[sc->state].master) {
		sc->error = IIC_ETIMEOUT;
		GLXIIC_WAKEUP(sc);
	} else {
		error = IIC_ETIMEOUT;
		iicbus_intr(sc->iicbus, INTR_ERROR, &error);
	}

	glxiic_smb_disable(sc);
	glxiic_smb_enable(sc, IIC_UNKNOWN, sc->addr);
	glxiic_set_state_locked(sc, GLXIIC_STATE_IDLE);
}