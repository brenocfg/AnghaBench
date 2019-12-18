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
struct resource {int dummy; } ;
struct bhndb_softc {int /*<<< orphan*/  bus_res; } ;
struct bhndb_dw_alloc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BHNDB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHNDB_LOCK (struct bhndb_softc*) ; 
 int /*<<< orphan*/  BHNDB_UNLOCK (struct bhndb_softc*) ; 
 int /*<<< orphan*/  PRIO ; 
 int SYS_RES_MEMORY ; 
 struct bhndb_dw_alloc* bhndb_dw_find_resource (int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  bhndb_dw_release (int /*<<< orphan*/ ,struct bhndb_dw_alloc*,struct resource*) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 

__attribute__((used)) static void
bhndb_suspend_resource(device_t dev, device_t child, int type,
    struct resource *r)
{
	struct bhndb_softc	*sc;
	struct bhndb_dw_alloc	*dwa;

	sc = device_get_softc(dev);

	/* Non-MMIO resources (e.g. IRQs) are handled solely by our parent */
	if (type != SYS_RES_MEMORY)
		return;

	BHNDB_LOCK(sc);
	dwa = bhndb_dw_find_resource(sc->bus_res, r);
	if (dwa == NULL) {
		BHNDB_UNLOCK(sc);
		return;
	}

	if (BHNDB_DEBUG(PRIO))
		device_printf(child, "suspend resource type=%d 0x%jx+0x%jx\n",
		    type, rman_get_start(r), rman_get_size(r));

	/* Release the resource's window reference */
	bhndb_dw_release(sc->bus_res, dwa, r);
	BHNDB_UNLOCK(sc);
}