#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {scalar_t__ status; TYPE_1__ new_file; } ;
typedef  TYPE_2__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_10__ {int /*<<< orphan*/  content_len; int /*<<< orphan*/  content; int /*<<< orphan*/  origin; } ;
struct TYPE_9__ {int flags; int (* print_cb ) (TYPE_2__ const*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; TYPE_5__ line; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_3__ diff_print_info ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_LINE_FILE_HDR ; 
 int GIT_DIFF_SHOW_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_UNUSED (float) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_print_one_name_only(
	const git_diff_delta *delta, float progress, void *data)
{
	diff_print_info *pi = data;
	git_buf *out = pi->buf;

	GIT_UNUSED(progress);

	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 &&
		delta->status == GIT_DELTA_UNMODIFIED)
		return 0;

	git_buf_clear(out);
	git_buf_puts(out, delta->new_file.path);
	git_buf_putc(out, '\n');
	if (git_buf_oom(out))
		return -1;

	pi->line.origin      = GIT_DIFF_LINE_FILE_HDR;
	pi->line.content     = git_buf_cstr(out);
	pi->line.content_len = git_buf_len(out);

	return pi->print_cb(delta, NULL, &pi->line, pi->payload);
}