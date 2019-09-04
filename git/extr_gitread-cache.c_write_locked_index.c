#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tempfile {int dummy; } ;
struct TYPE_4__ {int* hash; } ;
struct split_index {TYPE_1__ base_oid; } ;
struct lock_file {int dummy; } ;
struct index_state {int cache_changed; scalar_t__ fsmonitor_last_update; struct split_index* split_index; } ;

/* Variables and functions */
 unsigned int COMMIT_LOCK ; 
 int EXTMASK ; 
 unsigned int SKIP_IF_UNCHANGED ; 
 int SPLIT_INDEX_ORDERED ; 
 scalar_t__ alternate_index_output ; 
 int /*<<< orphan*/  cache_tree_verify (int /*<<< orphan*/ ,struct index_state*) ; 
 int /*<<< orphan*/  delete_tempfile (struct tempfile**) ; 
 int do_write_locked_index (struct index_state*,struct lock_file*,unsigned int) ; 
 int errno ; 
 int /*<<< orphan*/  fill_fsmonitor_bitmap (struct index_state*) ; 
 int /*<<< orphan*/  freshen_shared_index (char const*,int) ; 
 scalar_t__ git_env_bool (char*,int /*<<< orphan*/ ) ; 
 char* git_path (char*,...) ; 
 int /*<<< orphan*/  is_null_oid (TYPE_1__*) ; 
 scalar_t__ is_tempfile_active (struct tempfile*) ; 
 struct tempfile* mks_tempfile_sm (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_to_hex (TYPE_1__*) ; 
 int /*<<< orphan*/  oidclr (TYPE_1__*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ too_many_not_shared_entries (struct index_state*) ; 
 int write_shared_index (struct index_state*,struct tempfile**) ; 
 int write_split_index (struct index_state*,struct lock_file*,unsigned int) ; 

int write_locked_index(struct index_state *istate, struct lock_file *lock,
		       unsigned flags)
{
	int new_shared_index, ret;
	struct split_index *si = istate->split_index;

	if (git_env_bool("GIT_TEST_CHECK_CACHE_TREE", 0))
		cache_tree_verify(the_repository, istate);

	if ((flags & SKIP_IF_UNCHANGED) && !istate->cache_changed) {
		if (flags & COMMIT_LOCK)
			rollback_lock_file(lock);
		return 0;
	}

	if (istate->fsmonitor_last_update)
		fill_fsmonitor_bitmap(istate);

	if (!si || alternate_index_output ||
	    (istate->cache_changed & ~EXTMASK)) {
		if (si)
			oidclr(&si->base_oid);
		ret = do_write_locked_index(istate, lock, flags);
		goto out;
	}

	if (git_env_bool("GIT_TEST_SPLIT_INDEX", 0)) {
		int v = si->base_oid.hash[0];
		if ((v & 15) < 6)
			istate->cache_changed |= SPLIT_INDEX_ORDERED;
	}
	if (too_many_not_shared_entries(istate))
		istate->cache_changed |= SPLIT_INDEX_ORDERED;

	new_shared_index = istate->cache_changed & SPLIT_INDEX_ORDERED;

	if (new_shared_index) {
		struct tempfile *temp;
		int saved_errno;

		/* Same initial permissions as the main .git/index file */
		temp = mks_tempfile_sm(git_path("sharedindex_XXXXXX"), 0, 0666);
		if (!temp) {
			oidclr(&si->base_oid);
			ret = do_write_locked_index(istate, lock, flags);
			goto out;
		}
		ret = write_shared_index(istate, &temp);

		saved_errno = errno;
		if (is_tempfile_active(temp))
			delete_tempfile(&temp);
		errno = saved_errno;

		if (ret)
			goto out;
	}

	ret = write_split_index(istate, lock, flags);

	/* Freshen the shared index only if the split-index was written */
	if (!ret && !new_shared_index && !is_null_oid(&si->base_oid)) {
		const char *shared_index = git_path("sharedindex.%s",
						    oid_to_hex(&si->base_oid));
		freshen_shared_index(shared_index, 1);
	}

out:
	if (flags & COMMIT_LOCK)
		rollback_lock_file(lock);
	return ret;
}