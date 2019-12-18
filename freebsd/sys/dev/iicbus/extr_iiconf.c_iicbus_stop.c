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
struct iicbus_softc {scalar_t__ started; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IICBUS_STOP (int /*<<< orphan*/ ) ; 
 int IIC_ESTATUS ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

int
iicbus_stop(device_t bus)
{
	struct iicbus_softc *sc = (struct iicbus_softc *)device_get_softc(bus);
	int error = 0;

	if (!sc->started)
		return (IIC_ESTATUS); /* protocol error, bus not started */

	error = IICBUS_STOP(device_get_parent(bus));

	/* refuse any further access */
	sc->started = 0;

	return (error);
}