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
struct bhndb_dw_rentry {struct resource* dw_res; } ;
struct bhndb_dw_alloc {int /*<<< orphan*/  rnid; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bhndb_dw_rentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/ * bhndb_dw_find_resource_entry (struct bhndb_dw_alloc*,struct resource*) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_link ; 
 struct bhndb_dw_rentry* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bhndb_dw_retain(struct bhndb_resources *br, struct bhndb_dw_alloc *dwa,
    struct resource *res)
{
	struct bhndb_dw_rentry *rentry;

	KASSERT(bhndb_dw_find_resource_entry(dwa, res) == NULL,
	    ("double-retain of dynamic window for same resource"));

	/* Insert a reference entry; we use M_NOWAIT to allow use from
	 * within a non-sleepable lock */
	rentry = malloc(sizeof(*rentry), M_BHND, M_NOWAIT);
	if (rentry == NULL)
		return (ENOMEM);

	rentry->dw_res = res;
	LIST_INSERT_HEAD(&dwa->refs, rentry, dw_link);

	/* Update the free list */
	bit_set(br->dwa_freelist, dwa->rnid);
 
	return (0);
}