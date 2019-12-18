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
typedef  scalar_t__ u_char ;
struct iicbus_softc {scalar_t__ started; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IICBUS_REPEATED_START (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int IIC_ESTATUS ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

int
iicbus_repeated_start(device_t bus, u_char slave, int timeout)
{
	struct iicbus_softc *sc = (struct iicbus_softc *)device_get_softc(bus);
	int error = 0;

	if (!sc->started)
		return (IIC_ESTATUS); /* protocol error, bus not started */

	if (!(error = IICBUS_REPEATED_START(device_get_parent(bus), slave, timeout)))
		sc->started = slave;
	else
		sc->started = 0;

	return (error);
}