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
struct object_id {int dummy; } ;
struct lock_file {int dummy; } ;
struct index_state {scalar_t__ cache_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int WRITE_TREE_IGNORE_CACHE_TREE ; 
 int WRITE_TREE_UNREADABLE_INDEX ; 
 scalar_t__ cache_tree_fully_valid (scalar_t__) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 int /*<<< orphan*/  hold_lock_file_for_update (struct lock_file*,char const*,int /*<<< orphan*/ ) ; 
 int read_index_from (struct index_state*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int write_index_as_tree_internal (struct object_id*,struct index_state*,int,int,char const*) ; 
 int /*<<< orphan*/  write_locked_index (struct index_state*,struct lock_file*,int /*<<< orphan*/ ) ; 

int write_index_as_tree(struct object_id *oid, struct index_state *index_state, const char *index_path, int flags, const char *prefix)
{
	int entries, was_valid;
	struct lock_file lock_file = LOCK_INIT;
	int ret;

	hold_lock_file_for_update(&lock_file, index_path, LOCK_DIE_ON_ERROR);

	entries = read_index_from(index_state, index_path, get_git_dir());
	if (entries < 0) {
		ret = WRITE_TREE_UNREADABLE_INDEX;
		goto out;
	}

	was_valid = !(flags & WRITE_TREE_IGNORE_CACHE_TREE) &&
		    index_state->cache_tree &&
		    cache_tree_fully_valid(index_state->cache_tree);

	ret = write_index_as_tree_internal(oid, index_state, was_valid, flags,
					   prefix);
	if (!ret && !was_valid) {
		write_locked_index(index_state, &lock_file, COMMIT_LOCK);
		/* Not being able to write is fine -- we are only interested
		 * in updating the cache-tree part, and if the next caller
		 * ends up using the old index with unupdated cache-tree part
		 * it misses the work we did here, but that is just a
		 * performance penalty and not a big deal.
		 */
	}

out:
	rollback_lock_file(&lock_file);
	return ret;
}