#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ mode; char const* path; } ;
struct TYPE_8__ {scalar_t__ mode; char const* path; } ;
struct TYPE_10__ {TYPE_2__ old_file; TYPE_1__ new_file; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_12__ {int /*<<< orphan*/  content_len; int /*<<< orphan*/  content; int /*<<< orphan*/  origin; } ;
struct TYPE_11__ {int (* strcomp ) (char const*,char const*) ;int flags; int (* print_cb ) (TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; TYPE_6__ line; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_4__ diff_print_info ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_LINE_FILE_HDR ; 
 int GIT_DIFF_SHOW_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_UNUSED (float) ; 
 char diff_pick_suffix (scalar_t__) ; 
 int git__strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char,char const*,...) ; 
 char git_diff_status_char (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_print_one_name_status(
	const git_diff_delta *delta, float progress, void *data)
{
	diff_print_info *pi = data;
	git_buf *out = pi->buf;
	char old_suffix, new_suffix, code = git_diff_status_char(delta->status);
	int(*strcomp)(const char *, const char *) = pi->strcomp ?
		pi->strcomp : git__strcmp;

	GIT_UNUSED(progress);

	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 && code == ' ')
		return 0;

	old_suffix = diff_pick_suffix(delta->old_file.mode);
	new_suffix = diff_pick_suffix(delta->new_file.mode);

	git_buf_clear(out);

	if (delta->old_file.path != delta->new_file.path &&
		strcomp(delta->old_file.path,delta->new_file.path) != 0)
		git_buf_printf(out, "%c\t%s%c %s%c\n", code,
			delta->old_file.path, old_suffix, delta->new_file.path, new_suffix);
	else if (delta->old_file.mode != delta->new_file.mode &&
		delta->old_file.mode != 0 && delta->new_file.mode != 0)
		git_buf_printf(out, "%c\t%s%c %s%c\n", code,
			delta->old_file.path, old_suffix, delta->new_file.path, new_suffix);
	else if (old_suffix != ' ')
		git_buf_printf(out, "%c\t%s%c\n", code, delta->old_file.path, old_suffix);
	else
		git_buf_printf(out, "%c\t%s\n", code, delta->old_file.path);
	if (git_buf_oom(out))
		return -1;

	pi->line.origin      = GIT_DIFF_LINE_FILE_HDR;
	pi->line.content     = git_buf_cstr(out);
	pi->line.content_len = git_buf_len(out);

	return pi->print_cb(delta, NULL, &pi->line, pi->payload);
}