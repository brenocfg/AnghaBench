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
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_racy_timestamp (struct index_state*,struct cache_entry*) ; 

__attribute__((used)) static int has_racy_timestamp(struct index_state *istate)
{
	int entries = istate->cache_nr;
	int i;

	for (i = 0; i < entries; i++) {
		struct cache_entry *ce = istate->cache[i];
		if (is_racy_timestamp(istate, ce))
			return 1;
	}
	return 0;
}