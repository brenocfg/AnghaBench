#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;
struct stash_info {int /*<<< orphan*/  w_tree; struct object_id b_tree; int /*<<< orphan*/  u_tree; scalar_t__ has_u; int /*<<< orphan*/  w_commit; struct object_id i_tree; } ;
struct merge_options {char* branch1; char* branch2; int verbosity; } ;
struct commit {int dummy; } ;
struct child_process {int git_cmd; char const* dir; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  REFRESH_QUIET ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int apply_cached (struct strbuf*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ diff_tree_binary (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_cache () ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_newly_staged (struct strbuf*,struct object_id*) ; 
 int /*<<< orphan*/  init_merge_options (struct merge_options*,int /*<<< orphan*/ ) ; 
 int merge_recursive_generic (struct merge_options*,struct object_id*,int /*<<< orphan*/ *,int,struct object_id const**,struct commit**) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ oideq (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  read_cache_preload (int /*<<< orphan*/ *) ; 
 scalar_t__ refresh_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rerere (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_head () ; 
 scalar_t__ reset_tree (struct object_id*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ restore_untracked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_command (struct child_process*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int update_index (struct strbuf*) ; 
 int /*<<< orphan*/  warning (char*) ; 
 scalar_t__ write_cache_as_tree (struct object_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_apply_stash(const char *prefix, struct stash_info *info,
			  int index, int quiet)
{
	int ret;
	int has_index = index;
	struct merge_options o;
	struct object_id c_tree;
	struct object_id index_tree;
	struct commit *result;
	const struct object_id *bases[1];

	read_cache_preload(NULL);
	if (refresh_cache(REFRESH_QUIET))
		return -1;

	if (write_cache_as_tree(&c_tree, 0, NULL))
		return error(_("cannot apply a stash in the middle of a merge"));

	if (index) {
		if (oideq(&info->b_tree, &info->i_tree) ||
		    oideq(&c_tree, &info->i_tree)) {
			has_index = 0;
		} else {
			struct strbuf out = STRBUF_INIT;

			if (diff_tree_binary(&out, &info->w_commit)) {
				strbuf_release(&out);
				return error(_("could not generate diff %s^!."),
					     oid_to_hex(&info->w_commit));
			}

			ret = apply_cached(&out);
			strbuf_release(&out);
			if (ret)
				return error(_("conflicts in index."
					       "Try without --index."));

			discard_cache();
			read_cache();
			if (write_cache_as_tree(&index_tree, 0, NULL))
				return error(_("could not save index tree"));

			reset_head();
		}
	}

	if (info->has_u && restore_untracked(&info->u_tree))
		return error(_("could not restore untracked files from stash"));

	init_merge_options(&o, the_repository);

	o.branch1 = "Updated upstream";
	o.branch2 = "Stashed changes";

	if (oideq(&info->b_tree, &c_tree))
		o.branch1 = "Version stash was based on";

	if (quiet)
		o.verbosity = 0;

	if (o.verbosity >= 3)
		printf_ln(_("Merging %s with %s"), o.branch1, o.branch2);

	bases[0] = &info->b_tree;

	ret = merge_recursive_generic(&o, &c_tree, &info->w_tree, 1, bases,
				      &result);
	if (ret) {
		rerere(0);

		if (index)
			fprintf_ln(stderr, _("Index was not unstashed."));

		return ret;
	}

	if (has_index) {
		if (reset_tree(&index_tree, 0, 0))
			return -1;
	} else {
		struct strbuf out = STRBUF_INIT;

		if (get_newly_staged(&out, &c_tree)) {
			strbuf_release(&out);
			return -1;
		}

		if (reset_tree(&c_tree, 0, 1)) {
			strbuf_release(&out);
			return -1;
		}

		ret = update_index(&out);
		strbuf_release(&out);
		if (ret)
			return -1;

		discard_cache();
	}

	if (quiet) {
		if (refresh_cache(REFRESH_QUIET))
			warning("could not refresh index");
	} else {
		struct child_process cp = CHILD_PROCESS_INIT;

		/*
		 * Status is quite simple and could be replaced with calls to
		 * wt_status in the future, but it adds complexities which may
		 * require more tests.
		 */
		cp.git_cmd = 1;
		cp.dir = prefix;
		argv_array_push(&cp.args, "status");
		run_command(&cp);
	}

	return 0;
}