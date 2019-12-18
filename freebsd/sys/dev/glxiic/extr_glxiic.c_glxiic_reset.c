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
typedef  int /*<<< orphan*/  u_char ;
struct glxiic_softc {size_t state; int /*<<< orphan*/  error; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ master; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_LOCK (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_STATE_IDLE ; 
 int /*<<< orphan*/  GLXIIC_UNLOCK (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_WAKEUP (struct glxiic_softc*) ; 
 int /*<<< orphan*/  IIC_ESTATUS ; 
 int IIC_NOERR ; 
 struct glxiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxiic_set_state_locked (struct glxiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxiic_smb_disable (struct glxiic_softc*) ; 
 int /*<<< orphan*/  glxiic_smb_enable (struct glxiic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* glxiic_state_table ; 

__attribute__((used)) static int
glxiic_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct glxiic_softc *sc;

	sc = device_get_softc(dev);

	GLXIIC_LOCK(sc);

	if (oldaddr != NULL)
		*oldaddr = sc->addr;
	sc->addr = addr;

	/* A disable/enable cycle resets the controller. */
	glxiic_smb_disable(sc);
	glxiic_smb_enable(sc, speed, addr);

	if (glxiic_state_table[sc->state].master) {
		sc->error = IIC_ESTATUS;
		GLXIIC_WAKEUP(sc);
	}
	glxiic_set_state_locked(sc, GLXIIC_STATE_IDLE);

	GLXIIC_UNLOCK(sc);

	return (IIC_NOERR);
}