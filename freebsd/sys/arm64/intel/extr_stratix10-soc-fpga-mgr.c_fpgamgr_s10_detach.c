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
struct fpgamgr_s10_softc {int /*<<< orphan*/  sx; int /*<<< orphan*/  mgr_cdev_partial; int /*<<< orphan*/  mgr_cdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct fpgamgr_s10_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fpgamgr_s10_detach(device_t dev)
{
	struct fpgamgr_s10_softc *sc;

	sc = device_get_softc(dev);

	destroy_dev(sc->mgr_cdev);
	destroy_dev(sc->mgr_cdev_partial);

	sx_destroy(&sc->sx);

	return (0);
}