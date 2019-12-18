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
typedef  int u_int ;
typedef  scalar_t__ u_char ;
struct iicbus_softc {scalar_t__ bus_freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iicbus_softc* IICBUS_SOFTC (int /*<<< orphan*/ ) ; 
 scalar_t__ IIC_SLOW ; 

__attribute__((used)) static u_int
iicbus_get_frequency(device_t dev, u_char speed)
{
	struct iicbus_softc *sc = IICBUS_SOFTC(dev);

	/*
	 * If the frequency has not been configured for the bus, or the request
	 * is specifically for SLOW speed, use the standard 100KHz rate, else
	 * use the configured bus speed.
	 */
	if (sc->bus_freq == 0 || speed == IIC_SLOW)
		return (100000);
	return (sc->bus_freq);
}