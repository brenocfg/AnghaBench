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
struct repository {int /*<<< orphan*/  index; } ;
struct replay_opts {int dummy; } ;
struct lock_file {int dummy; } ;

/* Variables and functions */
 int COMMIT_LOCK ; 
 struct lock_file LOCK_INIT ; 
 int REFRESH_QUIET ; 
 int REFRESH_UNMERGED ; 
 int SKIP_IF_UNCHANGED ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* action_name (struct replay_opts*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_index (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int repo_hold_locked_index (struct repository*,struct lock_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ ,struct lock_file*,int) ; 

__attribute__((used)) static int read_and_refresh_cache(struct repository *r,
				  struct replay_opts *opts)
{
	struct lock_file index_lock = LOCK_INIT;
	int index_fd = repo_hold_locked_index(r, &index_lock, 0);
	if (repo_read_index(r) < 0) {
		rollback_lock_file(&index_lock);
		return error(_("git %s: failed to read the index"),
			_(action_name(opts)));
	}
	refresh_index(r->index, REFRESH_QUIET|REFRESH_UNMERGED, NULL, NULL, NULL);
	if (index_fd >= 0) {
		if (write_locked_index(r->index, &index_lock,
				       COMMIT_LOCK | SKIP_IF_UNCHANGED)) {
			return error(_("git %s: failed to refresh the index"),
				_(action_name(opts)));
		}
	}
	return 0;
}