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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct rev_info {int ignore_merges; int /*<<< orphan*/  commit_format; int /*<<< orphan*/  date_mode; int /*<<< orphan*/  abbrev; } ;
struct pretty_print_context {int /*<<< orphan*/  fmt; int /*<<< orphan*/  date_mode; int /*<<< orphan*/  abbrev; int /*<<< orphan*/  member_0; } ;
struct commit_list {TYPE_1__* item; struct commit_list* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  flags; } ;
struct commit {TYPE_2__ object; } ;
struct TYPE_3__ {TYPE_2__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_MEDIUM ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UNINTERESTING ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct commit* get_revision (struct rev_info*) ; 
 int /*<<< orphan*/  git_path_squash_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  pretty_print_commit (struct pretty_print_context*,struct commit*,struct strbuf*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  write_file_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void squash_message(struct commit *commit, struct commit_list *remoteheads)
{
	struct rev_info rev;
	struct strbuf out = STRBUF_INIT;
	struct commit_list *j;
	struct pretty_print_context ctx = {0};

	printf(_("Squash commit -- not updating HEAD\n"));

	repo_init_revisions(the_repository, &rev, NULL);
	rev.ignore_merges = 1;
	rev.commit_format = CMIT_FMT_MEDIUM;

	commit->object.flags |= UNINTERESTING;
	add_pending_object(&rev, &commit->object, NULL);

	for (j = remoteheads; j; j = j->next)
		add_pending_object(&rev, &j->item->object, NULL);

	setup_revisions(0, NULL, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die(_("revision walk setup failed"));

	ctx.abbrev = rev.abbrev;
	ctx.date_mode = rev.date_mode;
	ctx.fmt = rev.commit_format;

	strbuf_addstr(&out, "Squashed commit of the following:\n");
	while ((commit = get_revision(&rev)) != NULL) {
		strbuf_addch(&out, '\n');
		strbuf_addf(&out, "commit %s\n",
			oid_to_hex(&commit->object.oid));
		pretty_print_commit(&ctx, commit, &out);
	}
	write_file_buf(git_path_squash_msg(the_repository), out.buf, out.len);
	strbuf_release(&out);
}