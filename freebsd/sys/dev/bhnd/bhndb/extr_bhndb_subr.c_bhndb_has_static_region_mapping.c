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
struct bhndb_resources {int dummy; } ;
struct bhndb_region {scalar_t__ size; int /*<<< orphan*/ * static_regwin; } ;
typedef  scalar_t__ bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 struct bhndb_region* bhndb_find_resource_region (struct bhndb_resources*,scalar_t__,int) ; 

bool
bhndb_has_static_region_mapping(struct bhndb_resources *br,
    bhnd_addr_t addr, bhnd_size_t size)
{
	struct bhndb_region	*region;
	bhnd_addr_t		 r_addr;

	r_addr = addr;
	while ((region = bhndb_find_resource_region(br, r_addr, 1)) != NULL) {
		/* Must be backed by a static register window */
		if (region->static_regwin == NULL)
			return (false);

		/* Adjust the search offset */
		r_addr += region->size;

		/* Have we traversed a complete (if discontiguous) mapping? */
		if (r_addr == addr + size)
			return (true);

	}

	/* No complete mapping found */
	return (false);
}