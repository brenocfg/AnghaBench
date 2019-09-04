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
struct TYPE_9__ {int id_abbrev; scalar_t__ path; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int id_abbrev; scalar_t__ path; scalar_t__ mode; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {scalar_t__ similarity; TYPE_2__ new_file; TYPE_1__ old_file; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_12__ {int /*<<< orphan*/  content_len; int /*<<< orphan*/  content; int /*<<< orphan*/  origin; } ;
struct TYPE_11__ {int flags; int id_strlen; int (* print_cb ) (TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; TYPE_6__ line; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_4__ diff_print_info ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_LINE_FILE_HDR ; 
 int GIT_DIFF_SHOW_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_ERROR_PATCH ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  GIT_UNUSED (float) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 char git_diff_status_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_print_one_raw(
	const git_diff_delta *delta, float progress, void *data)
{
	diff_print_info *pi = data;
	git_buf *out = pi->buf;
	int id_abbrev;
	char code = git_diff_status_char(delta->status);
	char start_oid[GIT_OID_HEXSZ+1], end_oid[GIT_OID_HEXSZ+1];

	GIT_UNUSED(progress);

	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 && code == ' ')
		return 0;

	git_buf_clear(out);

	id_abbrev = delta->old_file.mode ? delta->old_file.id_abbrev :
		delta->new_file.id_abbrev;

	if (pi->id_strlen > id_abbrev) {
		git_error_set(GIT_ERROR_PATCH,
			"the patch input contains %d id characters (cannot print %d)",
			id_abbrev, pi->id_strlen);
		return -1;
	}

	git_oid_tostr(start_oid, pi->id_strlen + 1, &delta->old_file.id);
	git_oid_tostr(end_oid, pi->id_strlen + 1, &delta->new_file.id);

	git_buf_printf(
		out, (pi->id_strlen <= GIT_OID_HEXSZ) ?
			":%06o %06o %s... %s... %c" : ":%06o %06o %s %s %c",
		delta->old_file.mode, delta->new_file.mode, start_oid, end_oid, code);

	if (delta->similarity > 0)
		git_buf_printf(out, "%03u", delta->similarity);

	if (delta->old_file.path != delta->new_file.path)
		git_buf_printf(
			out, "\t%s %s\n", delta->old_file.path, delta->new_file.path);
	else
		git_buf_printf(
			out, "\t%s\n", delta->old_file.path ?
			delta->old_file.path : delta->new_file.path);

	if (git_buf_oom(out))
		return -1;

	pi->line.origin      = GIT_DIFF_LINE_FILE_HDR;
	pi->line.content     = git_buf_cstr(out);
	pi->line.content_len = git_buf_len(out);

	return pi->print_cb(delta, NULL, &pi->line, pi->payload);
}