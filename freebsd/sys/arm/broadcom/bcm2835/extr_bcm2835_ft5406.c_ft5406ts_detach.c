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
struct ft5406ts_softc {int /*<<< orphan*/  sc_evdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FT5406_LOCK_DESTROY (struct ft5406ts_softc*) ; 
 struct ft5406ts_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ft5406ts_detach(device_t dev)
{
	struct ft5406ts_softc *sc;

	sc = device_get_softc(dev);

	evdev_free(sc->sc_evdev);

	FT5406_LOCK_DESTROY(sc);

	return (0);
}