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
struct unpack_trees_options {int /*<<< orphan*/  result; int /*<<< orphan*/  src_index; scalar_t__ dir; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct cache_entry {int ce_flags; } ;
typedef  enum unpack_trees_error_types { ____Placeholder_unpack_trees_error_types } unpack_trees_error_types ;

/* Variables and functions */
 int CE_REMOVE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int add_rejected_path (struct unpack_trees_options*,int,char const*) ; 
 scalar_t__ icase_exists (struct unpack_trees_options*,char const*,int,struct stat*) ; 
 scalar_t__ ignore_case ; 
 struct cache_entry* index_file_exists (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_excluded (scalar_t__,int /*<<< orphan*/ ,char const*,int*) ; 
 scalar_t__ verify_clean_subdirectory (struct cache_entry const*,struct unpack_trees_options*) ; 

__attribute__((used)) static int check_ok_to_remove(const char *name, int len, int dtype,
			      const struct cache_entry *ce, struct stat *st,
			      enum unpack_trees_error_types error_type,
			      struct unpack_trees_options *o)
{
	const struct cache_entry *result;

	/*
	 * It may be that the 'lstat()' succeeded even though
	 * target 'ce' was absent, because there is an old
	 * entry that is different only in case..
	 *
	 * Ignore that lstat() if it matches.
	 */
	if (ignore_case && icase_exists(o, name, len, st))
		return 0;

	if (o->dir &&
	    is_excluded(o->dir, o->src_index, name, &dtype))
		/*
		 * ce->name is explicitly excluded, so it is Ok to
		 * overwrite it.
		 */
		return 0;
	if (S_ISDIR(st->st_mode)) {
		/*
		 * We are checking out path "foo" and
		 * found "foo/." in the working tree.
		 * This is tricky -- if we have modified
		 * files that are in "foo/" we would lose
		 * them.
		 */
		if (verify_clean_subdirectory(ce, o) < 0)
			return -1;
		return 0;
	}

	/*
	 * The previous round may already have decided to
	 * delete this path, which is in a subdirectory that
	 * is being replaced with a blob.
	 */
	result = index_file_exists(&o->result, name, len, 0);
	if (result) {
		if (result->ce_flags & CE_REMOVE)
			return 0;
	}

	return add_rejected_path(o, error_type, name);
}