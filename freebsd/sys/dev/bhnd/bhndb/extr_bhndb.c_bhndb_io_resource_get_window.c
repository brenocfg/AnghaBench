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
struct bhndb_regwin {scalar_t__ win_type; scalar_t__ win_size; } ;
struct bhndb_region {int alloc_flags; } ;
struct bhndb_dw_alloc {scalar_t__ target; struct bhndb_regwin* win; } ;
typedef  scalar_t__ bus_size_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int BHNDB_ALLOC_FULFILL_ON_OVERCOMMIT ; 
 int /*<<< orphan*/  BHNDB_LOCK_ASSERT (struct bhndb_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ BHNDB_REGWIN_T_DYN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct bhndb_dw_alloc* bhndb_dw_next_free (struct bhndb_resources*) ; 
 struct bhndb_dw_alloc* bhndb_dw_steal (struct bhndb_resources*,scalar_t__*) ; 
 struct bhndb_region* bhndb_find_resource_region (struct bhndb_resources*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,unsigned long long,scalar_t__) ; 

__attribute__((used)) static struct bhndb_dw_alloc *
bhndb_io_resource_get_window(struct bhndb_softc *sc, bus_addr_t addr,
    bus_size_t size, bool *borrowed, bool *stolen, bus_addr_t *restore)
{
	struct bhndb_resources	*br;
	struct bhndb_dw_alloc	*dwa;
	struct bhndb_region	*region;

	BHNDB_LOCK_ASSERT(sc, MA_OWNED);

	br = sc->bus_res;
	*borrowed = false;
	*stolen = false;

	/* Try to fetch a free window */
	if ((dwa = bhndb_dw_next_free(br)) != NULL)
		return (dwa);

	/* Search for an existing dynamic mapping of this address range.
	 * Static regions are not searched, as a statically mapped
	 * region would never be allocated as an indirect resource. */
	for (size_t i = 0; i < br->dwa_count; i++) {
		const struct bhndb_regwin *win;

		dwa = &br->dw_alloc[i];
		win = dwa->win;

		KASSERT(win->win_type == BHNDB_REGWIN_T_DYN,
			("invalid register window type"));

		/* Verify the range */
		if (addr < dwa->target)
			continue;

		if (addr + size > dwa->target + win->win_size)
			continue;

		/* Found */
		*borrowed = true;
		return (dwa);
	}

	/* Try to steal a window; this should only be required on very early
	 * PCI_V0 (BCM4318, etc) Wi-Fi chipsets */
	region = bhndb_find_resource_region(br, addr, size);
	if (region == NULL)
		return (NULL);

	if ((region->alloc_flags & BHNDB_ALLOC_FULFILL_ON_OVERCOMMIT) == 0)
		return (NULL);

	/* Steal a window. This acquires our backing spinlock, disabling
	 * interrupts; the spinlock will be released by
	 * bhndb_dw_return_stolen() */
	if ((dwa = bhndb_dw_steal(br, restore)) != NULL) {
		*stolen = true;
		return (dwa);
	}

	panic("register windows exhausted attempting to map 0x%llx-0x%llx\n", 
	    (unsigned long long) addr, (unsigned long long) addr+size-1);
}