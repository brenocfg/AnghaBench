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
struct bhndb_resources {size_t dwa_count; struct bhndb_dw_alloc* dw_alloc; } ;
struct bhndb_dw_alloc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * bhndb_dw_find_resource_entry (struct bhndb_dw_alloc*,struct resource*) ; 
 scalar_t__ bhndb_dw_is_free (struct bhndb_resources*,struct bhndb_dw_alloc*) ; 

struct bhndb_dw_alloc *
bhndb_dw_find_resource(struct bhndb_resources *br, struct resource *r)
{
	struct bhndb_dw_alloc	*dwa;

	for (size_t i = 0; i < br->dwa_count; i++) {
		dwa = &br->dw_alloc[i];

		/* Skip free dynamic windows */
		if (bhndb_dw_is_free(br, dwa))
			continue;

		/* Matching allocation found? */
		if (bhndb_dw_find_resource_entry(dwa, r) != NULL)
			return (dwa);
	}

	return (NULL);
}