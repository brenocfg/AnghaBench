#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_ENTRY_CHANGED ; 
 int CE_UPDATE_IN_BASE ; 
 TYPE_1__** active_cache ; 
 int /*<<< orphan*/  active_cache_changed ; 
 int cache_name_pos (char const*,int) ; 
 int /*<<< orphan*/  cache_tree_invalidate_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mark_fsmonitor_invalid (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static int mark_ce_flags(const char *path, int flag, int mark)
{
	int namelen = strlen(path);
	int pos = cache_name_pos(path, namelen);
	if (0 <= pos) {
		mark_fsmonitor_invalid(&the_index, active_cache[pos]);
		if (mark)
			active_cache[pos]->ce_flags |= flag;
		else
			active_cache[pos]->ce_flags &= ~flag;
		active_cache[pos]->ce_flags |= CE_UPDATE_IN_BASE;
		cache_tree_invalidate_path(&the_index, path);
		active_cache_changed |= CE_ENTRY_CHANGED;
		return 0;
	}
	return -1;
}