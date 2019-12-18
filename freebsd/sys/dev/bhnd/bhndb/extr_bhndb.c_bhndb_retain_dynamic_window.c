#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct bhndb_softc {int /*<<< orphan*/  bus_res; int /*<<< orphan*/  dev; } ;
struct bhndb_dw_alloc {TYPE_1__* win; } ;
typedef  scalar_t__ rman_res_t ;
struct TYPE_2__ {scalar_t__ win_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_LOCK_ASSERT (struct bhndb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct bhndb_dw_alloc* bhndb_dw_find_mapping (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct bhndb_dw_alloc* bhndb_dw_next_free (int /*<<< orphan*/ ) ; 
 scalar_t__ bhndb_dw_retain (int /*<<< orphan*/ ,struct bhndb_dw_alloc*,struct resource*) ; 
 int bhndb_dw_set_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhndb_dw_alloc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__,int) ; 
 scalar_t__ rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 

__attribute__((used)) static struct bhndb_dw_alloc *
bhndb_retain_dynamic_window(struct bhndb_softc *sc, struct resource *r)
{
	struct bhndb_dw_alloc	*dwa;
	rman_res_t		 r_start, r_size;
	int			 error;

	BHNDB_LOCK_ASSERT(sc, MA_OWNED);

	r_start = rman_get_start(r);
	r_size = rman_get_size(r);

	/* Look for an existing dynamic window we can reference */
	dwa = bhndb_dw_find_mapping(sc->bus_res, r_start, r_size);
	if (dwa != NULL) {
		if (bhndb_dw_retain(sc->bus_res, dwa, r) == 0)
			return (dwa);

		return (NULL);
	}

	/* Otherwise, try to reserve a free window */
	dwa = bhndb_dw_next_free(sc->bus_res);
	if (dwa == NULL) {
		/* No free windows */
		return (NULL);
	}

	/* Window must be large enough to map the entire resource */
	if (dwa->win->win_size < rman_get_size(r))
		return (NULL);

	/* Set the window target */
	error = bhndb_dw_set_addr(sc->dev, sc->bus_res, dwa, rman_get_start(r),
	    rman_get_size(r));
	if (error) {
		device_printf(sc->dev, "dynamic window initialization "
			"for 0x%llx-0x%llx failed: %d\n",
			(unsigned long long) r_start,
			(unsigned long long) r_start + r_size - 1,
			error);
		return (NULL);
	}

	/* Add our reservation */
	if (bhndb_dw_retain(sc->bus_res, dwa, r))
		return (NULL);

	return (dwa);
}