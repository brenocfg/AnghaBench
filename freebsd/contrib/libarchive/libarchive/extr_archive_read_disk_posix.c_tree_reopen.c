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
struct tree {int entry_fd; int initial_filesystem_id; int maxOpenCount; int openCount; scalar_t__ initial_dir_fd; int /*<<< orphan*/  working_dir_fd; TYPE_1__* stack; scalar_t__ entry_remaining_bytes; scalar_t__ entry_eof; int /*<<< orphan*/  path; int /*<<< orphan*/  initial_symlink_mode; int /*<<< orphan*/  symlink_mode; int /*<<< orphan*/  d; int /*<<< orphan*/ * current; scalar_t__ descend; scalar_t__ depth; scalar_t__ dirname_length; scalar_t__ tree_errno; scalar_t__ visit_type; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_DIR_HANDLE ; 
 int const O_CLOEXEC ; 
 int O_EXEC ; 
 int O_PATH ; 
 int const O_RDONLY ; 
 int O_SEARCH ; 
 int /*<<< orphan*/  __archive_ensure_cloexec_flag (scalar_t__) ; 
 int /*<<< orphan*/  archive_string_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  needsFirstVisit ; 
 int /*<<< orphan*/  needsRestoreTimes ; 
 int /*<<< orphan*/  onInitialDir ; 
 void* open (char*,int const) ; 
 int /*<<< orphan*/  tree_dup (scalar_t__) ; 
 int /*<<< orphan*/  tree_push (struct tree*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tree *
tree_reopen(struct tree *t, const char *path, int restore_time)
{
#if defined(O_PATH)
	/* Linux */
	const int o_flag = O_PATH;
#elif defined(O_SEARCH)
	/* SunOS */
	const int o_flag = O_SEARCH;
#elif defined(O_EXEC)
	/* FreeBSD */
	const int o_flag = O_EXEC;
#endif

	t->flags = (restore_time != 0)?needsRestoreTimes:0;
	t->flags |= onInitialDir;
	t->visit_type = 0;
	t->tree_errno = 0;
	t->dirname_length = 0;
	t->depth = 0;
	t->descend = 0;
	t->current = NULL;
	t->d = INVALID_DIR_HANDLE;
	t->symlink_mode = t->initial_symlink_mode;
	archive_string_empty(&t->path);
	t->entry_fd = -1;
	t->entry_eof = 0;
	t->entry_remaining_bytes = 0;
	t->initial_filesystem_id = -1;

	/* First item is set up a lot like a symlink traversal. */
	tree_push(t, path, 0, 0, 0, NULL);
	t->stack->flags = needsFirstVisit;
	t->maxOpenCount = t->openCount = 1;
	t->initial_dir_fd = open(".", O_RDONLY | O_CLOEXEC);
#if defined(O_PATH) || defined(O_SEARCH) || defined(O_EXEC)
	/*
	 * Most likely reason to fail opening "." is that it's not readable,
	 * so try again for execute. The consequences of not opening this are
	 * unhelpful and unnecessary errors later.
	 */
	if (t->initial_dir_fd < 0)
		t->initial_dir_fd = open(".", o_flag | O_CLOEXEC);
#endif
	__archive_ensure_cloexec_flag(t->initial_dir_fd);
	t->working_dir_fd = tree_dup(t->initial_dir_fd);
	return (t);
}