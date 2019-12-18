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
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int cache_name_stage_compare (char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry*) ; 

__attribute__((used)) static int index_name_stage_pos(const struct index_state *istate, const char *name, int namelen, int stage)
{
	int first, last;

	first = 0;
	last = istate->cache_nr;
	while (last > first) {
		int next = first + ((last - first) >> 1);
		struct cache_entry *ce = istate->cache[next];
		int cmp = cache_name_stage_compare(name, namelen, stage, ce->name, ce_namelen(ce), ce_stage(ce));
		if (!cmp)
			return next;
		if (cmp < 0) {
			last = next;
			continue;
		}
		first = next+1;
	}
	return -first-1;
}