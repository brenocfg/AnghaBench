#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct todo_list {int dummy; } ;
struct repository {int dummy; } ;
struct replay_opts {scalar_t__ action; TYPE_5__* revs; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_11__ {int nr; TYPE_3__* rev; } ;
struct TYPE_9__ {int nr; TYPE_1__* objects; } ;
struct TYPE_12__ {TYPE_4__ cmdline; scalar_t__ no_walk; TYPE_2__ pending; } ;
struct TYPE_10__ {scalar_t__ whence; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ REPLAY_REVERT ; 
 scalar_t__ REV_CMD_REV ; 
 struct todo_list TODO_LIST_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 scalar_t__ create_seq_dir (struct repository*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 struct commit* get_revision (TYPE_5__*) ; 
 int /*<<< orphan*/  lookup_commit_reference_gently (struct repository*,struct object_id*,int) ; 
 int oid_object_info (struct repository*,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int pick_commits (struct repository*,struct todo_list*,struct replay_opts*) ; 
 scalar_t__ prepare_revision_walk (TYPE_5__*) ; 
 scalar_t__ read_and_refresh_cache (struct repository*,struct replay_opts*) ; 
 scalar_t__ save_head (int /*<<< orphan*/ ) ; 
 scalar_t__ save_opts (struct replay_opts*) ; 
 int single_pick (struct repository*,struct commit*,struct replay_opts*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  todo_list_release (struct todo_list*) ; 
 char* type_name (int) ; 
 int /*<<< orphan*/  update_abort_safety_file () ; 
 scalar_t__ walk_revs_populate_todo (struct todo_list*,struct replay_opts*) ; 

int sequencer_pick_revisions(struct repository *r,
			     struct replay_opts *opts)
{
	struct todo_list todo_list = TODO_LIST_INIT;
	struct object_id oid;
	int i, res;

	assert(opts->revs);
	if (read_and_refresh_cache(r, opts))
		return -1;

	for (i = 0; i < opts->revs->pending.nr; i++) {
		struct object_id oid;
		const char *name = opts->revs->pending.objects[i].name;

		/* This happens when using --stdin. */
		if (!strlen(name))
			continue;

		if (!get_oid(name, &oid)) {
			if (!lookup_commit_reference_gently(r, &oid, 1)) {
				enum object_type type = oid_object_info(r,
									&oid,
									NULL);
				return error(_("%s: can't cherry-pick a %s"),
					name, type_name(type));
			}
		} else
			return error(_("%s: bad revision"), name);
	}

	/*
	 * If we were called as "git cherry-pick <commit>", just
	 * cherry-pick/revert it, set CHERRY_PICK_HEAD /
	 * REVERT_HEAD, and don't touch the sequencer state.
	 * This means it is possible to cherry-pick in the middle
	 * of a cherry-pick sequence.
	 */
	if (opts->revs->cmdline.nr == 1 &&
	    opts->revs->cmdline.rev->whence == REV_CMD_REV &&
	    opts->revs->no_walk &&
	    !opts->revs->cmdline.rev->flags) {
		struct commit *cmit;
		if (prepare_revision_walk(opts->revs))
			return error(_("revision walk setup failed"));
		cmit = get_revision(opts->revs);
		if (!cmit)
			return error(_("empty commit set passed"));
		if (get_revision(opts->revs))
			BUG("unexpected extra commit from walk");
		return single_pick(r, cmit, opts);
	}

	/*
	 * Start a new cherry-pick/ revert sequence; but
	 * first, make sure that an existing one isn't in
	 * progress
	 */

	if (walk_revs_populate_todo(&todo_list, opts) ||
			create_seq_dir(r) < 0)
		return -1;
	if (get_oid("HEAD", &oid) && (opts->action == REPLAY_REVERT))
		return error(_("can't revert as initial commit"));
	if (save_head(oid_to_hex(&oid)))
		return -1;
	if (save_opts(opts))
		return -1;
	update_abort_safety_file();
	res = pick_commits(r, &todo_list, opts);
	todo_list_release(&todo_list);
	return res;
}