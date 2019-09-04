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
struct index_state {int /*<<< orphan*/  cache_changed; int /*<<< orphan*/  split_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPLIT_INDEX_ORDERED ; 
 int /*<<< orphan*/  init_split_index (struct index_state*) ; 

void add_split_index(struct index_state *istate)
{
	if (!istate->split_index) {
		init_split_index(istate);
		istate->cache_changed |= SPLIT_INDEX_ORDERED;
	}
}