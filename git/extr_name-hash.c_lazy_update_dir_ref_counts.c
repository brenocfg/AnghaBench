#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lazy_entry {TYPE_1__* dir; } ;
struct index_state {int cache_nr; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;

/* Variables and functions */

__attribute__((used)) static inline void lazy_update_dir_ref_counts(
	struct index_state *istate,
	struct lazy_entry *lazy_entries)
{
	int k;

	for (k = 0; k < istate->cache_nr; k++) {
		if (lazy_entries[k].dir)
			lazy_entries[k].dir->nr++;
	}
}