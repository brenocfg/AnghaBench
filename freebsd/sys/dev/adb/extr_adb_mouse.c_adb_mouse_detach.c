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
struct adb_mouse_softc {int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  adb_set_autopoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct adb_mouse_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
adb_mouse_detach(device_t dev) 
{
	struct adb_mouse_softc *sc;

	adb_set_autopoll(dev,0);

	sc = device_get_softc(dev);
	destroy_dev(sc->cdev);

	mtx_destroy(&sc->sc_mtx);
	cv_destroy(&sc->sc_cv);

	return (0);
}