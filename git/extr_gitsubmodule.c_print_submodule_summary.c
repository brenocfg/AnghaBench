#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct rev_info {int /*<<< orphan*/  date_mode; } ;
struct repository {int dummy; } ;
struct pretty_print_context {int /*<<< orphan*/  output_encoding; int /*<<< orphan*/  date_mode; int /*<<< orphan*/  member_0; } ;
struct diff_options {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int SYMMETRIC_LEFT ; 
 int /*<<< orphan*/  diff_emit_submodule_add (struct diff_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_emit_submodule_del (struct diff_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_log_output_encoding () ; 
 struct commit* get_revision (struct rev_info*) ; 
 int /*<<< orphan*/  repo_format_commit_message (struct repository*,struct commit*,char const*,struct strbuf*,struct pretty_print_context*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_submodule_summary(struct repository *r, struct rev_info *rev, struct diff_options *o)
{
	static const char format[] = "  %m %s";
	struct strbuf sb = STRBUF_INIT;
	struct commit *commit;

	while ((commit = get_revision(rev))) {
		struct pretty_print_context ctx = {0};
		ctx.date_mode = rev->date_mode;
		ctx.output_encoding = get_log_output_encoding();
		strbuf_setlen(&sb, 0);
		repo_format_commit_message(r, commit, format, &sb,
				      &ctx);
		strbuf_addch(&sb, '\n');
		if (commit->object.flags & SYMMETRIC_LEFT)
			diff_emit_submodule_del(o, sb.buf);
		else
			diff_emit_submodule_add(o, sb.buf);
	}
	strbuf_release(&sb);
}