#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wt_status {int /*<<< orphan*/  fp; scalar_t__ display_comment_prefix; int /*<<< orphan*/  ahead_behind_flags; int /*<<< orphan*/  branch; int /*<<< orphan*/  is_initial; } ;
struct strbuf {char* buf; } ;
struct branch {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct branch* branch_get (char const*) ; 
 int /*<<< orphan*/  color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  color_fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 char comment_line_char ; 
 int /*<<< orphan*/  format_tracking_info (struct branch*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void wt_longstatus_print_tracking(struct wt_status *s)
{
	struct strbuf sb = STRBUF_INIT;
	const char *cp, *ep, *branch_name;
	struct branch *branch;
	char comment_line_string[3];
	int i;

	assert(s->branch && !s->is_initial);
	if (!skip_prefix(s->branch, "refs/heads/", &branch_name))
		return;
	branch = branch_get(branch_name);
	if (!format_tracking_info(branch, &sb, s->ahead_behind_flags))
		return;

	i = 0;
	if (s->display_comment_prefix) {
		comment_line_string[i++] = comment_line_char;
		comment_line_string[i++] = ' ';
	}
	comment_line_string[i] = '\0';

	for (cp = sb.buf; (ep = strchr(cp, '\n')) != NULL; cp = ep + 1)
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER, s),
				 "%s%.*s", comment_line_string,
				 (int)(ep - cp), cp);
	if (s->display_comment_prefix)
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER, s), "%c",
				 comment_line_char);
	else
		fputs("\n", s->fp);
	strbuf_release(&sb);
}