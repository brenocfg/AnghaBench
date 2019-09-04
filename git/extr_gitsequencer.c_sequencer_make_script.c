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
struct strbuf {int dummy; } ;
struct rev_info {int verbose_header; int max_parents; int cherry_mark; int limited; int reverse; int right_only; int topo_order; int pretty_given; int /*<<< orphan*/  commit_format; int /*<<< orphan*/  sort_order; } ;
struct repository {int dummy; } ;
struct pretty_print_context {int /*<<< orphan*/  output_encoding; int /*<<< orphan*/  fmt; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int PATCHSAME ; 
 int /*<<< orphan*/  REV_SORT_IN_GRAPH_ORDER ; 
 unsigned int TODO_LIST_ABBREVIATE_CMDS ; 
 unsigned int TODO_LIST_KEEP_EMPTY ; 
 unsigned int TODO_LIST_REBASE_MERGES ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  comment_line_char ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_commit_format (char*,struct rev_info*) ; 
 int /*<<< orphan*/  get_log_output_encoding () ; 
 struct commit* get_revision (struct rev_info*) ; 
 int /*<<< orphan*/  git_config_get_string (char*,char**) ; 
 int is_original_commit_empty (struct commit*) ; 
 int make_script_with_merges (struct pretty_print_context*,struct rev_info*,struct strbuf*,unsigned int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  pretty_print_commit (struct pretty_print_context*,struct commit*,struct strbuf*) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,int /*<<< orphan*/ *) ; 
 int setup_revisions (int,char const**,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 char* xstrdup (char*) ; 

int sequencer_make_script(struct repository *r, struct strbuf *out, int argc,
			  const char **argv, unsigned flags)
{
	char *format = NULL;
	struct pretty_print_context pp = {0};
	struct rev_info revs;
	struct commit *commit;
	int keep_empty = flags & TODO_LIST_KEEP_EMPTY;
	const char *insn = flags & TODO_LIST_ABBREVIATE_CMDS ? "p" : "pick";
	int rebase_merges = flags & TODO_LIST_REBASE_MERGES;

	repo_init_revisions(r, &revs, NULL);
	revs.verbose_header = 1;
	if (!rebase_merges)
		revs.max_parents = 1;
	revs.cherry_mark = 1;
	revs.limited = 1;
	revs.reverse = 1;
	revs.right_only = 1;
	revs.sort_order = REV_SORT_IN_GRAPH_ORDER;
	revs.topo_order = 1;

	revs.pretty_given = 1;
	git_config_get_string("rebase.instructionFormat", &format);
	if (!format || !*format) {
		free(format);
		format = xstrdup("%s");
	}
	get_commit_format(format, &revs);
	free(format);
	pp.fmt = revs.commit_format;
	pp.output_encoding = get_log_output_encoding();

	if (setup_revisions(argc, argv, &revs, NULL) > 1)
		return error(_("make_script: unhandled options"));

	if (prepare_revision_walk(&revs) < 0)
		return error(_("make_script: error preparing revisions"));

	if (rebase_merges)
		return make_script_with_merges(&pp, &revs, out, flags);

	while ((commit = get_revision(&revs))) {
		int is_empty  = is_original_commit_empty(commit);

		if (!is_empty && (commit->object.flags & PATCHSAME))
			continue;
		if (!keep_empty && is_empty)
			strbuf_addf(out, "%c ", comment_line_char);
		strbuf_addf(out, "%s %s ", insn,
			    oid_to_hex(&commit->object.oid));
		pretty_print_commit(&pp, commit, out);
		strbuf_addch(out, '\n');
	}
	return 0;
}