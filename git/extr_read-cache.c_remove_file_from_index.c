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
struct index_state {int cache_nr; TYPE_1__** cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_tree_invalidate_path (struct index_state*,char const*) ; 
 int index_name_pos (struct index_state*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_index_entry_at (struct index_state*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  untracked_cache_remove_from_index (struct index_state*,char const*) ; 

int remove_file_from_index(struct index_state *istate, const char *path)
{
	int pos = index_name_pos(istate, path, strlen(path));
	if (pos < 0)
		pos = -pos-1;
	cache_tree_invalidate_path(istate, path);
	untracked_cache_remove_from_index(istate, path);
	while (pos < istate->cache_nr && !strcmp(istate->cache[pos]->name, path))
		remove_index_entry_at(istate, pos);
	return 0;
}