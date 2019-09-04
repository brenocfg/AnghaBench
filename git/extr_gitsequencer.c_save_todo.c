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
struct TYPE_2__ {scalar_t__ len; scalar_t__ buf; } ;
struct todo_list {int current; TYPE_1__ buf; } ;
struct replay_opts {int dummy; } ;
struct lock_file {int dummy; } ;

/* Variables and functions */
 struct lock_file LOCK_INIT ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ close (int) ; 
 scalar_t__ commit_lock_file (struct lock_file*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ get_item_line (struct todo_list*,int) ; 
 scalar_t__ get_item_line_length (struct todo_list*,int) ; 
 int get_item_line_offset (struct todo_list*,int) ; 
 char* get_todo_path (struct replay_opts*) ; 
 int hold_lock_file_for_update (struct lock_file*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_rebase_i (struct replay_opts*) ; 
 int open (char const*,int,int) ; 
 char* rebase_path_done () ; 
 scalar_t__ write_in_full (int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int save_todo(struct todo_list *todo_list, struct replay_opts *opts)
{
	struct lock_file todo_lock = LOCK_INIT;
	const char *todo_path = get_todo_path(opts);
	int next = todo_list->current, offset, fd;

	/*
	 * rebase -i writes "git-rebase-todo" without the currently executing
	 * command, appending it to "done" instead.
	 */
	if (is_rebase_i(opts))
		next++;

	fd = hold_lock_file_for_update(&todo_lock, todo_path, 0);
	if (fd < 0)
		return error_errno(_("could not lock '%s'"), todo_path);
	offset = get_item_line_offset(todo_list, next);
	if (write_in_full(fd, todo_list->buf.buf + offset,
			todo_list->buf.len - offset) < 0)
		return error_errno(_("could not write to '%s'"), todo_path);
	if (commit_lock_file(&todo_lock) < 0)
		return error(_("failed to finalize '%s'"), todo_path);

	if (is_rebase_i(opts) && next > 0) {
		const char *done = rebase_path_done();
		int fd = open(done, O_CREAT | O_WRONLY | O_APPEND, 0666);
		int ret = 0;

		if (fd < 0)
			return 0;
		if (write_in_full(fd, get_item_line(todo_list, next - 1),
				  get_item_line_length(todo_list, next - 1))
		    < 0)
			ret = error_errno(_("could not write to '%s'"), done);
		if (close(fd) < 0)
			ret = error_errno(_("failed to finalize '%s'"), done);
		return ret;
	}
	return 0;
}