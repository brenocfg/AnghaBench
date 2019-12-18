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
struct bhndb_resources {int /*<<< orphan*/  dwa_freelist; } ;
struct bhndb_dw_rentry {int dummy; } ;
struct bhndb_dw_alloc {int /*<<< orphan*/  rnid; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bhndb_dw_rentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_BHND ; 
 struct bhndb_dw_rentry* bhndb_dw_find_resource_entry (struct bhndb_dw_alloc*,struct resource*) ; 
 int /*<<< orphan*/  bit_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_link ; 
 int /*<<< orphan*/  free (struct bhndb_dw_rentry*,int /*<<< orphan*/ ) ; 

void
bhndb_dw_release(struct bhndb_resources *br, struct bhndb_dw_alloc *dwa,
    struct resource *r)
{
	struct bhndb_dw_rentry	*rentry;

	/* Find the rentry */
	rentry = bhndb_dw_find_resource_entry(dwa, r);
	KASSERT(rentry != NULL, ("over release of resource entry"));

	LIST_REMOVE(rentry, dw_link);
	free(rentry, M_BHND);

	/* If this was the last reference, update the free list */
	if (LIST_EMPTY(&dwa->refs))
		bit_clear(br->dwa_freelist, dwa->rnid);
}