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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_2__ object; } ;
struct object_id {int dummy; } ;
struct TYPE_3__ {struct object_id oid; } ;
struct commit {int /*<<< orphan*/  date; TYPE_1__ object; } ;
struct archiver_args {int /*<<< orphan*/  time; struct commit const* commit; struct object_id const* commit_oid; struct tree* tree; int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (unsigned short) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dwim_ref (char const*,int,struct object_id*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int get_tree_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,struct object_id*,unsigned short*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 struct tree* parse_tree_indirect (struct object_id*) ; 
 int /*<<< orphan*/  remote_allow_unreachable ; 
 char* strchrnul (char const*,char) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parse_treeish_arg(const char **argv,
		struct archiver_args *ar_args, const char *prefix,
		int remote)
{
	const char *name = argv[0];
	const struct object_id *commit_oid;
	time_t archive_time;
	struct tree *tree;
	const struct commit *commit;
	struct object_id oid;

	/* Remotes are only allowed to fetch actual refs */
	if (remote && !remote_allow_unreachable) {
		char *ref = NULL;
		const char *colon = strchrnul(name, ':');
		int refnamelen = colon - name;

		if (!dwim_ref(name, refnamelen, &oid, &ref))
			die(_("no such ref: %.*s"), refnamelen, name);
		free(ref);
	}

	if (get_oid(name, &oid))
		die(_("not a valid object name: %s"), name);

	commit = lookup_commit_reference_gently(ar_args->repo, &oid, 1);
	if (commit) {
		commit_oid = &commit->object.oid;
		archive_time = commit->date;
	} else {
		commit_oid = NULL;
		archive_time = time(NULL);
	}

	tree = parse_tree_indirect(&oid);
	if (tree == NULL)
		die(_("not a tree object: %s"), oid_to_hex(&oid));

	if (prefix) {
		struct object_id tree_oid;
		unsigned short mode;
		int err;

		err = get_tree_entry(ar_args->repo,
				     &tree->object.oid,
				     prefix, &tree_oid,
				     &mode);
		if (err || !S_ISDIR(mode))
			die(_("current working directory is untracked"));

		tree = parse_tree_indirect(&tree_oid);
	}
	ar_args->tree = tree;
	ar_args->commit_oid = commit_oid;
	ar_args->commit = commit;
	ar_args->time = archive_time;
}