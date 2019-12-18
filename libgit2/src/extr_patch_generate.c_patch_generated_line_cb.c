#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  line_count; } ;
typedef  TYPE_2__ git_patch_hunk ;
struct TYPE_12__ {int content_size; int /*<<< orphan*/  context_size; int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; } ;
struct TYPE_14__ {TYPE_1__ base; } ;
typedef  TYPE_3__ git_patch_generated ;
struct TYPE_15__ {scalar_t__ origin; scalar_t__ content_len; } ;
typedef  TYPE_4__ git_diff_line ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff_delta ;

/* Variables and functions */
 scalar_t__ GIT_DIFF_LINE_ADDITION ; 
 scalar_t__ GIT_DIFF_LINE_CONTEXT ; 
 scalar_t__ GIT_DIFF_LINE_CONTEXT_EOFNL ; 
 scalar_t__ GIT_DIFF_LINE_DELETION ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_4__*) ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_4__* git_array_alloc (int /*<<< orphan*/ ) ; 
 TYPE_2__* git_array_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__ const*,int) ; 

__attribute__((used)) static int patch_generated_line_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk_,
	const git_diff_line *line_,
	void *payload)
{
	git_patch_generated  *patch = payload;
	git_patch_hunk *hunk;
	git_diff_line *line;

	GIT_UNUSED(delta);
	GIT_UNUSED(hunk_);

	hunk = git_array_last(patch->base.hunks);
	assert(hunk); /* programmer error if no hunk is available */

	line = git_array_alloc(patch->base.lines);
	GIT_ERROR_CHECK_ALLOC(line);

	memcpy(line, line_, sizeof(*line));

	/* do some bookkeeping so we can provide old/new line numbers */

	patch->base.content_size += line->content_len;

	if (line->origin == GIT_DIFF_LINE_ADDITION ||
		line->origin == GIT_DIFF_LINE_DELETION)
		patch->base.content_size += 1;
	else if (line->origin == GIT_DIFF_LINE_CONTEXT) {
		patch->base.content_size += 1;
		patch->base.context_size += line->content_len + 1;
	} else if (line->origin == GIT_DIFF_LINE_CONTEXT_EOFNL)
		patch->base.context_size += line->content_len;

	hunk->line_count++;

	return 0;
}