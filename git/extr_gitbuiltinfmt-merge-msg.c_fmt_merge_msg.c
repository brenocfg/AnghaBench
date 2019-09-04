#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int len; char* buf; } ;
struct rev_info {int ignore_merges; int limited; int /*<<< orphan*/  commit_format; } ;
struct object_id {int dummy; } ;
struct merge_parents {void* item; } ;
struct fmt_merge_msg_opts {scalar_t__ shortlog_len; scalar_t__ add_title; } ;
struct commit {int dummy; } ;
typedef  int /*<<< orphan*/  merge_parents ;
struct TYPE_6__ {int nr; TYPE_1__* items; } ;
struct TYPE_5__ {scalar_t__ nr; } ;
struct TYPE_4__ {int /*<<< orphan*/  util; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_ONELINE ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  find_merge_parents (struct merge_parents*,struct strbuf*,struct object_id*) ; 
 int /*<<< orphan*/  fmt_merge_msg_sigs (struct strbuf*) ; 
 int /*<<< orphan*/  fmt_merge_msg_title (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ handle_line (char*,struct merge_parents*) ; 
 struct commit* lookup_commit_or_die (struct object_id*,char*) ; 
 int /*<<< orphan*/  memset (struct merge_parents*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ origins ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 void* resolve_refdup (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shortlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct commit*,struct rev_info*,struct fmt_merge_msg_opts*,struct strbuf*) ; 
 TYPE_2__ srcs ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_complete_line (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  the_repository ; 

int fmt_merge_msg(struct strbuf *in, struct strbuf *out,
		  struct fmt_merge_msg_opts *opts)
{
	int i = 0, pos = 0;
	struct object_id head_oid;
	const char *current_branch;
	void *current_branch_to_free;
	struct merge_parents merge_parents;

	memset(&merge_parents, 0, sizeof(merge_parents));

	/* get current branch */
	current_branch = current_branch_to_free =
		resolve_refdup("HEAD", RESOLVE_REF_READING, &head_oid, NULL);
	if (!current_branch)
		die("No current branch");
	if (starts_with(current_branch, "refs/heads/"))
		current_branch += 11;

	find_merge_parents(&merge_parents, in, &head_oid);

	/* get a line */
	while (pos < in->len) {
		int len;
		char *newline, *p = in->buf + pos;

		newline = strchr(p, '\n');
		len = newline ? newline - p : strlen(p);
		pos += len + !!newline;
		i++;
		p[len] = 0;
		if (handle_line(p, &merge_parents))
			die("error in line %d: %.*s", i, len, p);
	}

	if (opts->add_title && srcs.nr)
		fmt_merge_msg_title(out, current_branch);

	if (origins.nr)
		fmt_merge_msg_sigs(out);

	if (opts->shortlog_len) {
		struct commit *head;
		struct rev_info rev;

		head = lookup_commit_or_die(&head_oid, "HEAD");
		repo_init_revisions(the_repository, &rev, NULL);
		rev.commit_format = CMIT_FMT_ONELINE;
		rev.ignore_merges = 1;
		rev.limited = 1;

		strbuf_complete_line(out);

		for (i = 0; i < origins.nr; i++)
			shortlog(origins.items[i].string,
				 origins.items[i].util,
				 head, &rev, opts, out);
	}

	strbuf_complete_line(out);
	free(current_branch_to_free);
	free(merge_parents.item);
	return 0;
}