#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  content_len; int /*<<< orphan*/  content; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ git_diff_line ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff_delta ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_LINE_ADDITION ; 
 int /*<<< orphan*/  GIT_DIFF_LINE_CONTEXT ; 
 int /*<<< orphan*/  GIT_DIFF_LINE_DELETION ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int git_buf_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_diff_print_callback__to_buf(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	const git_diff_line *line,
	void *payload)
{
	git_buf *output = payload;
	GIT_UNUSED(delta); GIT_UNUSED(hunk);

	if (!output) {
		git_error_set(GIT_ERROR_INVALID, "buffer pointer must be provided");
		return -1;
	}

	if (line->origin == GIT_DIFF_LINE_ADDITION ||
		line->origin == GIT_DIFF_LINE_DELETION ||
		line->origin == GIT_DIFF_LINE_CONTEXT)
		git_buf_putc(output, line->origin);

	return git_buf_put(output, line->content, line->content_len);
}