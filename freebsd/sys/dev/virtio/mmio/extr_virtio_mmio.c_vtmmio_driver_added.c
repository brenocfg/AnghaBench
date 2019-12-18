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
struct vtmmio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct vtmmio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_probe_and_attach_child (struct vtmmio_softc*) ; 

__attribute__((used)) static void
vtmmio_driver_added(device_t dev, driver_t *driver)
{
	struct vtmmio_softc *sc;

	sc = device_get_softc(dev);

	vtmmio_probe_and_attach_child(sc);
}