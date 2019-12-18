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
struct bhndb_softc {int /*<<< orphan*/  parent_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_ACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/ * bhndb_get_rman (struct bhndb_softc*,int /*<<< orphan*/ ,int) ; 
 int bhndb_try_activate_resource (struct bhndb_softc*,int /*<<< orphan*/ ,int,int,struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_activate_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{
	struct bhndb_softc *sc = device_get_softc(dev);

	/* Delegate directly to our parent device's bus if the requested
	 * resource type isn't handled locally. */
	if (bhndb_get_rman(sc, child, type) == NULL) {
		return (BUS_ACTIVATE_RESOURCE(device_get_parent(sc->parent_dev),
		    child, type, rid, r));
	}

	return (bhndb_try_activate_resource(sc, child, type, rid, r, NULL));
}