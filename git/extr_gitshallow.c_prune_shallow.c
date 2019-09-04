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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct lock_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 unsigned int PRUNE_QUICK ; 
 unsigned int PRUNE_SHOW_ONLY ; 
 unsigned int QUICK ; 
 unsigned int SEEN_ONLY ; 
 struct strbuf STRBUF_INIT ; 
 unsigned int VERBOSE ; 
 int /*<<< orphan*/  check_shallow_file_for_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_lock_file_path (struct lock_file*) ; 
 int /*<<< orphan*/  git_path_shallow (int /*<<< orphan*/ ) ; 
 int hold_lock_file_for_update (struct lock_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_shallow_commits_1 (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

void prune_shallow(unsigned options)
{
	struct lock_file shallow_lock = LOCK_INIT;
	struct strbuf sb = STRBUF_INIT;
	unsigned flags = SEEN_ONLY;
	int fd;

	if (options & PRUNE_QUICK)
		flags |= QUICK;

	if (options & PRUNE_SHOW_ONLY) {
		flags |= VERBOSE;
		write_shallow_commits_1(&sb, 0, NULL, flags);
		strbuf_release(&sb);
		return;
	}
	fd = hold_lock_file_for_update(&shallow_lock,
				       git_path_shallow(the_repository),
				       LOCK_DIE_ON_ERROR);
	check_shallow_file_for_update(the_repository);
	if (write_shallow_commits_1(&sb, 0, NULL, flags)) {
		if (write_in_full(fd, sb.buf, sb.len) < 0)
			die_errno("failed to write to %s",
				  get_lock_file_path(&shallow_lock));
		commit_lock_file(&shallow_lock);
	} else {
		unlink(git_path_shallow(the_repository));
		rollback_lock_file(&shallow_lock);
	}
	strbuf_release(&sb);
}