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
struct bhndb_resources {struct bhndb_dw_alloc* dw_alloc; int /*<<< orphan*/  dwa_count; int /*<<< orphan*/  dwa_freelist; } ;
struct bhndb_dw_alloc {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bit_ffc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline struct bhndb_dw_alloc *
bhndb_dw_next_free(struct bhndb_resources *br)
{
	struct bhndb_dw_alloc	*dw_free;
	int			 bit;

	bit_ffc(br->dwa_freelist, br->dwa_count, &bit);
	if (bit == -1)
		return (NULL);

	dw_free = &br->dw_alloc[bit];

	KASSERT(LIST_EMPTY(&dw_free->refs),
	    ("free list out of sync with refs"));

	return (dw_free);
}