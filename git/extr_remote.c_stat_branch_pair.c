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
struct rev_info {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
struct argv_array {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;
typedef  enum ahead_behind_flags { ____Placeholder_ahead_behind_flags } ahead_behind_flags ;

/* Variables and functions */
 int AHEAD_BEHIND_FULL ; 
 int AHEAD_BEHIND_QUICK ; 
 int /*<<< orphan*/  ALL_REV_FLAGS ; 
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  BUG (char*,int) ; 
 int SYMMETRIC_LEFT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 struct commit* get_revision (struct rev_info*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 scalar_t__ read_ref (char const*,struct object_id*) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int stat_branch_pair(const char *branch_name, const char *base,
			     int *num_ours, int *num_theirs,
			     enum ahead_behind_flags abf)
{
	struct object_id oid;
	struct commit *ours, *theirs;
	struct rev_info revs;
	struct argv_array argv = ARGV_ARRAY_INIT;

	/* Cannot stat if what we used to build on no longer exists */
	if (read_ref(base, &oid))
		return -1;
	theirs = lookup_commit_reference(the_repository, &oid);
	if (!theirs)
		return -1;

	if (read_ref(branch_name, &oid))
		return -1;
	ours = lookup_commit_reference(the_repository, &oid);
	if (!ours)
		return -1;

	*num_theirs = *num_ours = 0;

	/* are we the same? */
	if (theirs == ours)
		return 0;
	if (abf == AHEAD_BEHIND_QUICK)
		return 1;
	if (abf != AHEAD_BEHIND_FULL)
		BUG("stat_branch_pair: invalid abf '%d'", abf);

	/* Run "rev-list --left-right ours...theirs" internally... */
	argv_array_push(&argv, ""); /* ignored */
	argv_array_push(&argv, "--left-right");
	argv_array_pushf(&argv, "%s...%s",
			 oid_to_hex(&ours->object.oid),
			 oid_to_hex(&theirs->object.oid));
	argv_array_push(&argv, "--");

	repo_init_revisions(the_repository, &revs, NULL);
	setup_revisions(argv.argc, argv.argv, &revs, NULL);
	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));

	/* ... and count the commits on each side. */
	while (1) {
		struct commit *c = get_revision(&revs);
		if (!c)
			break;
		if (c->object.flags & SYMMETRIC_LEFT)
			(*num_ours)++;
		else
			(*num_theirs)++;
	}

	/* clear object flags smudged by the above traversal */
	clear_commit_marks(ours, ALL_REV_FLAGS);
	clear_commit_marks(theirs, ALL_REV_FLAGS);

	argv_array_clear(&argv);
	return 1;
}