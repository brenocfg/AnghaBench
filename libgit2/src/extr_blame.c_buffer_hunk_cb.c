#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {scalar_t__ old_lines; scalar_t__ old_start; scalar_t__ new_start; } ;
typedef  TYPE_1__ git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff_delta ;
struct TYPE_13__ {scalar_t__ orig_start_line_number; } ;
typedef  TYPE_2__ git_blame_hunk ;
struct TYPE_14__ {TYPE_2__* current_hunk; int /*<<< orphan*/  hunks; int /*<<< orphan*/  path; scalar_t__ current_diff_line; } ;
typedef  TYPE_3__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_blame_get_hunk_byline (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hunk_starts_at_or_after_line (TYPE_2__*,scalar_t__) ; 
 TYPE_2__* new_hunk (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* split_hunk_in_vector (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,int) ; 

__attribute__((used)) static int buffer_hunk_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	void *payload)
{
	git_blame *blame = (git_blame*)payload;
	uint32_t wedge_line;

	GIT_UNUSED(delta);

	wedge_line = (hunk->old_lines == 0) ? hunk->new_start : hunk->old_start;
	blame->current_diff_line = wedge_line;

	blame->current_hunk = (git_blame_hunk*)git_blame_get_hunk_byline(blame, wedge_line);
	if (!blame->current_hunk) {
		/* Line added at the end of the file */
		blame->current_hunk = new_hunk(wedge_line, 0, wedge_line, blame->path);
		GIT_ERROR_CHECK_ALLOC(blame->current_hunk);

		git_vector_insert(&blame->hunks, blame->current_hunk);
	} else if (!hunk_starts_at_or_after_line(blame->current_hunk, wedge_line)){
		/* If this hunk doesn't start between existing hunks, split a hunk up so it does */
		blame->current_hunk = split_hunk_in_vector(&blame->hunks, blame->current_hunk,
				wedge_line - blame->current_hunk->orig_start_line_number, true);
		GIT_ERROR_CHECK_ALLOC(blame->current_hunk);
	}

	return 0;
}