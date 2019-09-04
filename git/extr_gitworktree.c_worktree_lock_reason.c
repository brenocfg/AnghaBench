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
struct worktree {int lock_reason_valid; char const* lock_reason; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_main_worktree (struct worktree*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 char const* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 int /*<<< orphan*/  worktree_git_path (struct worktree*,char*) ; 

const char *worktree_lock_reason(struct worktree *wt)
{
	assert(!is_main_worktree(wt));

	if (!wt->lock_reason_valid) {
		struct strbuf path = STRBUF_INIT;

		strbuf_addstr(&path, worktree_git_path(wt, "locked"));
		if (file_exists(path.buf)) {
			struct strbuf lock_reason = STRBUF_INIT;
			if (strbuf_read_file(&lock_reason, path.buf, 0) < 0)
				die_errno(_("failed to read '%s'"), path.buf);
			strbuf_trim(&lock_reason);
			wt->lock_reason = strbuf_detach(&lock_reason, NULL);
		} else
			wt->lock_reason = NULL;
		wt->lock_reason_valid = 1;
		strbuf_release(&path);
	}

	return wt->lock_reason;
}