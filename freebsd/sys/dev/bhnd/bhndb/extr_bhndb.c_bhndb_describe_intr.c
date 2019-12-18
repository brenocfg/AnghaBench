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
 int BUS_DESCRIBE_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 struct bhndb_intr_handler* bhndb_find_intr_handler (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
bhndb_describe_intr(device_t dev, device_t child, struct resource *irq,
    void *cookie, const char *descr)
{
	struct bhndb_softc		*sc;
	struct bhndb_intr_handler	*ih;
	struct bhndb_intr_isrc		*isrc;

	sc = device_get_softc(dev);

	/* Locate the interrupt handler entry; the caller owns the handler
	 * reference, and thus our entry is guaranteed to remain valid after
	 * we drop out lock below. */
	BHNDB_LOCK(sc);

	ih = bhndb_find_intr_handler(sc->bus_res, cookie);
	if (ih == NULL) {
		panic("%s requested invalid cookiep %p",
		    device_get_nameunit(child), cookie);
	}

	isrc = ih->ih_isrc;

	BHNDB_UNLOCK(sc);

	/* Perform the actual request via the host isrc */
	return (BUS_DESCRIBE_INTR(device_get_parent(isrc->is_owner),
	    isrc->is_owner, isrc->is_res, ih->ih_cookiep, descr));
}