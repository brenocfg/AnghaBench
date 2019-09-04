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
struct pathspec {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int ADD_CACHE_RENORMALIZE ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int add_file_to_cache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ce_path_match (int /*<<< orphan*/ *,struct cache_entry*,struct pathspec const*,int /*<<< orphan*/ *) ; 
 scalar_t__ ce_stage (struct cache_entry*) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static int renormalize_tracked_files(const struct pathspec *pathspec, int flags)
{
	int i, retval = 0;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];

		if (ce_stage(ce))
			continue; /* do not touch unmerged paths */
		if (!S_ISREG(ce->ce_mode) && !S_ISLNK(ce->ce_mode))
			continue; /* do not touch non blobs */
		if (pathspec && !ce_path_match(&the_index, ce, pathspec, NULL))
			continue;
		retval |= add_file_to_cache(ce->name, flags | ADD_CACHE_RENORMALIZE);
	}

	return retval;
}