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
struct strbuf {int dummy; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;
struct commit {int dummy; } ;
struct TYPE_4__ {struct commit_list* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* commit_list_insert (struct commit*,struct commit_list**) ; 
 struct commit* get_merge_parent (char const*) ; 
 int /*<<< orphan*/  handle_fetch_head (struct commit_list**,struct strbuf*) ; 
 int /*<<< orphan*/  have_message ; 
 int /*<<< orphan*/  help_unknown_ref (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_name (int /*<<< orphan*/ ,struct strbuf*) ; 
 TYPE_1__* merge_remote_util (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_merge_message (struct strbuf*,struct strbuf*) ; 
 struct commit_list* reduce_parents (struct commit*,int*,struct commit_list*) ; 
 scalar_t__ shortlog_len ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static struct commit_list *collect_parents(struct commit *head_commit,
					   int *head_subsumed,
					   int argc, const char **argv,
					   struct strbuf *merge_msg)
{
	int i;
	struct commit_list *remoteheads = NULL;
	struct commit_list **remotes = &remoteheads;
	struct strbuf merge_names = STRBUF_INIT, *autogen = NULL;

	if (merge_msg && (!have_message || shortlog_len))
		autogen = &merge_names;

	if (head_commit)
		remotes = &commit_list_insert(head_commit, remotes)->next;

	if (argc == 1 && !strcmp(argv[0], "FETCH_HEAD")) {
		handle_fetch_head(remotes, autogen);
		remoteheads = reduce_parents(head_commit, head_subsumed, remoteheads);
	} else {
		for (i = 0; i < argc; i++) {
			struct commit *commit = get_merge_parent(argv[i]);
			if (!commit)
				help_unknown_ref(argv[i], "merge",
						 _("not something we can merge"));
			remotes = &commit_list_insert(commit, remotes)->next;
		}
		remoteheads = reduce_parents(head_commit, head_subsumed, remoteheads);
		if (autogen) {
			struct commit_list *p;
			for (p = remoteheads; p; p = p->next)
				merge_name(merge_remote_util(p->item)->name, autogen);
		}
	}

	if (autogen) {
		prepare_merge_message(autogen, merge_msg);
		strbuf_release(autogen);
	}

	return remoteheads;
}