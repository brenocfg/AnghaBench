#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct patch_id_args {int /*<<< orphan*/  ctx; } ;
struct TYPE_9__ {int origin; int /*<<< orphan*/  content_len; int /*<<< orphan*/  content; } ;
typedef  TYPE_1__ git_diff_line ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff_delta ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
#define  GIT_DIFF_LINE_ADDITION 133 
#define  GIT_DIFF_LINE_ADD_EOFNL 132 
#define  GIT_DIFF_LINE_CONTEXT 131 
#define  GIT_DIFF_LINE_CONTEXT_EOFNL 130 
#define  GIT_DIFF_LINE_DELETION 129 
#define  GIT_DIFF_LINE_DEL_EOFNL 128 
 int /*<<< orphan*/  GIT_ERROR_PATCH ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_2__*,char) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_spaces (TYPE_2__*) ; 

__attribute__((used)) static int patchid_line_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	const git_diff_line *line,
	void *payload)
{
	struct patch_id_args *args = (struct patch_id_args *) payload;
	git_buf buf = GIT_BUF_INIT;
	int error;

	GIT_UNUSED(delta);
	GIT_UNUSED(hunk);

	switch (line->origin) {
	    case GIT_DIFF_LINE_ADDITION:
		git_buf_putc(&buf, '+');
		break;
	    case GIT_DIFF_LINE_DELETION:
		git_buf_putc(&buf, '-');
		break;
	    case GIT_DIFF_LINE_CONTEXT:
		break;
	    case GIT_DIFF_LINE_CONTEXT_EOFNL:
	    case GIT_DIFF_LINE_ADD_EOFNL:
	    case GIT_DIFF_LINE_DEL_EOFNL:
		/*
		 * Ignore EOF without newlines for patch IDs as whitespace is
		 * not supposed to be significant.
		 */
		return 0;
	    default:
		git_error_set(GIT_ERROR_PATCH, "invalid line origin for patch");
		return -1;
	}

	git_buf_put(&buf, line->content, line->content_len);
	strip_spaces(&buf);

	if ((error = git_hash_update(&args->ctx, buf.ptr, buf.size)) < 0)
		goto out;

out:
	git_buf_dispose(&buf);
	return error;
}