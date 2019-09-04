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
struct merge_options {TYPE_1__* repo; scalar_t__ call_depth; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ ce_stage (struct cache_entry*) ; 
 scalar_t__ ignore_case ; 
 struct cache_entry* index_file_exists (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ remove_file_from_index (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ remove_path (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int remove_file(struct merge_options *o, int clean,
		       const char *path, int no_wd)
{
	int update_cache = o->call_depth || clean;
	int update_working_directory = !o->call_depth && !no_wd;

	if (update_cache) {
		if (remove_file_from_index(o->repo->index, path))
			return -1;
	}
	if (update_working_directory) {
		if (ignore_case) {
			struct cache_entry *ce;
			ce = index_file_exists(o->repo->index, path, strlen(path),
					       ignore_case);
			if (ce && ce_stage(ce) == 0 && strcmp(path, ce->name))
				return 0;
		}
		if (remove_path(path))
			return -1;
	}
	return 0;
}