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
struct merge_options {char* subtree_shift; int show_rename_progress; char const* branch1; int /*<<< orphan*/  branch2; int /*<<< orphan*/  renormalize; } ;
struct lock_file {int dummy; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  REFRESH_QUIET ; 
 int SKIP_IF_UNCHANGED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  commit_list_insert (int /*<<< orphan*/ ,struct commit_list**) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_index_file () ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_merge_options (struct merge_options*,int /*<<< orphan*/ ) ; 
 int isatty (int) ; 
 int merge_recursive (struct merge_options*,struct commit*,int /*<<< orphan*/ ,struct commit_list*,struct commit**) ; 
 TYPE_1__* merge_remote_util (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_renormalize ; 
 scalar_t__ parse_merge_opt (struct merge_options*,int /*<<< orphan*/ ) ; 
 scalar_t__ refresh_and_write_cache (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int show_progress ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  the_repository ; 
 int try_merge_command (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,struct commit_list*,char const*,struct commit_list*) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int) ; 
 int /*<<< orphan*/ * xopts ; 
 int xopts_nr ; 

__attribute__((used)) static int try_merge_strategy(const char *strategy, struct commit_list *common,
			      struct commit_list *remoteheads,
			      struct commit *head)
{
	const char *head_arg = "HEAD";

	if (refresh_and_write_cache(REFRESH_QUIET, SKIP_IF_UNCHANGED, 0) < 0)
		return error(_("Unable to write index."));

	if (!strcmp(strategy, "recursive") || !strcmp(strategy, "subtree")) {
		struct lock_file lock = LOCK_INIT;
		int clean, x;
		struct commit *result;
		struct commit_list *reversed = NULL;
		struct merge_options o;
		struct commit_list *j;

		if (remoteheads->next) {
			error(_("Not handling anything other than two heads merge."));
			return 2;
		}

		init_merge_options(&o, the_repository);
		if (!strcmp(strategy, "subtree"))
			o.subtree_shift = "";

		o.renormalize = option_renormalize;
		o.show_rename_progress =
			show_progress == -1 ? isatty(2) : show_progress;

		for (x = 0; x < xopts_nr; x++)
			if (parse_merge_opt(&o, xopts[x]))
				die(_("Unknown option for merge-recursive: -X%s"), xopts[x]);

		o.branch1 = head_arg;
		o.branch2 = merge_remote_util(remoteheads->item)->name;

		for (j = common; j; j = j->next)
			commit_list_insert(j->item, &reversed);

		hold_locked_index(&lock, LOCK_DIE_ON_ERROR);
		clean = merge_recursive(&o, head,
				remoteheads->item, reversed, &result);
		if (clean < 0)
			exit(128);
		if (write_locked_index(&the_index, &lock,
				       COMMIT_LOCK | SKIP_IF_UNCHANGED))
			die(_("unable to write %s"), get_index_file());
		return clean ? 0 : 1;
	} else {
		return try_merge_command(the_repository,
					 strategy, xopts_nr, xopts,
					 common, head_arg, remoteheads);
	}
}