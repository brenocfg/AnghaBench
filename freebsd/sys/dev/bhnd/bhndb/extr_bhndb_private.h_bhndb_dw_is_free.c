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
struct bhndb_resources {int /*<<< orphan*/  dwa_freelist; } ;
struct bhndb_dw_alloc {int /*<<< orphan*/  rnid; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bit_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
bhndb_dw_is_free(struct bhndb_resources *br, struct bhndb_dw_alloc *dwa)
{
	bool is_free = LIST_EMPTY(&dwa->refs);

	KASSERT(is_free == !bit_test(br->dwa_freelist, dwa->rnid),
	    ("refs out of sync with free list"));

	return (is_free);
}