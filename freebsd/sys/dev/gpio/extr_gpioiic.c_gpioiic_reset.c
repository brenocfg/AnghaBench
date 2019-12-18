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
typedef  int /*<<< orphan*/  u_char ;
struct gpioiic_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_ENOADDR ; 
 struct gpioiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpioiic_reset_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpioiic_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct gpioiic_softc		*sc;

	sc = device_get_softc(dev);
	gpioiic_reset_bus(sc->sc_dev);

	return (IIC_ENOADDR);
}