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
struct safe_softc {scalar_t__ sc_suspended; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct safe_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
safe_resume(device_t dev)
{
	struct safe_softc *sc = device_get_softc(dev);

#ifdef notyet
	/* XXX retore PCI settings and start the device */
#endif
	sc->sc_suspended = 0;
	return (0);
}