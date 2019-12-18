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
 int ce_stage (struct cache_entry const*) ; 
 int index_name_pos (struct index_state*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int unmerged_mask(struct index_state *istate, const char *path)
{
	int pos, mask;
	const struct cache_entry *ce;

	pos = index_name_pos(istate, path, strlen(path));
	if (0 <= pos)
		return 0;

	mask = 0;
	pos = -pos-1;
	while (pos < istate->cache_nr) {
		ce = istate->cache[pos++];
		if (strcmp(ce->name, path) || !ce_stage(ce))
			break;
		mask |= (1 << (ce_stage(ce) - 1));
	}
	return mask;
}