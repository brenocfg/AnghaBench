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
struct object_id {int dummy; } ;
struct merge_options {char* subtree_shift; char const* branch1; char const* branch2; int verbosity; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct object_id const**) ; 
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 char* _ (char*) ; 
 char* better_branch_name (char*) ; 
 int /*<<< orphan*/  builtin_merge_recursive_usage ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  die_resolve_conflict (char*) ; 
 scalar_t__ ends_with (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  init_merge_options (struct merge_options*,int /*<<< orphan*/ ) ; 
 int merge_recursive_generic (struct merge_options*,struct object_id*,struct object_id*,unsigned int,struct object_id const**,struct commit**) ; 
 scalar_t__ parse_merge_opt (struct merge_options*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ repo_read_index_unmerged (int /*<<< orphan*/ ) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usagef (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int,char const*) ; 
 struct object_id* xmalloc (int) ; 

int cmd_merge_recursive(int argc, const char **argv, const char *prefix)
{
	const struct object_id *bases[21];
	unsigned bases_count = 0;
	int i, failed;
	struct object_id h1, h2;
	struct merge_options o;
	char *better1, *better2;
	struct commit *result;

	init_merge_options(&o, the_repository);
	if (argv[0] && ends_with(argv[0], "-subtree"))
		o.subtree_shift = "";

	if (argc < 4)
		usagef(builtin_merge_recursive_usage, argv[0]);

	for (i = 1; i < argc; ++i) {
		const char *arg = argv[i];

		if (starts_with(arg, "--")) {
			if (!arg[2])
				break;
			if (parse_merge_opt(&o, arg + 2))
				die(_("unknown option %s"), arg);
			continue;
		}
		if (bases_count < ARRAY_SIZE(bases)-1) {
			struct object_id *oid = xmalloc(sizeof(struct object_id));
			if (get_oid(argv[i], oid))
				die(_("could not parse object '%s'"), argv[i]);
			bases[bases_count++] = oid;
		}
		else
			warning(Q_("cannot handle more than %d base. "
				   "Ignoring %s.",
				   "cannot handle more than %d bases. "
				   "Ignoring %s.",
				    (int)ARRAY_SIZE(bases)-1),
				(int)ARRAY_SIZE(bases)-1, argv[i]);
	}
	if (argc - i != 3) /* "--" "<head>" "<remote>" */
		die(_("not handling anything other than two heads merge."));

	if (repo_read_index_unmerged(the_repository))
		die_resolve_conflict("merge");

	o.branch1 = argv[++i];
	o.branch2 = argv[++i];

	if (get_oid(o.branch1, &h1))
		die(_("could not resolve ref '%s'"), o.branch1);
	if (get_oid(o.branch2, &h2))
		die(_("could not resolve ref '%s'"), o.branch2);

	o.branch1 = better1 = better_branch_name(o.branch1);
	o.branch2 = better2 = better_branch_name(o.branch2);

	if (o.verbosity >= 3)
		printf(_("Merging %s with %s\n"), o.branch1, o.branch2);

	failed = merge_recursive_generic(&o, &h1, &h2, bases_count, bases, &result);

	free(better1);
	free(better2);

	if (failed < 0)
		return 128; /* die() error code */
	return failed;
}