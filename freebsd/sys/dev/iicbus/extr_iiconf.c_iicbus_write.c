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
struct iicbus_softc {int started; scalar_t__ strict; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IICBUS_WRITE (int /*<<< orphan*/ ,char const*,int,int*,int) ; 
 int IIC_ESTATUS ; 
 int LSB ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

int
iicbus_write(device_t bus, const char *buf, int len, int *sent, int timeout)
{
	struct iicbus_softc *sc = (struct iicbus_softc *)device_get_softc(bus);
	
	/* a slave must have been started for writing */
	if (sc->started == 0 || (sc->strict != 0 && (sc->started & LSB) != 0))
		return (IIC_ESTATUS);

	return (IICBUS_WRITE(device_get_parent(bus), buf, len, sent, timeout));
}