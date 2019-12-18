#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int path_len; int /*<<< orphan*/  is_ignored; } ;
typedef  TYPE_1__ filesystem_iterator_frame ;
struct TYPE_10__ {char* path; } ;
typedef  TYPE_2__ filesystem_iterator_entry ;
struct TYPE_11__ {int /*<<< orphan*/  ignores; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ filesystem_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIR_FLAG_TRUE ; 
 int /*<<< orphan*/  GIT_IGNORE_NOTFOUND ; 
 TYPE_1__* filesystem_iterator_parent_frame (TYPE_3__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_ignore__lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_ignore__push_dir (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  iterator__honor_ignores (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void filesystem_iterator_frame_push_ignores(
	filesystem_iterator *iter,
	filesystem_iterator_entry *frame_entry,
	filesystem_iterator_frame *new_frame)
{
	filesystem_iterator_frame *previous_frame;
	const char *path = frame_entry ? frame_entry->path : "";

	if (!iterator__honor_ignores(&iter->base))
		return;

	if (git_ignore__lookup(&new_frame->is_ignored,
			&iter->ignores, path, GIT_DIR_FLAG_TRUE) < 0) {
		git_error_clear();
		new_frame->is_ignored = GIT_IGNORE_NOTFOUND;
	}

	/* if this is not the top level directory... */
	if (frame_entry) {
		const char *relative_path;

		previous_frame = filesystem_iterator_parent_frame(iter);

		/* push new ignores for files in this directory */
		relative_path = frame_entry->path + previous_frame->path_len;

		/* inherit ignored from parent if no rule specified */
		if (new_frame->is_ignored <= GIT_IGNORE_NOTFOUND)
			new_frame->is_ignored = previous_frame->is_ignored;

		git_ignore__push_dir(&iter->ignores, relative_path);
	}
}