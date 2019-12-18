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
struct bhndb_resources {size_t dwa_count; struct bhndb_dw_alloc* dw_alloc; } ;
struct bhndb_regwin {scalar_t__ win_size; } ;
struct bhndb_dw_alloc {scalar_t__ target; struct bhndb_regwin* win; } ;
typedef  scalar_t__ bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */

struct bhndb_dw_alloc *
bhndb_dw_find_mapping(struct bhndb_resources *br, bhnd_addr_t addr,
    bhnd_size_t size)
{
	struct bhndb_dw_alloc		*dwr;
	const struct bhndb_regwin	*win;

	/* Search for an existing dynamic mapping of this address range. */
	for (size_t i = 0; i < br->dwa_count; i++) {
		dwr = &br->dw_alloc[i];
		win = dwr->win;

		/* Verify the range */
		if (addr < dwr->target)
			continue;

		if (addr + size > dwr->target + win->win_size)
			continue;

		/* Found a usable mapping */
		return (dwr);
	}

	/* not found */
	return (NULL);
}