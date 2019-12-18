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
struct bhndb_resources {int /*<<< orphan*/  dw_steal_mtx; } ;
struct bhndb_regwin {scalar_t__ win_size; } ;
struct bhndb_dw_alloc {int target; struct bhndb_regwin* win; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_size_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int BHNDB_SET_WINDOW_ADDR (int /*<<< orphan*/ ,struct bhndb_regwin*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ bhndb_dw_is_free (struct bhndb_resources*,struct bhndb_dw_alloc*) ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ *) ; 

int
bhndb_dw_set_addr(device_t dev, struct bhndb_resources *br,
    struct bhndb_dw_alloc *dwa, bus_addr_t addr, bus_size_t size)
{
	const struct bhndb_regwin	*rw;
	bus_addr_t			 offset;
	int				 error;

	rw = dwa->win;

	KASSERT(bhndb_dw_is_free(br, dwa) || mtx_owned(&br->dw_steal_mtx),
	    ("attempting to set the target address on an in-use window"));

	/* Page-align the target address */
	offset = addr % rw->win_size;
	dwa->target = addr - offset;

	/* Verify that the window is large enough for the full target */
	if (rw->win_size - offset < size)
		return (ENOMEM);
	
	/* Update the window target */
	error = BHNDB_SET_WINDOW_ADDR(dev, dwa->win, dwa->target);
	if (error) {
		dwa->target = 0x0;
		return (error);
	}

	return (0);
}