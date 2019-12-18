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
typedef  int /*<<< orphan*/  uintmax_t ;
struct bhndb_resources {int /*<<< orphan*/  dw_steal_mtx; } ;
struct bhndb_dw_alloc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int bhndb_dw_set_addr (int /*<<< orphan*/ ,struct bhndb_resources*,struct bhndb_dw_alloc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 

void
bhndb_dw_return_stolen(device_t dev, struct bhndb_resources *br,
    struct bhndb_dw_alloc *dwa, bus_addr_t saved)
{
	int error;

	mtx_assert(&br->dw_steal_mtx, MA_OWNED);

	error = bhndb_dw_set_addr(dev, br, dwa, saved, 0);
	if (error) {
		panic("failed to restore register window target %#jx: %d\n",
		    (uintmax_t)saved, error);
	}

	mtx_unlock_spin(&br->dw_steal_mtx);
}