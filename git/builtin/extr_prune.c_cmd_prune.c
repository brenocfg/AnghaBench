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
struct rev_info {int exclude_promisor_objects; } ;
struct option {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option const OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option const OPT_END () ; 
 struct option const OPT_EXPIRY_DATE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct option const OPT__DRY_RUN (scalar_t__*,int /*<<< orphan*/ ) ; 
 struct option const OPT__VERBOSE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRUNE_PACKED_DRY_RUN ; 
 int /*<<< orphan*/  PRUNE_SHOW_ONLY ; 
 int /*<<< orphan*/  TIME_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,char*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  expire ; 
 scalar_t__ fetch_if_missing ; 
 int /*<<< orphan*/  for_each_loose_file_in_objdir (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rev_info*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_object_directory () ; 
 int /*<<< orphan*/  get_oid (char const*,struct object_id*) ; 
 scalar_t__ is_repository_shallow (int /*<<< orphan*/ ) ; 
 int isatty (int) ; 
 char* mkpathdup (char*,char*) ; 
 struct object* parse_object_or_die (struct object_id*,char const*) ; 
 int parse_options (int,char const**,char const*,struct option const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perform_reachability_traversal (struct rev_info*) ; 
 int /*<<< orphan*/  prune_cruft ; 
 int /*<<< orphan*/  prune_object ; 
 int /*<<< orphan*/  prune_packed_objects (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prune_shallow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prune_subdir ; 
 int /*<<< orphan*/  prune_usage ; 
 scalar_t__ read_replace_refs ; 
 int ref_paranoia ; 
 int /*<<< orphan*/  remove_temporary_files (char*) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,char const*) ; 
 scalar_t__ repository_format_precious_objects ; 
 scalar_t__ save_commit_buffer ; 
 scalar_t__ show_only ; 
 int show_progress ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  verbose ; 

int cmd_prune(int argc, const char **argv, const char *prefix)
{
	struct rev_info revs;
	int exclude_promisor_objects = 0;
	const struct option options[] = {
		OPT__DRY_RUN(&show_only, N_("do not remove, show only")),
		OPT__VERBOSE(&verbose, N_("report pruned objects")),
		OPT_BOOL(0, "progress", &show_progress, N_("show progress")),
		OPT_EXPIRY_DATE(0, "expire", &expire,
				N_("expire objects older than <time>")),
		OPT_BOOL(0, "exclude-promisor-objects", &exclude_promisor_objects,
			 N_("limit traversal to objects outside promisor packfiles")),
		OPT_END()
	};
	char *s;

	expire = TIME_MAX;
	save_commit_buffer = 0;
	read_replace_refs = 0;
	ref_paranoia = 1;
	repo_init_revisions(the_repository, &revs, prefix);

	argc = parse_options(argc, argv, prefix, options, prune_usage, 0);

	if (repository_format_precious_objects)
		die(_("cannot prune in a precious-objects repo"));

	while (argc--) {
		struct object_id oid;
		const char *name = *argv++;

		if (!get_oid(name, &oid)) {
			struct object *object = parse_object_or_die(&oid,
								    name);
			add_pending_object(&revs, object, "");
		}
		else
			die("unrecognized argument: %s", name);
	}

	if (show_progress == -1)
		show_progress = isatty(2);
	if (exclude_promisor_objects) {
		fetch_if_missing = 0;
		revs.exclude_promisor_objects = 1;
	}

	for_each_loose_file_in_objdir(get_object_directory(), prune_object,
				      prune_cruft, prune_subdir, &revs);

	prune_packed_objects(show_only ? PRUNE_PACKED_DRY_RUN : 0);
	remove_temporary_files(get_object_directory());
	s = mkpathdup("%s/pack", get_object_directory());
	remove_temporary_files(s);
	free(s);

	if (is_repository_shallow(the_repository)) {
		perform_reachability_traversal(&revs);
		prune_shallow(show_only ? PRUNE_SHOW_ONLY : 0);
	}

	return 0;
}