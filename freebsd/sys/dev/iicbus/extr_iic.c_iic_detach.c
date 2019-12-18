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
struct iic_softc {scalar_t__ sc_devnode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 struct iic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iic_detach(device_t dev)
{
	struct iic_softc *sc;

	sc = device_get_softc(dev);

	if (sc->sc_devnode)
		destroy_dev(sc->sc_devnode);

	return (0);
}