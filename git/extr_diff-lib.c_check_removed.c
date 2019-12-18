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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry const*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ has_symlink_leading_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_missing_file_error (int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ resolve_gitlink_ref (int /*<<< orphan*/ ,char*,struct object_id*) ; 

__attribute__((used)) static int check_removed(const struct cache_entry *ce, struct stat *st)
{
	if (lstat(ce->name, st) < 0) {
		if (!is_missing_file_error(errno))
			return -1;
		return 1;
	}
	if (has_symlink_leading_path(ce->name, ce_namelen(ce)))
		return 1;
	if (S_ISDIR(st->st_mode)) {
		struct object_id sub;

		/*
		 * If ce is already a gitlink, we can have a plain
		 * directory (i.e. the submodule is not checked out),
		 * or a checked out submodule.  Either case this is not
		 * a case where something was removed from the work tree,
		 * so we will return 0.
		 *
		 * Otherwise, if the directory is not a submodule
		 * repository, that means ce which was a blob turned into
		 * a directory --- the blob was removed!
		 */
		if (!S_ISGITLINK(ce->ce_mode) &&
		    resolve_gitlink_ref(ce->name, "HEAD", &sub))
			return 1;
	}
	return 0;
}