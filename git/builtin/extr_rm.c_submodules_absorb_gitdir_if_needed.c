#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;
struct TYPE_4__ {int nr; TYPE_1__* entry; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABSORB_GITDIR_RECURSE_SUBMODULES ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  absorb_git_dir_into_superproject (char const*,int /*<<< orphan*/ ) ; 
 struct cache_entry** active_cache ; 
 int cache_name_pos (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int get_ours_cache_pos (char const*,int) ; 
 scalar_t__ is_empty_dir (char const*) ; 
 TYPE_2__ list ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  submodule_uses_gitfile (char const*) ; 

__attribute__((used)) static void submodules_absorb_gitdir_if_needed(void)
{
	int i;
	for (i = 0; i < list.nr; i++) {
		const char *name = list.entry[i].name;
		int pos;
		const struct cache_entry *ce;

		pos = cache_name_pos(name, strlen(name));
		if (pos < 0) {
			pos = get_ours_cache_pos(name, pos);
			if (pos < 0)
				continue;
		}
		ce = active_cache[pos];

		if (!S_ISGITLINK(ce->ce_mode) ||
		    !file_exists(ce->name) ||
		    is_empty_dir(name))
			continue;

		if (!submodule_uses_gitfile(name))
			absorb_git_dir_into_superproject(name,
				ABSORB_GITDIR_RECURSE_SUBMODULES);
	}
}