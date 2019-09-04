#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_2__* items; } ;
struct strbuf {int /*<<< orphan*/  len; } ;
struct TYPE_7__ {scalar_t__ nr; } ;
struct rev_info {TYPE_3__ pending; int /*<<< orphan*/ * commits; } ;
struct pretty_print_context {int /*<<< orphan*/  member_0; } ;
struct object_id {int dummy; } ;
struct origin_data {scalar_t__ is_local_branch; struct object_id oid; } ;
struct object {scalar_t__ type; int flags; struct object_id const oid; } ;
struct fmt_merge_msg_opts {int shortlog_len; scalar_t__ credit_people; } ;
struct commit {struct object object; TYPE_1__* parents; } ;
struct TYPE_8__ {int /*<<< orphan*/  hexsz; } ;
struct TYPE_6__ {char const* string; } ;
struct TYPE_5__ {scalar_t__ next; } ;

/* Variables and functions */
 int ADDED ; 
 scalar_t__ OBJ_COMMIT ; 
 int SEEN ; 
 int SHOWN ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int TREESAME ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  add_branch_desc (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,char const*) ; 
 int /*<<< orphan*/  add_people_info (struct strbuf*,struct string_list*,struct string_list*) ; 
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int) ; 
 struct object* deref_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  format_commit_message (struct commit*,char*,struct strbuf*,struct pretty_print_context*) ; 
 int /*<<< orphan*/  free_commit_list (int /*<<< orphan*/ *) ; 
 struct commit* get_revision (struct rev_info*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  record_person (char,struct string_list*,struct commit*) ; 
 int /*<<< orphan*/  setup_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_ltrim (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_append_nodup (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 TYPE_4__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ use_branch_desc ; 

__attribute__((used)) static void shortlog(const char *name,
		     struct origin_data *origin_data,
		     struct commit *head,
		     struct rev_info *rev,
		     struct fmt_merge_msg_opts *opts,
		     struct strbuf *out)
{
	int i, count = 0;
	struct commit *commit;
	struct object *branch;
	struct string_list subjects = STRING_LIST_INIT_DUP;
	struct string_list authors = STRING_LIST_INIT_DUP;
	struct string_list committers = STRING_LIST_INIT_DUP;
	int flags = UNINTERESTING | TREESAME | SEEN | SHOWN | ADDED;
	struct strbuf sb = STRBUF_INIT;
	const struct object_id *oid = &origin_data->oid;
	int limit = opts->shortlog_len;

	branch = deref_tag(the_repository, parse_object(the_repository, oid),
			   oid_to_hex(oid),
			   the_hash_algo->hexsz);
	if (!branch || branch->type != OBJ_COMMIT)
		return;

	setup_revisions(0, NULL, rev, NULL);
	add_pending_object(rev, branch, name);
	add_pending_object(rev, &head->object, "^HEAD");
	head->object.flags |= UNINTERESTING;
	if (prepare_revision_walk(rev))
		die("revision walk setup failed");
	while ((commit = get_revision(rev)) != NULL) {
		struct pretty_print_context ctx = {0};

		if (commit->parents && commit->parents->next) {
			/* do not list a merge but count committer */
			if (opts->credit_people)
				record_person('c', &committers, commit);
			continue;
		}
		if (!count && opts->credit_people)
			/* the 'tip' committer */
			record_person('c', &committers, commit);
		if (opts->credit_people)
			record_person('a', &authors, commit);
		count++;
		if (subjects.nr > limit)
			continue;

		format_commit_message(commit, "%s", &sb, &ctx);
		strbuf_ltrim(&sb);

		if (!sb.len)
			string_list_append(&subjects,
					   oid_to_hex(&commit->object.oid));
		else
			string_list_append_nodup(&subjects,
						 strbuf_detach(&sb, NULL));
	}

	if (opts->credit_people)
		add_people_info(out, &authors, &committers);
	if (count > limit)
		strbuf_addf(out, "\n* %s: (%d commits)\n", name, count);
	else
		strbuf_addf(out, "\n* %s:\n", name);

	if (origin_data->is_local_branch && use_branch_desc)
		add_branch_desc(out, name);

	for (i = 0; i < subjects.nr; i++)
		if (i >= limit)
			strbuf_addstr(out, "  ...\n");
		else
			strbuf_addf(out, "  %s\n", subjects.items[i].string);

	clear_commit_marks((struct commit *)branch, flags);
	clear_commit_marks(head, flags);
	free_commit_list(rev->commits);
	rev->commits = NULL;
	rev->pending.nr = 0;

	string_list_clear(&authors, 0);
	string_list_clear(&committers, 0);
	string_list_clear(&subjects, 0);
}