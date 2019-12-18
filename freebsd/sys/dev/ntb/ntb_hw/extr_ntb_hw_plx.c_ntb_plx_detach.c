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
struct ntb_plx_softc {int mw_count; int /*<<< orphan*/  conf_res; int /*<<< orphan*/  conf_rid; struct ntb_plx_mw_info* mw_info; } ;
struct ntb_plx_mw_info {int /*<<< orphan*/  mw_res; int /*<<< orphan*/  mw_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_plx_teardown_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ntb_plx_detach(device_t dev)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);
	struct ntb_plx_mw_info *mw;
	int i;

	/* Detach & delete all children */
	ntb_unregister_device(dev);

	/* Disable and free interrupts. */
	ntb_plx_teardown_intr(dev);

	/* Free memory resources. */
	for (i = 0; i < sc->mw_count; i++) {
		mw = &sc->mw_info[i];
		bus_release_resource(dev, SYS_RES_MEMORY, mw->mw_rid,
		    mw->mw_res);
	}
	bus_release_resource(dev, SYS_RES_MEMORY, sc->conf_rid, sc->conf_res);
	return (0);
}