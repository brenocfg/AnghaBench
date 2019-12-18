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
struct bhndb_intr_handler {int /*<<< orphan*/  ih_cookiep; struct bhndb_intr_isrc* ih_isrc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_LOCK (struct bhndb_softc*) ; 
 int /*<<< orphan*/  BHNDB_UNLOCK (struct bhndb_softc*) ; 
 int /*<<< orphan*/  bhndb_deregister_intr_handler (int /*<<< orphan*/ ,struct bhndb_intr_handler*) ; 
 struct bhndb_intr_handler* bhndb_find_intr_handler (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bhndb_free_intr_handler (struct bhndb_intr_handler*) ; 
 int /*<<< orphan*/  bhndb_register_intr_handler (int /*<<< orphan*/ ,struct bhndb_intr_handler*) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
bhndb_teardown_intr(device_t dev, device_t child, struct resource *r,
    void *cookiep)
{
	struct bhndb_softc		*sc;
	struct bhndb_intr_handler	*ih;
	struct bhndb_intr_isrc		*isrc;
	int				 error;

	sc = device_get_softc(dev);

	/* Locate and claim ownership of the interrupt handler entry */
	BHNDB_LOCK(sc);

	ih = bhndb_find_intr_handler(sc->bus_res, cookiep);
	if (ih == NULL) {
		panic("%s requested teardown of invalid cookiep %p",
		    device_get_nameunit(child), cookiep);
	}

	bhndb_deregister_intr_handler(sc->bus_res, ih);

	BHNDB_UNLOCK(sc);

	/* Perform actual interrupt teardown via the host isrc */
	isrc = ih->ih_isrc;
	error = bus_teardown_intr(isrc->is_owner, isrc->is_res, ih->ih_cookiep);
	if (error) {
		/* If teardown fails, we need to reinsert the handler entry
		 * to allow later teardown */
		BHNDB_LOCK(sc);
		bhndb_register_intr_handler(sc->bus_res, ih);
		BHNDB_UNLOCK(sc);

		return (error);
	}

	/* Free the entry */
	bhndb_free_intr_handler(ih);
	return (0);
}