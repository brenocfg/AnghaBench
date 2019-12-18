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
struct bhndb_softc {struct bhndb_resources* bus_res; } ;
struct bhndb_resources {size_t dwa_count; struct bhndb_dw_alloc* dw_alloc; } ;
struct bhndb_dw_alloc {int target; int /*<<< orphan*/  win; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_LOCK (struct bhndb_softc*) ; 
 int BHNDB_SET_WINDOW_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BHNDB_UNLOCK (struct bhndb_softc*) ; 
 scalar_t__ bhndb_dw_is_free (struct bhndb_resources*,struct bhndb_dw_alloc*) ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

int
bhndb_generic_resume(device_t dev)
{
	struct bhndb_softc	*sc;
	struct bhndb_resources	*bus_res;
	struct bhndb_dw_alloc	*dwa;
	int			 error;

	sc = device_get_softc(dev);
	bus_res = sc->bus_res;

	/* Guarantee that all in-use dynamic register windows are mapped to
	 * their previously configured target address. */
	BHNDB_LOCK(sc);
	error = 0;
	for (size_t i = 0; i < bus_res->dwa_count; i++) {
		dwa = &bus_res->dw_alloc[i];
	
		/* Skip regions that were not previously used */
		if (bhndb_dw_is_free(bus_res, dwa) && dwa->target == 0x0)
			continue;

		/* Otherwise, ensure the register window is correct before
		 * any children attempt MMIO */
		error = BHNDB_SET_WINDOW_ADDR(dev, dwa->win, dwa->target);
		if (error)
			break;
	}
	BHNDB_UNLOCK(sc);

	/* Error restoring hardware state; children cannot be safely resumed */
	if (error) {
		device_printf(dev, "Unable to restore hardware configuration; "
		    "cannot resume: %d\n", error);
		return (error);
	}

	return (bus_generic_resume(dev));
}