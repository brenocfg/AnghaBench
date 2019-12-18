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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 struct lock_file LOCK_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ commit_lock_file (struct lock_file*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int error_errno (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  git_path_head_file () ; 
 int hold_lock_file_for_update (struct lock_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int save_head(const char *head)
{
	struct lock_file head_lock = LOCK_INIT;
	struct strbuf buf = STRBUF_INIT;
	int fd;
	ssize_t written;

	fd = hold_lock_file_for_update(&head_lock, git_path_head_file(), 0);
	if (fd < 0)
		return error_errno(_("could not lock HEAD"));
	strbuf_addf(&buf, "%s\n", head);
	written = write_in_full(fd, buf.buf, buf.len);
	strbuf_release(&buf);
	if (written < 0) {
		error_errno(_("could not write to '%s'"), git_path_head_file());
		rollback_lock_file(&head_lock);
		return -1;
	}
	if (commit_lock_file(&head_lock) < 0)
		return error(_("failed to finalize '%s'"), git_path_head_file());
	return 0;
}