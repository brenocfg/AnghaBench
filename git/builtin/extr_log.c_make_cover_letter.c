#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct shortlog {int wrap_lines; int in1; int in2; int /*<<< orphan*/  file; int /*<<< orphan*/  wrap; } ;
struct TYPE_4__ {int /*<<< orphan*/  file; int /*<<< orphan*/  use_color; } ;
struct rev_info {int /*<<< orphan*/  creation_factor; int /*<<< orphan*/  rdiff2; scalar_t__ rdiff1; int /*<<< orphan*/  rdiff_title; TYPE_2__ diffopt; int /*<<< orphan*/  idiff_title; scalar_t__ idiff_oid1; scalar_t__ numbered_files; int /*<<< orphan*/  commit_format; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct pretty_print_context {int print_email_subject; struct rev_info* rev; TYPE_1__ date_mode; int /*<<< orphan*/  fmt; int /*<<< orphan*/  after_subject; int /*<<< orphan*/  member_0; } ;
struct diff_options {int /*<<< orphan*/  use_color; int /*<<< orphan*/  file; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_EMAIL ; 
 int /*<<< orphan*/  DATE_RFC2822 ; 
 int /*<<< orphan*/  MAIL_DEFAULT_WRAP ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  cmit_fmt_is_mail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_setup (struct diff_options*) ; 
 int /*<<< orphan*/  diff_setup_done (struct diff_options*) ; 
 char* find_branch_name (struct rev_info*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 char* git_committer_info (int /*<<< orphan*/ ) ; 
 scalar_t__ has_non_ascii (char const*) ; 
 int /*<<< orphan*/  log_write_email_headers (struct rev_info*,struct commit*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ open_next_file (int /*<<< orphan*/ *,char*,struct rev_info*,int) ; 
 int /*<<< orphan*/  pp_user_info (struct pretty_print_context*,int /*<<< orphan*/ *,struct strbuf*,char const*,char const*) ; 
 int /*<<< orphan*/  prepare_cover_text (struct pretty_print_context*,char const*,struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  shortlog_add_commit (struct shortlog*,struct commit*) ; 
 int /*<<< orphan*/  shortlog_init (struct shortlog*) ; 
 int /*<<< orphan*/  shortlog_output (struct shortlog*) ; 
 int /*<<< orphan*/  show_diffstat (struct rev_info*,struct commit*,struct commit*) ; 
 int /*<<< orphan*/  show_interdiff (struct rev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_range_diff (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct diff_options*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 

__attribute__((used)) static void make_cover_letter(struct rev_info *rev, int use_stdout,
			      struct commit *origin,
			      int nr, struct commit **list,
			      const char *branch_name,
			      int quiet)
{
	const char *committer;
	struct shortlog log;
	struct strbuf sb = STRBUF_INIT;
	int i;
	const char *encoding = "UTF-8";
	int need_8bit_cte = 0;
	struct pretty_print_context pp = {0};
	struct commit *head = list[0];

	if (!cmit_fmt_is_mail(rev->commit_format))
		die(_("cover letter needs email format"));

	committer = git_committer_info(0);

	if (!use_stdout &&
	    open_next_file(NULL, rev->numbered_files ? NULL : "cover-letter", rev, quiet))
		die(_("failed to create cover-letter file"));

	log_write_email_headers(rev, head, &pp.after_subject, &need_8bit_cte, 0);

	for (i = 0; !need_8bit_cte && i < nr; i++) {
		const char *buf = get_commit_buffer(list[i], NULL);
		if (has_non_ascii(buf))
			need_8bit_cte = 1;
		unuse_commit_buffer(list[i], buf);
	}

	if (!branch_name)
		branch_name = find_branch_name(rev);

	pp.fmt = CMIT_FMT_EMAIL;
	pp.date_mode.type = DATE_RFC2822;
	pp.rev = rev;
	pp.print_email_subject = 1;
	pp_user_info(&pp, NULL, &sb, committer, encoding);
	prepare_cover_text(&pp, branch_name, &sb, encoding, need_8bit_cte);
	fprintf(rev->diffopt.file, "%s\n", sb.buf);

	strbuf_release(&sb);

	shortlog_init(&log);
	log.wrap_lines = 1;
	log.wrap = MAIL_DEFAULT_WRAP;
	log.in1 = 2;
	log.in2 = 4;
	log.file = rev->diffopt.file;
	for (i = 0; i < nr; i++)
		shortlog_add_commit(&log, list[i]);

	shortlog_output(&log);

	/* We can only do diffstat with a unique reference point */
	if (origin)
		show_diffstat(rev, origin, head);

	if (rev->idiff_oid1) {
		fprintf_ln(rev->diffopt.file, "%s", rev->idiff_title);
		show_interdiff(rev, 0);
	}

	if (rev->rdiff1) {
		/*
		 * Pass minimum required diff-options to range-diff; others
		 * can be added later if deemed desirable.
		 */
		struct diff_options opts;
		diff_setup(&opts);
		opts.file = rev->diffopt.file;
		opts.use_color = rev->diffopt.use_color;
		diff_setup_done(&opts);
		fprintf_ln(rev->diffopt.file, "%s", rev->rdiff_title);
		show_range_diff(rev->rdiff1, rev->rdiff2,
				rev->creation_factor, 1, &opts);
	}
}