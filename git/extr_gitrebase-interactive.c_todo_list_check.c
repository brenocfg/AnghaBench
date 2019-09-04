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
struct todo_list {int nr; struct todo_item* items; } ;
struct todo_item {int /*<<< orphan*/  arg_len; struct commit* commit; } ;
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct commit_seen {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
typedef  enum missing_commit_check_level { ____Placeholder_missing_commit_check_level } missing_commit_check_level ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int MISSING_COMMIT_CHECK_ERROR ; 
 int MISSING_COMMIT_CHECK_IGNORE ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  clear_commit_seen (struct commit_seen*) ; 
 int* commit_seen_at (struct commit_seen*,struct commit*) ; 
 int /*<<< orphan*/  find_unique_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_missing_commit_check_level () ; 
 int /*<<< orphan*/  init_commit_seen (struct commit_seen*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  todo_item_get_arg (struct todo_list*,struct todo_item*) ; 

int todo_list_check(struct todo_list *old_todo, struct todo_list *new_todo)
{
	enum missing_commit_check_level check_level = get_missing_commit_check_level();
	struct strbuf missing = STRBUF_INIT;
	int res = 0, i;
	struct commit_seen commit_seen;

	init_commit_seen(&commit_seen);

	if (check_level == MISSING_COMMIT_CHECK_IGNORE)
		goto leave_check;

	/* Mark the commits in git-rebase-todo as seen */
	for (i = 0; i < new_todo->nr; i++) {
		struct commit *commit = new_todo->items[i].commit;
		if (commit)
			*commit_seen_at(&commit_seen, commit) = 1;
	}

	/* Find commits in git-rebase-todo.backup yet unseen */
	for (i = old_todo->nr - 1; i >= 0; i--) {
		struct todo_item *item = old_todo->items + i;
		struct commit *commit = item->commit;
		if (commit && !*commit_seen_at(&commit_seen, commit)) {
			strbuf_addf(&missing, " - %s %.*s\n",
				    find_unique_abbrev(&commit->object.oid, DEFAULT_ABBREV),
				    item->arg_len,
				    todo_item_get_arg(old_todo, item));
			*commit_seen_at(&commit_seen, commit) = 1;
		}
	}

	/* Warn about missing commits */
	if (!missing.len)
		goto leave_check;

	if (check_level == MISSING_COMMIT_CHECK_ERROR)
		res = 1;

	fprintf(stderr,
		_("Warning: some commits may have been dropped accidentally.\n"
		"Dropped commits (newer to older):\n"));

	/* Make the list user-friendly and display */
	fputs(missing.buf, stderr);
	strbuf_release(&missing);

	fprintf(stderr, _("To avoid this message, use \"drop\" to "
		"explicitly remove a commit.\n\n"
		"Use 'git config rebase.missingCommitsCheck' to change "
		"the level of warnings.\n"
		"The possible behaviours are: ignore, warn, error.\n\n"));

leave_check:
	clear_commit_seen(&commit_seen);
	return res;
}