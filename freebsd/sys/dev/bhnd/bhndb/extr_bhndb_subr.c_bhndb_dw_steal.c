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
struct bhndb_resources {scalar_t__ dwa_count; struct bhndb_dw_alloc* dw_alloc; int /*<<< orphan*/  dw_steal_mtx; } ;
struct bhndb_dw_alloc {int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * bhndb_dw_next_free (struct bhndb_resources*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 

struct bhndb_dw_alloc *
bhndb_dw_steal(struct bhndb_resources *br, bus_addr_t *saved)
{
	struct bhndb_dw_alloc *dw_stolen;

	KASSERT(bhndb_dw_next_free(br) == NULL,
	    ("attempting to steal an in-use window while free windows remain"));

	/* Nothing to steal from? */
	if (br->dwa_count == 0)
		return (NULL);

	/*
	 * Acquire our steal spinlock; this will be released in
	 * bhndb_dw_return_stolen().
	 * 
	 * Acquiring also disables interrupts, which is required when one is
	 * stealing an in-use existing register window.
	 */
	mtx_lock_spin(&br->dw_steal_mtx);

	dw_stolen = &br->dw_alloc[0];
	*saved = dw_stolen->target;
	return (dw_stolen);
}