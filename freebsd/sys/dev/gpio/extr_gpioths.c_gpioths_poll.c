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
struct gpioths_softc {int /*<<< orphan*/  callout; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int GPIOTHS_POLLTIME ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_parent (scalar_t__) ; 
 struct gpioths_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  gpioths_dht_readbytes (int /*<<< orphan*/ ,scalar_t__) ; 
 int hz ; 

__attribute__((used)) static void
gpioths_poll(void *arg)
{
	struct gpioths_softc	*sc;
	device_t		 dev;

	dev = (device_t)arg;
	sc = device_get_softc(dev);

	gpioths_dht_readbytes(device_get_parent(dev), dev);
	callout_schedule(&sc->callout, GPIOTHS_POLLTIME * hz);
}