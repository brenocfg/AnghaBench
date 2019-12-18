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
struct bhndb_intr_isrc {int /*<<< orphan*/  is_res; int /*<<< orphan*/  is_owner; } ;
struct bhndb_intr_handler {int /*<<< orphan*/  ih_cookiep; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_LOCK (struct bhndb_softc*) ; 
 int BHNDB_MAP_INTR_ISRC (int /*<<< orphan*/ ,struct resource*,struct bhndb_intr_isrc**) ; 
 int /*<<< orphan*/  BHNDB_UNLOCK (struct bhndb_softc*) ; 
 int ENOMEM ; 
 struct bhndb_intr_handler* bhndb_alloc_intr_handler (int /*<<< orphan*/ ,struct resource*,struct bhndb_intr_isrc*) ; 
 int /*<<< orphan*/  bhndb_free_intr_handler (struct bhndb_intr_handler*) ; 
 int /*<<< orphan*/  bhndb_register_intr_handler (int /*<<< orphan*/ ,struct bhndb_intr_handler*) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bhndb_setup_intr(device_t dev, device_t child, struct resource *r,
    int flags, driver_filter_t filter, driver_intr_t handler, void *arg,
    void **cookiep)
{
	struct bhndb_softc		*sc;
	struct bhndb_intr_isrc		*isrc;
	struct bhndb_intr_handler	*ih;
	int				 error;

	sc = device_get_softc(dev);

	/* Fetch the isrc */
	if ((error = BHNDB_MAP_INTR_ISRC(dev, r, &isrc))) {
		device_printf(dev, "failed to fetch isrc: %d\n", error);
		return (error);
	}

	/* Allocate new ihandler entry  */
	ih = bhndb_alloc_intr_handler(child, r, isrc);
	if (ih == NULL)
		return (ENOMEM);

	/* Perform actual interrupt setup via the host isrc */
	error = bus_setup_intr(isrc->is_owner, isrc->is_res, flags, filter,
	    handler, arg, &ih->ih_cookiep);
	if (error) {
		bhndb_free_intr_handler(ih);
		return (error);
	}

	/* Add to our interrupt handler list */
	BHNDB_LOCK(sc);
	bhndb_register_intr_handler(sc->bus_res, ih);
	BHNDB_UNLOCK(sc);

	/* Provide the interrupt handler entry as our cookiep value */
	*cookiep = ih;
	return (0);
}