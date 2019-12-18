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
typedef  int uint32_t ;
struct viawd_softc {int /*<<< orphan*/ * wd_res; int /*<<< orphan*/  wd_rid; int /*<<< orphan*/  sb_dev; int /*<<< orphan*/ * ev_tag; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VIAWD_MEM_CTRL ; 
 int VIAWD_MEM_CTRL_ENABLE ; 
 int /*<<< orphan*/  VIAWD_TIMEOUT_SHUTDOWN ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct viawd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int viawd_read_4 (struct viawd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viawd_tmr_set (struct viawd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viawd_tmr_state (struct viawd_softc*,int) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
viawd_detach(device_t dev)
{
	struct viawd_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	/* Deregister event handler. */
	if (sc->ev_tag != NULL)
		EVENTHANDLER_DEREGISTER(watchdog_list, sc->ev_tag);
	sc->ev_tag = NULL;

	/*
	 * Do not stop the watchdog on shutdown if active but bump the
	 * timer to avoid spurious reset.
	 */
	reg = viawd_read_4(sc, VIAWD_MEM_CTRL);
	if (reg & VIAWD_MEM_CTRL_ENABLE) {
		viawd_tmr_set(sc, VIAWD_TIMEOUT_SHUTDOWN);
		viawd_tmr_state(sc, 1);
		device_printf(dev,
		    "Keeping watchog alive during shutdown for %d seconds\n",
		    VIAWD_TIMEOUT_SHUTDOWN);
	}

	if (sc->wd_res != NULL)
		bus_release_resource(sc->sb_dev, SYS_RES_MEMORY,
		    sc->wd_rid, sc->wd_res);

	return (0);
}