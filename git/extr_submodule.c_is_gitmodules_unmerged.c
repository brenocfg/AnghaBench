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
 int /*<<< orphan*/  GITMODULES_FILE ; 
 scalar_t__ ce_namelen (struct cache_entry const*) ; 
 int index_name_pos (struct index_state const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int is_gitmodules_unmerged(const struct index_state *istate)
{
	int pos = index_name_pos(istate, GITMODULES_FILE, strlen(GITMODULES_FILE));
	if (pos < 0) { /* .gitmodules not found or isn't merged */
		pos = -1 - pos;
		if (istate->cache_nr > pos) {  /* there is a .gitmodules */
			const struct cache_entry *ce = istate->cache[pos];
			if (ce_namelen(ce) == strlen(GITMODULES_FILE) &&
			    !strcmp(ce->name, GITMODULES_FILE))
				return 1;
		}
	}

	return 0;
}